#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "comboboxdelegate.h"
#include "customtablemodel.h"
#include "constants.h"

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *inParent) :
    QMainWindow(inParent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initTable();
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;

    if (mAppRole == eAppRole::arServer && mDataStorege)
        saveToDB(mDataStorege->dump());
}
//-----------------------------------------------------------------------------
bool MainWindow::initialize()
{
    mAppRole = selectAppRole();

    if (mDataStorege)
        ui->tableView->setModel(new CustomTableModel(mDataStorege));

    if (mAppRole == eAppRole::arNone)
    {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось выбрать роль приложения!"));
        return false;
    }
    else
        return true;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void MainWindow::initTable()
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    ui->tableView->setItemDelegateForColumn(CustomColumns::ccCountry, new ComboBoxDelegate(this));
}
//-----------------------------------------------------------------------------
eAppRole MainWindow::selectAppRole()
{
    eAppRole Result;

    if (becomeServer()) // Пытаемся стать сервером
    {
        Result = eAppRole::arServer;
        mDataStorege = std::make_shared<DataStorege>(loadFromDB()); // Инициализируем из БД
    }
    else
    {
        if (becomeClient()) // Пытаемся стать клиентом
        {
            Result = eAppRole::arClient;
            mDataStorege = std::make_shared<DataStorege>(); // Инициализируем по сети
        }
        else
            Result = eAppRole::arNone; // Жизнь прошла зря...
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool MainWindow::becomeServer()
{
    bool Result = true;//false;

    return Result;
}
//-----------------------------------------------------------------------------
bool MainWindow::becomeClient()
{
    bool Result = false;

    return Result;
}
//-----------------------------------------------------------------------------
QSqlDatabase MainWindow::getDataBaseConnection() const
{
    QSqlDatabase DB;

    if (!QSqlDatabase::contains(mDbConnectionName))
    {
        DB = QSqlDatabase::addDatabase("QSQLITE", mDbConnectionName);
        DB.setDatabaseName(mDbFileName);
        DB.open();
    }
    else
        DB = QSqlDatabase::database(mDbConnectionName, true);


    return std::move(DB);
}
//-----------------------------------------------------------------------------
bool MainWindow::createDbTable() const
{
    bool Result = false;
    QSqlDatabase DB = getDataBaseConnection();

    if (!DB.isOpen())
    {
        Result = false;
        qDebug() << DB.lastError();
    }
    else
    {
        QString QueryText = "CREATE TABLE IF NOT EXISTS CustomData ("
                            "" + cID + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "" + cName + " VARCHAR(50) NOT NULL, "
                            "" + cPhone + " UNSIGNED BIG INT NOT NULL, "
                            "" + cCounty + " INTEGER NOT NULL)";

        QSqlQuery Query(DB);
        Result = Query.exec(QueryText);
        DB.close();
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool MainWindow::initDbTable() const
{
    bool Result = false;
    QSqlDatabase DB = getDataBaseConnection();

    if (!DB.isOpen())
    {
        Result = false;
        qDebug() << DB.lastError();
    }
    else
    {
        QSqlQuery Query(DB);

        if (!Query.exec("SELECT COUNT(*) FROM CustomData"))
        {
            Result = false;
            qDebug() << Query.lastError();
        }
        else
        {
            Query.next();

            if (Query.value(0).toInt() != 0)
                Result = false;
            else
            {
                Query.prepare("INSERT INTO CustomData VALUES ("
                            ":" + cID + ", "
                            ":" + cName + ", "
                            ":" + cPhone + ", "
                            ":" + cCounty + ")");

                QVariantList IDs, Name, Phone, Country;

                IDs     << 1                    << 2                    << 3                    << 4                    << 5                    << 6;
                Name    << "Осип"               << "Розалина"           << "Виталий"            << "Валерия"            << "Евгений"            << "Людмила";
                Phone   << quint64(8384201433)  << quint64(85540729804) << quint64(85175119904) << quint64(85155921468) << quint64(84041925532) << quint64(89463735992);
                Country << cUSA                 << cRussia              << cUkraine             << cUSA                 << cRussia              << cUkraine;

                Query.addBindValue(IDs);
                Query.addBindValue(Name);
                Query.addBindValue(Phone);
                Query.addBindValue(Country);


                Result = Query.execBatch();
                if (!Result)
                    qDebug() << Query.lastError();
            }
        }
        DB.close();
    }

    return Result;
}
//-----------------------------------------------------------------------------
std::vector<CustomData> MainWindow::loadFromDB()
{
    if (createDbTable())
        initDbTable();

    std::vector<CustomData> Result;
    QSqlDatabase DB = getDataBaseConnection();

    if (!DB.isOpen())
        qDebug() << DB.lastError();
    else
    {
        QSqlQuery Query(DB);

        if (!Query.exec("SELECT * FROM CustomData"))
            qDebug() << Query.lastError();
        else
        {
            while (Query.next())
            {
                CustomData NewData;

                NewData.mID = Query.value(cID).toUInt();
                NewData.mName = Query.value(cName).toString();
                NewData.mTelefon = Query.value(cPhone).toULongLong();
                NewData.mCountryCode = static_cast<eCountry>(Query.value(cCounty).toInt());

                Result.push_back(NewData);
            }
        }

        DB.close();
    }

    return std::move(Result);
}
//-----------------------------------------------------------------------------
bool MainWindow::saveToDB(const std::vector<CustomData> &inData) const
{
    bool Result = false;
    QSqlDatabase DB = getDataBaseConnection();

    if (!DB.isOpen())
    {
        Result = false;
        qDebug() << DB.lastError();
    }
    else
    {
        QSqlQuery Query(DB);

        for (const auto& Row : inData)
        {
            Query.prepare("INSERT OR REPLACE INTO CustomData ("
                            "" + cID + ", "
                            "" + cName + ", "
                            "" + cPhone + ", "
                            "" + cCounty + ""
                            " ) VALUES ( "
                            ":" + cID + ", "
                            ":" + cName + ", "
                            ":" + cPhone + ", "
                            ":" + cCounty + " )");

            Query.bindValue(":" + cID, Row.mID);
            Query.bindValue(":" + cName, Row.mName);
            Query.bindValue(":" + cPhone, Row.mTelefon);
            Query.bindValue(":" + cCounty, Row.mCountryCode);

            if (!Query.exec())
                qDebug() << Query.lastError();
        }

        DB.close();
        Result = true;
    }

    return Result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void MainWindow::show()
{
    if (mAppRole != eAppRole::arNone)
        QMainWindow::show();
}
//-----------------------------------------------------------------------------
