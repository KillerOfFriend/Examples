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

    Q_INVOKABLE void copy(const QString &inPath);
    Q_INVOKABLE void cut(const QString &inPath);
    Q_INVOKABLE void paste(const QString &inPath);
    Q_INVOKABLE void remove(const QString &inPath);

private:
    OrgFooDbusfilemanagerInterface m_qdbusInterface;
};
//-----------------------------------------------------------------------------

#endif // FSDBUSADAPTER_H
