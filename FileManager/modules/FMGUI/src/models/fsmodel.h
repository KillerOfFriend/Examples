#ifndef FSMODEL_H
#define FSMODEL_H

#include <array>

#include <QDir>
#include <QStringList>
#include <QAbstractTableModel>

//-----------------------------------------------------------------------------
///
/// \brief The FsModel class - Класс описывает модель содержимого директории
///
class FsModel : public QAbstractTableModel
{
public:
    enum eColumns ///< Перечень столбцов
    {
        cName = 0,              ///< Имя объекта
        cType = 1,              ///< Тип объекта
        cSize = 2,              ///< Размер объекта
        cLastChangeDate = 3,    ///< Дата последнего изменения объекта

        cCount                  ///< Счётчик столбцов
    };

    enum eRoles                 ///< Роли доступа к данным
    {
        // Роли отображения
        rNameRole =             Qt::UserRole + FsModel::cName,              ///< Роль имени объекта
        rTypeRole =             Qt::UserRole + FsModel::cType,              ///< Роль типа объекта
        rSizeRole =             Qt::UserRole + FsModel::cSize,              ///< Роль размера объекта
        rLastChangeDateRole =   Qt::UserRole + FsModel::cLastChangeDate,    ///< Роль даты последнего изменения объекта

        // Служебные роли
        rObjectPathRole =       Qt::UserRole + FsModel::cCount + 1          ///< Роль полного пути к объекту
    };

    FsModel(QObject* inParent = nullptr);
    virtual ~FsModel() override = default;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QHash<int, QByteArray> roleNames() const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    ///
    /// \brief setDir - Метод задаст текущую директорию
    /// \param inDir - Новое значение текущей директории
    ///
    void setDir(const QDir& inDir);

private:
    static std::array<QString, eColumns::cCount> m_columnsText; ///< Текстовые наименования столбцов
    QDir m_currentDir;                                          ///< Текущая директория

    ///
    /// \brief initColumnsText - Метод инициализирует текст столбцов
    ///
    static void initColumnsText();
};
//-----------------------------------------------------------------------------

#endif // FSMODEL_H
