#include "dbdatasource.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "constants.h"
#include "custom_errors.h"

//-----------------------------------------------------------------------------
DBDataSource::DBDataSource(const QString& inDbFilePath, QObject *inParent) : aThreadedDataSource(inParent)
{
    mDataBase = QSqlDatabase::addDatabase("QSQLITE");
    mDataBase.setDatabaseName(inDbFilePath);

    if (mDataBase.open())
    {
        if (createTable())
            initTable();
    }
}
//-----------------------------------------------------------------------------
DBDataSource::~DBDataSource()
{
    mDataBase.close();
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
void DBDataSource::updateInThread()
{
    std::error_code Err = CustomErrorCodes::cecNoError;
    mDataStorage.clear();

    if (!mDataBase.isOpen())
    {
        Err = CustomErrorCodes::cecParserDbConnectFail;
        sig_onError("Error in Query result: " + QString::fromStdString(Err.message()));
    }
    else
    {
        QString QueryText = "SELECT * FROM CustomData";

        QSqlQuery Query(mDataBase);
        if (Query.exec(QueryText))
        {
            std::size_t UpdatePos = 0;
            std::size_t UpdateSize = 0;

            if(Query.last())
            {
                UpdateSize = Query.at() + 1;
                Query.first();
                Query.previous();
            }

            while (Query.next())
            {
                Err = checkParams(Query);

                // Индикация состояния
                UpdatePos++;
                sig_onUpdateProc(UpdatePos, UpdateSize);

                if (Err)
                    sig_onError("Error in Query result: " + QString::fromStdString(Err.message()));
                else
                {
                    std::size_t Index = Query.value("id").toUInt();
                    std::shared_ptr<BaseData> NewRecord = std::make_shared<RowData>(Index);

                    NewRecord->mData.mTextEditor = Query.value(QString::fromStdString(cTextEditor)).toString();
                    NewRecord->mData.mFileFormats = Query.value(QString::fromStdString(cFileFormats)).toString();
                    NewRecord->mData.mEncoding = Query.value(QString::fromStdString(cEncoding)).toString();
                    NewRecord->mData.mHasIntelLisense = Query.value(QString::fromStdString(cHasIntelLisense)).toBool();
                    NewRecord->mData.mHasPlugin = Query.value(QString::fromStdString(cHasPlugins)).toBool();
                    NewRecord->mData.mCanCompile = Query.value(QString::fromStdString(cCanCompile)).toBool();

                    mDataStorage.push_back(NewRecord);
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------
void DBDataSource::uploadInThread()
{
    for (auto& FileData : mDataStorage)
    {
        if (!FileData->mDataModified)
            continue;

        CustomData DataBuff;

        {
            std::lock_guard<std::mutex> lg(mDataDefender); // В защищённом режиме
            DataBuff = FileData->mData; // Копируем данные на запись
        }

        std::error_code Err = writeRow(std::dynamic_pointer_cast<RowData>(FileData)->mIndex, DataBuff); // Запускаем запись

        if (!Err) // Ошибка записи
        {
            qDebug() << QString::fromStdString(Err.message());
            sig_onError(QString::fromStdString(Err.message()));
        }
    }
}
//-----------------------------------------------------------------------------
bool DBDataSource::createTable() const
{
    QString QueryText = "CREATE TABLE IF NOT EXISTS CustomData ("
                        "id integer PRIMARY KEY AUTOINCREMENT, "
                        "" + QString::fromStdString(cTextEditor) + " varchar(50) NOT NULL, "
                        "" + QString::fromStdString(cFileFormats) + " varchar(50) NOT NULL, "
                        "" + QString::fromStdString(cEncoding) + " varchar(50) NOT NULL, "
                        "" + QString::fromStdString(cHasIntelLisense) + " integer NOT NULL, "
                        "" + QString::fromStdString(cHasPlugins) + " integer NOT NULL, "
                        "" + QString::fromStdString(cCanCompile) + " integer NOT NULL)";

    QSqlQuery Query(mDataBase);
    return Query.exec(QueryText);
}
//-----------------------------------------------------------------------------
void DBDataSource::initTable() const
{
    QString QueryText = "SELECT COUNT(*) FROM CustomData";
    QSqlQuery Query(mDataBase);

    if (Query.exec(QueryText))
    {
        Query.next();
        if (Query.value(0).toInt() == 0)
        {
            QSqlQuery Query(mDataBase);
            //            Query.prepare("INSERT INTO CustomData VALUES (?, ?, ?, ?, ?, ?)");
            Query.prepare("INSERT INTO CustomData VALUES ("
                        ":id, "
                        ":" + QString::fromStdString(cTextEditor) + ", "
                        ":" + QString::fromStdString(cFileFormats) + ", "
                        ":" + QString::fromStdString(cEncoding) + ", "
                        ":" + QString::fromStdString(cHasIntelLisense) + ", "
                        ":" + QString::fromStdString(cHasPlugins) + ", "
                        ":" + QString::fromStdString(cCanCompile) + ")");

            QVariantList TextEditor, FileFormats, Encoding, HasIntelLisense, HasPlugins, CanCompile, IDs;

            IDs                 << 1            << 2            << 3            << 4            << 5            << 6;
            TextEditor          << "Atom1"      << "notepad"    << "notepad++"  << "Sublime"    << "vim"        << "VisualStudio Code";
            FileFormats         << "everything" << "txt"        << "everything" << "everything" << "everything" << "everything";
            Encoding            << "ANSI; UTF;" << "ANSI"       << "ANSI; UTF;" << "ANSI; UTF;" << "ANSI; UTF"  << "ANSI; UTF;";
            HasIntelLisense     << true         << false        << true         << true         << false        << true;
            HasPlugins          << true         << true         << true         << true         << false        << true;
            CanCompile          << false        << true         << false        << false        << false        << true;

            Query.addBindValue(IDs);
            Query.addBindValue(TextEditor);
            Query.addBindValue(FileFormats);
            Query.addBindValue(Encoding);
            Query.addBindValue(HasIntelLisense);
            Query.addBindValue(HasPlugins);
            Query.addBindValue(CanCompile);

            if (!Query.execBatch())
                qDebug() << Query.lastError();
        }
    }
}
//-----------------------------------------------------------------------------
std::error_code DBDataSource::checkParams(const QSqlQuery& inQueryRes) const
{
    std::error_code Result = CustomErrorCodes::cecNoError;
    QVariant Val;

    Val = inQueryRes.value("id");
    if (Val.isNull() || !Val.isValid())
        Result = CustomErrorCodes::cecParserDbNotFoundID;

    Val = inQueryRes.value(QString::fromStdString(cTextEditor));
    if (Val.isNull() || !Val.isValid())
        Result = CustomErrorCodes::cecParserNotFoundParamTextEditor;

    Val = inQueryRes.value(QString::fromStdString(cFileFormats));
    if (Val.isNull() || !Val.isValid())
        Result = CustomErrorCodes::cecParserNotFoundParamFileFormats;

    Val = inQueryRes.value(QString::fromStdString(cEncoding));
    if (Val.isNull() || !Val.isValid())
        Result = CustomErrorCodes::cecParserNotFoundParamEncoding;

    Val = inQueryRes.value(QString::fromStdString(cHasIntelLisense));
    if (Val.isNull() || !Val.isValid())
        Result = CustomErrorCodes::cecParserNotFoundParamHasIntelLisense;

    Val = inQueryRes.value(QString::fromStdString(cHasPlugins));
    if (Val.isNull() || !Val.isValid())
        Result = CustomErrorCodes::cecParserNotFoundParamHasPlugin;

    Val = inQueryRes.value(QString::fromStdString(cCanCompile));
    if (Val.isNull() || !Val.isValid())
        Result = CustomErrorCodes::cecParserNotFoundParamCanCompile;

    return Result;
}
//-----------------------------------------------------------------------------
std::error_code DBDataSource::writeRow(const std::size_t inIndex, const CustomData& inData)
{
    std::error_code Result = CustomErrorCodes::cecNoError;

    if (!mDataBase.isOpen())
        Result = CustomErrorCodes::cecWriterDbConnectFail;
    else
    {
        QSqlQuery Query(mDataBase);
        Query.prepare("UPDATE CustomData SET "
                      "" + QString::fromStdString(cTextEditor) +" = :" + QString::fromStdString(cTextEditor) + ", "
                      "" + QString::fromStdString(cFileFormats) +" = :" + QString::fromStdString(cFileFormats) + ", "
                      "" + QString::fromStdString(cEncoding) +" = :" + QString::fromStdString(cEncoding) + ", "
                      "" + QString::fromStdString(cHasIntelLisense) +" = :" + QString::fromStdString(cHasIntelLisense) + ", "
                      "" + QString::fromStdString(cHasPlugins) +" = :" + QString::fromStdString(cHasPlugins) + ", "
                      "" + QString::fromStdString(cCanCompile) +" = :" + QString::fromStdString(cCanCompile) + " "
                      "WHERE id = :id");

        Query.bindValue(":id", static_cast<quint64>(inIndex));
        Query.bindValue(":" + QString::fromStdString(cTextEditor), inData.mTextEditor);
        Query.bindValue(":" + QString::fromStdString(cFileFormats), inData.mFileFormats);
        Query.bindValue(":" + QString::fromStdString(cEncoding), inData.mEncoding);
        Query.bindValue(":" + QString::fromStdString(cHasIntelLisense), inData.mHasIntelLisense);
        Query.bindValue(":" + QString::fromStdString(cHasPlugins), inData.mHasPlugin);
        Query.bindValue(":" + QString::fromStdString(cCanCompile), inData.mCanCompile);

        if (!Query.exec())
            Result = CustomErrorCodes::cecWriterDbWriteFail;
    }

    return Result;
}
//-----------------------------------------------------------------------------
