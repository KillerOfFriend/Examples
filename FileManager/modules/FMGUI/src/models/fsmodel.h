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
    enum eColumns { cName = 0, cType = 1, cSize = 2, cLastChangeDate = 3, cCount };
    enum eRoles
    {
        rNameRole =             Qt::UserRole + FsModel::cName,
        rTypeRole =             Qt::UserRole + FsModel::cType,
        rSizeRole =             Qt::UserRole + FsModel::cSize,
        rLastChangeDateRole =   Qt::UserRole + FsModel::cLastChangeDate
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
    static const QHash<int, QByteArray> m_roles;                ///< Роли

    QFileInfoList m_dirContent;                                 ///< Содержимое текущей директории

    ///
    /// \brief initColumnsText - Метод инициализирует текст столбцов
    ///
    static void initColumnsText();
};
//-----------------------------------------------------------------------------

#endif // FSMODEL_H
