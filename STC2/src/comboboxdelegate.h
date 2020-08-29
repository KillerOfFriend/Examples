#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QAbstractItemModel>

//-----------------------------------------------------------------------------
class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:

    /**
     * @brief ComboBoxDelegate - Инициализирующий конструктор
     * @param inParent - Объект предок
     */
    ComboBoxDelegate(QObject *inParent = nullptr);

    /**
     * @brief ~ComboBoxDelegate - Виртуальный деструктор по умолчанию
     * @param inParent - Объект предок
     */
    virtual ~ComboBoxDelegate() override = default;

    /**
     * @brief createEditor - Метод создаст виджет делегата
     * @param parent - Родительский элемент
     * @param option - Визуальные опции
     * @param index - Индекс в моделе данных
     * @return Верёнт указатель на созданый виджет
     */
    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private:

    /**
     * @brief createModel - Метод создаст модель данных для списка делегата
     * @return Вернёт модель данных
     */
    QAbstractItemModel* createModel() const;

    qint32 getCBRow(const QAbstractItemModel* inCBModel, const QModelIndex& inTableIndex) const;

};
//-----------------------------------------------------------------------------

#endif // COMBOBOXDELEGATE_H
