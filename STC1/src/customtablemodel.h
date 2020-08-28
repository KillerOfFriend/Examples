#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <memory>
#include <vector>
#include <array>

#include <QAbstractTableModel>

#include "datasource.h"
#include "types.h"

//-----------------------------------------------------------------------------
/**
 * @brief The CustomTableModel class - Класс описывает модель данных
 */
class CustomTableModel : public QAbstractTableModel
{
public:

    CustomTableModel(const std::shared_ptr<iDataSource> inDataSource, QObject *inParent = nullptr);
    virtual ~CustomTableModel() override = default;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

protected:

    std::shared_ptr<iDataSource> mDataSource = nullptr; ///< Источник данных
    static std::array<QString, CustomColumns::ccCount> mColumnsText; ///< Контейнер с текстом столбцов

    /**
     * @brief initColumnsText - Метод инициализирует текст столбцов
     */
    static void initColumnsText();

    /**
     * @brief isCheckableColumn - Метод проверит является ли столбец флаговым
     * @param inCol - Столбец
     * @return Вернёт признак того, что столбец является флаговым
     */
    bool isCheckableColumn(const CustomColumns inCol) const;

};
//-----------------------------------------------------------------------------

#endif // CUSTOMTABLEMODEL_H
