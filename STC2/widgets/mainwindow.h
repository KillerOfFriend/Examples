#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMenu>
#include <QMainWindow>
#include <QItemSelection>

#include "sqlite.h"
#include "datastorege.h"
#include "network.h"

//-----------------------------------------------------------------------------
/**
 * @brief The eAppRole enum - Перечень ролей приложения
 */
enum class eAppRole
{
    arNone,     ///< Роль не определена
    arServer,   ///< Роль - Сервер
    arClient    ///< Роль - Клиент
};
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

    /**
     * @brief initialize - Метод инициализирует данные
     * @return Вернёт рпизнак успешности операции
     */
    bool initialize();

private:
    Ui::MainWindow *ui;

    SqLite mDb; ///< База данных
    std::shared_ptr<DataStorege> mDataStorege = nullptr; ///< Хранилище данных
    std::unique_ptr<NetWork> mNetWork = nullptr; ///< Сетевой функционал

    eAppRole mAppRole = eAppRole::arNone; ///< Роль приложения
    QMenu mContextMenu; ///< Контекстное меню

    /**
     * @brief initTable - Метод инициализирует таблицу
     */
    void initTable();

    /**
     * @brief initContextMenu - Метод инициализирует контекстное меню
     */
    void initContextMenu();

    /**
     * @brief selectAppRole - Метод выберет текущую роль приложения
     * @return Вернёт роль приложения
     */
    eAppRole selectAppRole();

    /**
     * @brief becomeServer - Метод попытается сделать приложение сервером
     * @return Вернёт признак успешности операции
     */
    bool becomeServer();

    /**
     * @brief becomeClient - Метод попытается сделать приложение клиентом
     * @return Вернёт признак успешности операции
     */
    bool becomeClient();


public slots:

    /**
     * @brief show - Слот выведет окно формы
     */
    void show();

private slots:

    void slot_onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_actionEdit_triggered();
    void on_actionAddRowBefore_triggered();
    void on_actionAddRowAfter_triggered();
    void on_actionRemoveRow_triggered();
};
//-----------------------------------------------------------------------------

#endif // MAINWINDOW_H
