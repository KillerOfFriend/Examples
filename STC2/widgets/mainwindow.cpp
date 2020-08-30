#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "comboboxdelegate.h"
#include "customtablemodel.h"
#include "tcpserver.h"
#include "tcpclient.h"

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *inParent) :
    QMainWindow(inParent),
    ui(new Ui::MainWindow),
    mDb(SqLite("SqLite", "STC2"))
{
    ui->setupUi(this);

    mDataStorege = std::make_shared<DataStorege>(); // Инициализируем источник данных

    initTable();
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;

    if (mNetWork) // Останавливаем сеть
        mNetWork->stop();

    if (mAppRole == eAppRole::arServer && mDataStorege)
        mDb.saveToDB(mDataStorege->dump());
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
        mDataStorege->init(mDb.loadFromDB()); // Инициализируем из БД
        setWindowTitle("Server");
    }
    else
    {
        if (becomeClient()) // Пытаемся стать клиентом
        {
            Result = eAppRole::arClient;
            setWindowTitle("Client");
        }
        else
        {
            Result = eAppRole::arNone; // Жизнь прошла зря...
            mDataStorege = nullptr;
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool MainWindow::becomeServer()
{
    mNetWork = std::make_unique<TcpServer>(QHostAddress::Any, 7485, mDataStorege);
    bool Result = mNetWork->start(); // Пытаемся запустить сервер

    if (!Result) // Запуск не прошёл
        mNetWork = nullptr;

    return Result;
}
//-----------------------------------------------------------------------------
bool MainWindow::becomeClient()
{
    mNetWork = std::make_unique<TcpClient>(QHostAddress::LocalHost, 7485, mDataStorege);
    bool Result = mNetWork->start(); // Пытаемся запустить подключить клиент

    if (!Result) // Запуск не прошёл
        mNetWork = nullptr;

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
