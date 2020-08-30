#include "network.h"

#include <cassert>

#include <QDataStream>
#include <QDebug>

#include <tools.h>

//-----------------------------------------------------------------------------
NetWork::NetWork(const std::shared_ptr<DataStorege> inDataStorege, QObject *inParent)
    : QObject(inParent),
      mDataStorege(inDataStorege)
{
    assert(mDataStorege != nullptr);
    connectDataStorege();
}
//-----------------------------------------------------------------------------
void NetWork::read(QByteArray inData)
{
    QDataStream Stream(&inData, QIODevice::ReadOnly);
    ePackageType Type;

    Stream >> Type;
    qDebug() << "Recieve: "  << inData.size();

    switch (Type)
    {
        case ePackageType::ptInit:
        {
            onInit(inData);
            break;
        }

        case ePackageType::ptEdit:
        {
            quint64 Row;
            CustomColumns Col;
            QVariant Data;

            Stream >> Row;
            Stream >> Col;
            Stream >> Data;

            disconnectDataStorege();
            mDataStorege->setData(Row, Col, Data, true);
            connectDataStorege();

            break;
        };

        case ePackageType::ptInsert:
        {
            quint64 Row;
            Stream >> Row;

            disconnectDataStorege();
            mDataStorege->insertRow(Row);
            connectDataStorege();

            break;
        }

        case ePackageType::ptRemove:
        {
            quint64 Row;
            Stream >> Row;

            disconnectDataStorege();
            mDataStorege->removeRow(Row);
            connectDataStorege();

            break;
        }
    }
}
//-----------------------------------------------------------------------------
void NetWork::connectDataStorege()
{
    if (!mDataStorege)
        return;

    connect(mDataStorege.get(), &DataStorege::sig_onSetData, this, &NetWork::slot_onSetData);
    connect(mDataStorege.get(), &DataStorege::sig_onInsertRow, this, &NetWork::slot_onInsertRow);
    connect(mDataStorege.get(), &DataStorege::sig_onRemoveRow, this, &NetWork::slot_onRemoveRow);
}
//-----------------------------------------------------------------------------
void NetWork::disconnectDataStorege()
{
    if (!mDataStorege)
        return;

    disconnect(mDataStorege.get(), &DataStorege::sig_onSetData, this, &NetWork::slot_onSetData);
    disconnect(mDataStorege.get(), &DataStorege::sig_onInsertRow, this, &NetWork::slot_onInsertRow);
    disconnect(mDataStorege.get(), &DataStorege::sig_onRemoveRow, this, &NetWork::slot_onRemoveRow);
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
void NetWork::slot_onSetData(quint64 inRow, CustomColumns inCol, QVariant inData)
{
    QByteArray Data;
    QDataStream Stream(&Data, QIODevice::WriteOnly);
    Stream << ePackageType::ptEdit << inRow << inCol << inData;
    write(Data);
}
//-----------------------------------------------------------------------------
void NetWork::slot_onInsertRow(quint64 inRow)
{
    QByteArray Data;
    QDataStream Stream(&Data, QIODevice::WriteOnly);
    Stream << ePackageType::ptInsert << inRow;
    write(Data);
}
//-----------------------------------------------------------------------------
void NetWork::slot_onRemoveRow(quint64 inRow)
{
    QByteArray Data;
    QDataStream Stream(&Data, QIODevice::WriteOnly);
    Stream << ePackageType::ptRemove << inRow;
    write(Data);
}
//-----------------------------------------------------------------------------
