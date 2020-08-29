#include "comboboxdelegate.h"

#include <QComboBox>
#include <QStandardItemModel>

#include "tools.h"

#define CodeRole Qt::UserRole

//-----------------------------------------------------------------------------
ComboBoxDelegate::ComboBoxDelegate(QObject *inParent) : QItemDelegate(inParent)
{

}
//-----------------------------------------------------------------------------
QWidget* ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    return new QComboBox(parent);
}
//-----------------------------------------------------------------------------
void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = dynamic_cast<QComboBox*>(editor);

    if (!comboBox)
        return;

    QAbstractItemModel* CMModel = createModel(); // Создаём модель данных для комбобокса
    comboBox->setModel(CMModel);

    qint32 RowIndex = getCBRow(CMModel, index);
    comboBox->setCurrentIndex(RowIndex); // Выбираем в комбобоксе строку, соответствующую текущим данным в ячейке талице
}
//-----------------------------------------------------------------------------
void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = dynamic_cast<QComboBox*>(editor);

    if (!comboBox || !model || !index.isValid())
        return;

    QVariant CurrentData = comboBox->currentData(CodeRole); // Получаем код страны из данных выбранных в комбобоксе

    if (CurrentData.isValid())
        model->setData(index, CurrentData); // Задаём данные в табличную модель
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
QAbstractItemModel* ComboBoxDelegate::createModel() const
{
    QStandardItem* NewItem = nullptr;
    QStandardItemModel* Model = new QStandardItemModel();

    /*
     * Создаём айтемы модели, содержищие название страны (для отображения)
     * И коды стран для присвоения табличной моделе
     */

    NewItem = new QStandardItem(tools::countryText(eCountry::cUSA));
    NewItem->setData(eCountry::cUSA, CodeRole);
    Model->appendRow(NewItem);

    NewItem = new QStandardItem(tools::countryText(eCountry::cRussia));
    NewItem->setData(eCountry::cRussia, CodeRole);
    Model->appendRow(NewItem);

    NewItem = new QStandardItem(tools::countryText(eCountry::cUkraine));
    NewItem->setData(eCountry::cUkraine, CodeRole);
    Model->appendRow(NewItem);

    return Model;
}
//-----------------------------------------------------------------------------
qint32 ComboBoxDelegate::getCBRow(const QAbstractItemModel* inCBModel, const QModelIndex& inTableIndex) const
{
    qint32 Result = -1;

    if (inCBModel && inTableIndex.isValid()) // Если указатель на модель комбобокса и индекс таблици валидны
        for (qint32 Row = 0; Row < inCBModel->rowCount(); ++Row) // Перебераем все строки модели комбобокса
        {
            QModelIndex CbIndex = inCBModel->index(Row, 0); // Гененрируем индекс
            // И ищим валидный индекс с данными отображения идентичными данным отображения в индексе таблицы
            if (CbIndex.isValid() && (CbIndex.data(Qt::DisplayRole).toString() == inTableIndex.data(Qt::DisplayRole).toString()) )
            {
                Result = Row; // Запоминаем строку
                break; // Прерываем поиск
            }
        }

    return Result;
}
//-----------------------------------------------------------------------------
