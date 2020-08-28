#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "customtablemodel.h"
#include "xmldatasource.h"
#include "dbdatasource.h"
#include "uploaddialog.h"

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *inParent) :
    QMainWindow(inParent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initContextMenu();
    initTable();
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
void MainWindow::on_actionImportXml_triggered()
{
    on_actionClearTable_triggered();

    QStringList FilesPaths = QFileDialog::getOpenFileNames(this, tr("Открыть XML"), "", tr("XML (*.xml)"));

    if (!FilesPaths.isEmpty())
    {
        std::shared_ptr<iDataSource> DataSource = std::make_shared<XmlDataSource>(FilesPaths);

        UploadDialog UDialog(this);
        connect(DataSource.get(), &iDataSource::sig_onUpdateProc, &UDialog, &UploadDialog::slot_onUpdateProc);
        connect(DataSource.get(), &iDataSource::sig_onError, &UDialog, &UploadDialog::slot_onError);

        DataSource->update();
        UDialog.exec();

        ui->tableView->setModel(new CustomTableModel(DataSource));
    }
}
//-----------------------------------------------------------------------------
void MainWindow::on_actionImportDB_triggered()
{
    on_actionClearTable_triggered();

    std::shared_ptr<iDataSource> DataSource = std::make_shared<DBDataSource>("SqlLite");

    UploadDialog UDialog(this);
    connect(DataSource.get(), &iDataSource::sig_onUpdateProc, &UDialog, &UploadDialog::slot_onUpdateProc);
    connect(DataSource.get(), &iDataSource::sig_onError, &UDialog, &UploadDialog::slot_onError);

    DataSource->update();
    UDialog.exec();

    ui->tableView->setModel(new CustomTableModel(DataSource));
}
//-----------------------------------------------------------------------------
void MainWindow::on_actionClearTable_triggered()
{
    ui->tableView->setModel(nullptr);
}
//-----------------------------------------------------------------------------
void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    if (ui->tableView->model() && ui->tableView->currentIndex().isValid())
        mContextMenu.popup(ui->tableView->viewport()->mapToGlobal(pos));
}
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
void MainWindow::initContextMenu()
{
    mContextMenu.clear();
    QAction* Action = nullptr;

    Action = new QAction(tr("Редактировать"), this);
    connect(Action, &QAction::triggered, this, &MainWindow::onTriggeredEdit);
    mContextMenu.addAction(Action);

    Action = new QAction(tr("Удалить"), this);
    connect(Action, &QAction::triggered, this, &MainWindow::onTriggeredDelete);
    mContextMenu.addAction(Action);
}
//-----------------------------------------------------------------------------
void MainWindow::initTable()
{
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}
//-----------------------------------------------------------------------------
void MainWindow::onTriggeredEdit()
{
    if (ui->tableView->currentIndex().isValid())
        ui->tableView->edit(ui->tableView->currentIndex());
}
//-----------------------------------------------------------------------------
void MainWindow::onTriggeredDelete()
{
    QModelIndexList Selected = ui->tableView->selectionModel()->selectedIndexes();

    if (!Selected.isEmpty() && ui->tableView->model())
        ui->tableView->model()->removeRows(Selected.front().row(), Selected.size());
}
//-----------------------------------------------------------------------------
