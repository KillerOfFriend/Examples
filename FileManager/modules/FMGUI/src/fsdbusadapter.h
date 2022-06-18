#ifndef FSDBUSADAPTER_H
#define FSDBUSADAPTER_H

#include "dbusfsinterface.h"

//-----------------------------------------------------------------------------
class FsDBusAdapter : public QObject
{
    Q_OBJECT
public:
    FsDBusAdapter(QObject *inParent = nullptr);
    virtual ~FsDBusAdapter() override = default;

    Q_INVOKABLE bool copy(const QString &inPath);
    Q_INVOKABLE bool cut(const QString &inPath);
    Q_INVOKABLE bool paste(const QString &inPath);
    Q_INVOKABLE bool remove(const QString &inPath);

private:
    OrgFooDbusfilemanagerInterface m_qdbusInterface;
};
//-----------------------------------------------------------------------------

#endif // FSDBUSADAPTER_H
