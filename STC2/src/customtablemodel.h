#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <memory>
#include <array>

#include <QAbstractTableModel>

#include "types.h"
#include "datastorege.h"

//-----------------------------------------------------------------------------
/**
 * @brief The CustomTableModel class - Класс описывает модель данных
 */
class CustomTableModel : public QAbstractTableModel
{
public:

    CustomTableModel(const std::shared_ptr<DataStorege> inDataStorege, QObject *inParent = nullptr);
    virtual ~CustomTableModel() override = default;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

protected:

    const std::shared_ptr<DataStorege> mDataStorege = nullptr;          ///< Хранилище данных
    static std::array<QString, CustomColumns::ccCount> mColumnsText;    ///< Контейнер с текстом столбцов

    /**
     * @brief initColumnsText - Метод инициализирует текст столбцов
     */
    static void initColumnsText();

};
//-----------------------------------------------------------------------------

#endif // CUSTOMTABLEMODEL_H
