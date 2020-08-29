#include "customtablemodel.h"

#include <mutex>
#include <assert.h>

static std::once_flag ColumnsArrayInit;
std::array<QString, CustomColumns::ccCount> CustomTableModel::mColumnsText;

//-----------------------------------------------------------------------------
// CustomTableModel
//-----------------------------------------------------------------------------
CustomTableModel::CustomTableModel(const std::shared_ptr<iDataSource> inDataSource, QObject *inParent)
    : QAbstractTableModel(inParent),
      mDataSource(inDataSource)
{
    assert(inDataSource != nullptr);
    std::call_once(ColumnsArrayInit, CustomTableModel::initColumnsText); // Единажды инициализируем текст столбцов
}
//-----------------------------------------------------------------------------
int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mDataSource->rowCount();
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
                if (!isCheckableColumn(static_cast<CustomColumns>(index.column()))) // Если это не флаговый столбец
                    Result = mDataSource->getData(index.row(), static_cast<CustomColumns>(index.column())); // Получаем данные напрямую
                else
                    Result = QVariant();

                break;
            } // case Qt::DisplayRole

            case Qt::CheckStateRole: // Проль отображения флага
            {
                if (isCheckableColumn(static_cast<CustomColumns>(index.column()))) // Если это флаговый столбец
                {
                    bool Val = mDataSource->getData(index.row(), static_cast<CustomColumns>(index.column())).toBool(); // Получаем состояние флага
                    Result = Result = (Val) ? Qt::Checked : Qt::Unchecked; // Преобразуем к состоянию Qt
                }
                else
                    Result = QVariant();

                break;
            } // case Qt::CheckStateRole

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
                if (!isCheckableColumn(static_cast<CustomColumns>(index.column()))) // Если это не флаговый столбец
                    Result = mDataSource->setData(index.row(), static_cast<CustomColumns>(index.column()), value); // Редактируем данные
                else
                    Result = false; // Редактирование запрещено

                break;
            }

            case Qt::CheckStateRole: // Роль взведения флага
            {
                if (isCheckableColumn(static_cast<CustomColumns>(index.column()))) // Если это флаговый столбец
                {
                    bool Val = (value == Qt::Checked) ? true : false; // Преобразуем к булю
                    Result = mDataSource->setData(index.row(), static_cast<CustomColumns>(index.column()), Val); // Редактируем данные
                }
                else
                    Result = false; // Взвод флага запрещён

                break;
            }

            default: { Result = false; break; }
        } // switch (role)
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool CustomTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    bool Result = true;

    beginRemoveRows(parent, row, row + count - 1);

    for (int RowIndex = row + count - 1; RowIndex >= row ; --RowIndex) // Удаляем все столбцы СТРОГО снизу вверх
        Result += mDataSource->removeData(RowIndex);

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

    if (isCheckableColumn(static_cast<CustomColumns>(index.column()))) // Если это флаговый столбец
        Result = Result | Qt::ItemFlag::ItemIsUserCheckable; // Разрешаем пользовотелю взводить флаг
    else // Если это не флаговый столбец
        Result = Result | Qt::ItemFlag::ItemIsEditable; // Разрешаем пользователю редактировать текст

    return Result;
}
//-----------------------------------------------------------------------------
bool CustomTableModel::isCheckableColumn(const CustomColumns inCol) const
{
    bool Result = false;

    switch (inCol)
    {   // Для всех флаговыхс толбцов вернём истину
        case CustomColumns::ccHasIntelLisense:
        case CustomColumns::ccHasPlugin:
        case CustomColumns::ccCanCompile:
        {
            Result = true;
            break;
        }

        default: { Result = false; break; }

    } // switch (inCol)

    return Result;
}
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
void CustomTableModel::initColumnsText()
{
    CustomTableModel::mColumnsText[CustomColumns::ccTextEditor] = tr("Редактор");
    CustomTableModel::mColumnsText[CustomColumns::ccFileFormats] = tr("Формат файлов");
    CustomTableModel::mColumnsText[CustomColumns::ccEncoding] = tr("Кодировки");
    CustomTableModel::mColumnsText[CustomColumns::ccHasIntelLisense] = tr("Лицензия Intel");
    CustomTableModel::mColumnsText[CustomColumns::ccHasPlugin] = tr("Поддержка плагинов");
    CustomTableModel::mColumnsText[CustomColumns::ccCanCompile] = tr("Поддержка компиляции");
}
//-----------------------------------------------------------------------------

