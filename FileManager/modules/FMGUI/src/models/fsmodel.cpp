#include "fsmodel.h"

#include <mutex>

#include <QIcon>
#include <QDateTime>

//-----------------------------------------------------------------------------
static std::once_flag ColumnsArrayInit; /// < Флаг инициализации текста столбцов
std::array<QString, FsModel::eColumns::cCount> FsModel::m_columnsText;
//-----------------------------------------------------------------------------
FsModel::FsModel(QObject* inParent) : QAbstractTableModel(inParent)
{
    std::call_once(ColumnsArrayInit, FsModel::initColumnsText); // Единажды инициализируем текст столбцов
}
//-----------------------------------------------------------------------------
int FsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_currentDir.count();
}
//-----------------------------------------------------------------------------
int FsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnsText.size();
}
//-----------------------------------------------------------------------------
QHash<int, QByteArray> FsModel::roleNames() const
{
    return {
        // Роли отображения
        { FsModel::rNameRole, "name"},
        { FsModel::rTypeRole, "type"},
        { FsModel::rSizeRole, "size"},
        { FsModel::rLastChangeDateRole, "lastchangedate"},
        // Служебные роли
        { FsModel::rObjectPathRole, "objectpath"},

        { Qt::DecorationRole, "imageURL"}
    };
}
//-----------------------------------------------------------------------------
QVariant FsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( (index.row() < 0 || index.row() >= rowCount()) || (index.column() < 0 || index.column() >= columnCount()) )
        return QVariant();

    QVariant Result = QVariant();

    const QFileInfo& ItemInfo = m_currentDir.entryInfoList().at(index.row());

    switch (role)
    {
        // Роли отображения
        case rNameRole:             { Result = ItemInfo.fileName(); break; }
        case rTypeRole:             { Result = (ItemInfo.isDir()) ? "Dir" : ItemInfo.suffix(); break; }
        case rSizeRole:             { Result = (ItemInfo.isDir()) ? QVariant() : ItemInfo.size(); break; }
        case rLastChangeDateRole:   { Result = ItemInfo.lastModified().toString("HH:mm:ss MM-dd.MM.yyyy"); break; }

        // Служебные роли
        case rObjectPathRole:       { Result = ItemInfo.absoluteFilePath(); break; }
        case Qt::DecorationRole:
        {
            Result = ItemInfo.isDir() ? "qrc:/img/directory.png" : "qrc:/img/file.png";
            break;
        } // case Qt::DecorationRole:

        default: { Result = QVariant(); break; }
    } // switch (role)

    return Result;
}
//-----------------------------------------------------------------------------
QVariant FsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( section < 0 || section >= columnCount() )
        return QVariant();

    QVariant Result = QVariant();

    if (role == Qt::DisplayRole && orientation == Qt::Orientation::Horizontal)
        Result = m_columnsText[section];
    else
        Result = QVariant();

    return Result;
}
//-----------------------------------------------------------------------------
void FsModel::setDir(const QDir& inDir)
{
    layoutAboutToBeChanged();
    m_currentDir = inDir;
    layoutChanged();
}
//-----------------------------------------------------------------------------
void FsModel::initColumnsText()
{
    m_columnsText[cName] =              tr("Название");
    m_columnsText[cType] =              tr("Тип");
    m_columnsText[cSize] =              tr("Размер");
    m_columnsText[cLastChangeDate] =    tr("Дата последнего изменения");
}
//-----------------------------------------------------------------------------
