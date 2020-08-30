#include "customtablemodel.h"

#include <mutex>
#include <assert.h>

static std::once_flag ColumnsArrayInit;
std::array<QString, CustomColumns::ccCount> CustomTableModel::mColumnsText;

//-----------------------------------------------------------------------------
// CustomTableModel
//-----------------------------------------------------------------------------
CustomTableModel::CustomTableModel(const std::shared_ptr<DataStorege> inDataStorege, QObject *inParent)
    : QAbstractTableModel(inParent),
      mDataStorege(inDataStorege)
{
    assert(mDataStorege != nullptr);
    std::call_once(ColumnsArrayInit, CustomTableModel::initColumnsText); // Единажды инициализируем текст столбцов

    // Обработка инициализации
    connect(mDataStorege.get(), &DataStorege::sig_onStartRestart, this, &CustomTableModel::beginResetModel);
    connect(mDataStorege.get(), &DataStorege::sig_onEndRestart, this, &CustomTableModel::endResetModel);
}
//-----------------------------------------------------------------------------
int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mDataStorege->getRowCount();
}
//-----------------------------------------------------------------------------
int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return CustomColumns::ccCount;
}
//-----------------------------------------------------------------------------
QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    QVariant Result {};

    if (!index.isValid()) // Отсекаем невалидные индексы
        Result = QVariant();
    else // Обрабатываем запрос данных на отображение
    {
        switch (role)
        {
            case Qt::DisplayRole: // Роль отображения текста
            {
                Result = mDataStorege->getData(index.row(), static_cast<CustomColumns>(index.column()));
                break;
            } // case Qt::DisplayRole

            default: { Result = QVariant(); break; }

        } // switch (role)
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool Result = false;

    if (!index.isValid()) // Отсекаем невалидные индексы
        Result = false;
    else // Обрабатываем изменение данных
    {
        switch (role) // Проверяем роль
        {
            case Qt::EditRole: // Роль редактирования текста
            {
                Result = mDataStorege->setData(index.row(), static_cast<CustomColumns>(index.column()), value);
                break;
            }

            default: { Result = false; break; }
        } // switch (role)
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool CustomTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    bool Result = true;

    beginInsertRows(parent, row, row + count - 1);

    for (int RowIndex = row; RowIndex < row + count; ++RowIndex)
        Result += mDataStorege->insertRow(RowIndex);

    endInsertRows();

    return Result;
}
//-----------------------------------------------------------------------------
bool CustomTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    bool Result = true;

    beginRemoveRows(parent, row, row + count - 1);

    for (int RowIndex = row + count - 1; RowIndex >= row ; --RowIndex) // Удаляем все столбцы СТРОГО снизу вверх
        Result += mDataStorege->removeRow(RowIndex);

    endRemoveRows();

    return Result;
}
//-----------------------------------------------------------------------------
QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractTableModel::headerData(section, orientation, role);
    else
    { // Обрабатываем горизонтальную шапку на отображение текста
        if (section < 0 || section >= CustomColumns::ccCount) // Проверяем ОДЗ
            return QVariant();
        else
            return mColumnsText[section]; // Возврашаем текст ячейки
    }
}
//-----------------------------------------------------------------------------
Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags Result = QAbstractTableModel::flags(index);

    if (index.column() != CustomColumns::ccID) // Запрещаем редактировать идентификатор
        Result |= Qt::ItemFlag::ItemIsEditable;

    return Result;
}
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
void CustomTableModel::initColumnsText()
{
    CustomTableModel::mColumnsText[CustomColumns::ccID] = tr("ID");
    CustomTableModel::mColumnsText[CustomColumns::ccName] = tr("Имя");
    CustomTableModel::mColumnsText[CustomColumns::ccTelefon] = tr("Телефон");
    CustomTableModel::mColumnsText[CustomColumns::ccCountry] = tr("Страна");
}
//-----------------------------------------------------------------------------

