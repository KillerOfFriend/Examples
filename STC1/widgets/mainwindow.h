#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMenu>
#include <QMainWindow>

//-----------------------------------------------------------------------------
namespace Ui {
class MainWindow;
}
//-----------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *inParent = nullptr);
    ~MainWindow();

private slots:
    void on_actionImportXml_triggered();

    void on_actionImportDB_triggered();

    void on_actionClearTable_triggered();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;

    QMenu mContextMenu; ///< Контекстное меню

    /**
     * @brief initContextMenu - Метод инициализирует контекстное меню
     */
    void initContextMenu();

    /**
     * @brief initTable - Метод инициализирует раблицу
     */
    void initTable();

private slots:

    /**
     * @brief onTriggeredEdit - Слот, реагирующий на пункт контекстного меню "Редактирование"
     */
    void onTriggeredEdit();

    /**
     * @brief onTriggeredDelete - Слот, реагирующий на пункт контекстного меню "Удаление"
     */
    void onTriggeredDelete();
};
//-----------------------------------------------------------------------------

#endif // MAINWINDOW_H
