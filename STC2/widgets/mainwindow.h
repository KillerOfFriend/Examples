#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMenu>
#include <QMainWindow>
#include <QSqlDatabase>

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

    std::shared_ptr<DataStorege> mDataStorege = nullptr; ///< Хранилище данных

    const QString mDbFileName = "SqLite"; ///< Имя файла БД
    const QString mDbConnectionName = "STC2"; ///< Имя соединения БД

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



    /**
     * @brief getDataBaseConnection - Метод вернёт соединение с БД
     * @return Вернёт соединение с БД
     */
    QSqlDatabase getDataBaseConnection() const;

    /**
     * @brief createDbTable - Метод создасть таблицу в БД
     * @return Вернёт признак успешности операции
     */
    bool createDbTable() const;

    /**
     * @brief initDbTable - Метод инициализирует таблицу бд если необходимо
     * @return Вернёт признак успешности операции
     */
    bool initDbTable() const;

    /**
     * @brief loadFromDB - Метод загрузит данные из БД
     * @return Вернёт перечень загруженых данных
     */
    std::vector<CustomData> loadFromDB();

    /**
     * @brief saveToDB - Метод выгрузит данные в БД
     * @param inData - Перечень выгружаемых данных
     * @return Вернёт признак успешности операции
     */
    bool saveToDB(const std::vector<CustomData>& inData) const;

public slots:

    /**
     * @brief show - Слот выведет окно формы
     */
    void show();

};
//-----------------------------------------------------------------------------

#endif // MAINWINDOW_H
