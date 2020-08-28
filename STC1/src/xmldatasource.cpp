#include "xmldatasource.h"

#include <QCryptographicHash>
#include <QXmlStreamReader>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>
#include <QUuid>

#include "custom_errors.h"

//-----------------------------------------------------------------------------
XmlDataSource::XmlDataSource(const QStringList &inFilesPaths)
{
    for (const QString& Path : inFilesPaths)
        mDataStorage.emplace_back(std::make_unique<XmlFileData>(Path));
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
void XmlDataSource::updateInThread()
{
    std::size_t UpdatePos = 0;
    const std::size_t UpdateSize = mDataStorage.size();

    auto It = mDataStorage.begin();
    while (It != mDataStorage.end())
    {
        auto FileData = std::dynamic_pointer_cast<XmlFileData>(*It);
        QByteArray FileHash = getFileHash(FileData->mPath);
        if (FileData->mHash == FileHash) // Если файл был изменён
            continue;

        // Индикация состояния
        UpdatePos++;
        sig_onUpdateProc(UpdatePos, UpdateSize);

        CustomData DataBuff;
        std::error_code Err = readXML(FileData->mPath, DataBuff);

        if (Err) // Ошибка чтения
        {
            qDebug() << "Error in file " + QFileInfo(FileData->mPath).fileName() + " : " + QString::fromStdString(Err.message());
            sig_onError("Error in file " + QFileInfo(FileData->mPath).fileName() + " : " + QString::fromStdString(Err.message()));
            It = mDataStorage.erase(It); // Удаляем из списка битый файл
        }
        else // Если чтение прошло успешно
        {
            std::lock_guard<std::mutex> lg(mDataDefender); // В защищённом режиме
            FileData->mData = std::move(DataBuff); // Получаем считанные данные
            FileData->mHash = std::move(FileHash); // Запоминаем новый хеш
            It++;
        }
   }
}
//-----------------------------------------------------------------------------
void XmlDataSource::uploadInThread()
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

        std::error_code Err = writeXML(std::dynamic_pointer_cast<XmlFileData>(FileData)->mPath, DataBuff); // Запускаем запись

        if (!Err) // Ошибка записи
        {
            qDebug() << QString::fromStdString(Err.message());
            sig_onError(QString::fromStdString(Err.message()));
        }
        else
        {
            std::lock_guard<std::mutex> lg(mDataDefender); // В защищённом режиме
            FileData->mDataModified = false; // Сбрасываем флаг изменений
        }
    }
}
//-----------------------------------------------------------------------------
QByteArray XmlDataSource::getFileHash(const QString& inFilePath) const
{
    QByteArray Result;

    QFile File(inFilePath);

    if (File.open(QFile::ReadOnly))
    {
        QCryptographicHash hash(QCryptographicHash::Algorithm::Md5);

        if (hash.addData(&File))
            Result = hash.result();

        File.close();
    }

    return std::move(Result);
}
//-----------------------------------------------------------------------------
std::error_code XmlDataSource::readXML(const QString &inFilPath, CustomData &outData)
{
    std::error_code Result = CustomErrorCodes::cecNoError;

    if (!QFile::exists(inFilPath)) // Проверяем что файл существует
        Result = CustomErrorCodes::cecParserXmlFileNotExists;
    else
    {
        QFile inputFile(inFilPath);
        // Пытаемся открыть файл на чтение
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
            Result = CustomErrorCodes::cecParserXmlFileOpenFail;
        else
            outData = parseXml(inputFile, Result);

        inputFile.close();
    }

    return Result;
}
//-----------------------------------------------------------------------------
std::error_code XmlDataSource::writeXML(const QString &inFilPath, CustomData &outDat) const
{
    std::error_code Result = CustomErrorCodes::cecNoError;

    QFile outputFile(inFilPath);
    // Пытаемся открыть файл на чтение
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        Result = CustomErrorCodes::cecWriterXmlFileOpenFail;
    else
    {
        QXmlStreamWriter xmlWriter(&outputFile);
        xmlWriter.setAutoFormatting(true);  // Set the auto-formatting text

        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("root");

        xmlWriter.writeStartElement("texteditor");
        xmlWriter.writeCharacters(outDat.mTextEditor);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("fileformats");
        xmlWriter.writeCharacters(outDat.mFileFormats);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("encoding");
        xmlWriter.writeCharacters(outDat.mEncoding);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("hasintellisense");
        xmlWriter.writeCharacters( (outDat.mHasIntelLisense ? "true" : "false") );
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("hasplugins");
        xmlWriter.writeCharacters( (outDat.mHasPlugin ? "true" : "false") );
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("cancompile");
        xmlWriter.writeCharacters( (outDat.mCanCompile ? "true" : "false") );
        xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();

        outputFile.close();
    }

    return Result;
}
//-----------------------------------------------------------------------------
CustomData XmlDataSource::parseXml(QFile& inXmlFile, std::error_code& outErrorCode) const
{
    CustomData Result;
    QXmlStreamReader xmlReader(&inXmlFile); // Инициализируем парсер XML

    bool ParseErr = false;
    ParamArray FindParams = { {false} };

    while(!xmlReader.atEnd()) // Перебираем весь файл
    {
        switch (xmlReader.readNext()) // Проверяем тег
        {
            case QXmlStreamReader::Comment: { break; } // Если встретили коментарий

            case QXmlStreamReader::StartElement: // Если встретили начальный тег
            {
                if (xmlReader.name() == QString::fromStdString(cTextEditor)) // Если это тег тектового редактора
                {
                    Result.mTextEditor = xmlReader.readElementText();
                    FindParams[static_cast<size_t>(CustomColumns::ccTextEditor)] = true;
                }
                else if (xmlReader.name() == QString::fromStdString(cFileFormats)) // Если это тег форматов
                {
                    Result.mFileFormats = xmlReader.readElementText();
                    FindParams[static_cast<size_t>(CustomColumns::ccFileFormats)] = true;
                }
                else if (xmlReader.name() == QString::fromStdString(cEncoding)) // Если это тег кодировки
                {
                    Result.mEncoding = xmlReader.readElementText();
                    FindParams[static_cast<size_t>(CustomColumns::ccEncoding)] = true;
                }
                else if (xmlReader.name() == QString::fromStdString(cHasIntelLisense)) // Если это тег лицензии
                {
                    QString Val = xmlReader.readElementText();
                    Result.mHasIntelLisense = (Val.toLower() == "true") ? true : false;
                    FindParams[static_cast<size_t>(CustomColumns::ccHasIntelLisense)] = true;
                }
                else if (xmlReader.name() == QString::fromStdString(cHasPlugins)) // Если это тег поддержики плагинов
                {
                    QString Val = xmlReader.readElementText();
                    Result.mHasPlugin = (Val.toLower() == "true") ? true : false;
                    FindParams[static_cast<size_t>(CustomColumns::ccHasPlugin)] = true;
                }
                else if (xmlReader.name() == QString::fromStdString(cCanCompile)) // Если это тег поддержики компиляции
                {
                    QString Val = xmlReader.readElementText();
                    Result.mCanCompile = (Val.toLower() == "true") ? true : false;
                    FindParams[static_cast<size_t>(CustomColumns::ccCanCompile)] = true;
                }
            }

//                    default: { break; }
        } // switch

        if (xmlReader.hasError()) // Если произошла ошибка парсинга
        {
            ParseErr = true;
            break;
        }
    }

    // Проверяем корректность
    if (ParseErr) // Если произошла ошибка парсинга
    {
        Result = CustomData(); // Обнуляем результат
        outErrorCode = CustomErrorCodes::cecParserXmlParseFail;
    }
    else
    {   // Проверяем, все ли параметры были найдены
        outErrorCode = checkParams(FindParams);
        if (outErrorCode != CustomErrorCodes::cecNoError) // Если произошла ошибка
            Result = CustomData(); // Обнуляем результат
    }

    return std::move(Result);
}
//-----------------------------------------------------------------------------
std::error_code XmlDataSource::checkParams(const ParamArray& inParam) const
{
    auto FindRes = std::find(inParam.cbegin(), inParam.cend(), false);
    if (FindRes != inParam.cend()) // Если произошла ошибка парсинга или какой то параметр не был найден
    {
        switch (static_cast<CustomColumns>(std::distance(inParam.cbegin(), FindRes))) // Проверяем столбец
        {
            case CustomColumns::ccTextEditor:
                return CustomErrorCodes::cecParserNotFoundParamTextEditor;
            case CustomColumns::ccFileFormats:
                return CustomErrorCodes::cecParserNotFoundParamFileFormats;
            case CustomColumns::ccEncoding:
                return CustomErrorCodes::cecParserNotFoundParamEncoding;
            case CustomColumns::ccHasIntelLisense:
                return CustomErrorCodes::cecParserNotFoundParamHasIntelLisense;
            case CustomColumns::ccHasPlugin:
                return CustomErrorCodes::cecParserNotFoundParamHasPlugin;
            case CustomColumns::ccCanCompile:
                return CustomErrorCodes::cecParserNotFoundParamCanCompile;
        }
    }

    return CustomErrorCodes::cecNoError; // Все параметры были найдены
}
//-----------------------------------------------------------------------------
