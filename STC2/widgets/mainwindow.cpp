#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "comboboxdelegate.h"
#include "customtablemodel.h"

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *inParent) :
    QMainWindow(inParent),
    ui(new Ui::MainWindow),
    mDb(SqLite("SqLite", "STC2"))
{
    ui->setupUi(this);

    initTable();
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;

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
        mDataStorege = std::make_shared<DataStorege>(mDb.loadFromDB()); // Инициализируем из БД
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


//-----------------------------------------------------------------------------
void MainWindow::show()
{
    if (mAppRole != eAppRole::arNone)
        QMainWindow::show();
}
//-----------------------------------------------------------------------------
