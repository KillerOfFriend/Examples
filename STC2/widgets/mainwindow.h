#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMenu>
#include <QMainWindow>

#include "sqlite.h"
#include "datastorege.h"

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
    eAppRole mAppRole = eAppRole::arNone; ///< Роль приложения

    /**
     * @brief initTable - Метод инициализирует таблицу
     */
    void initTable();

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

};
//-----------------------------------------------------------------------------

#endif // MAINWINDOW_H
