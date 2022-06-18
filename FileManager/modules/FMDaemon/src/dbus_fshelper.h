#ifndef DBUS_FSHELPER_H
#define DBUS_FSHELPER_H

#include <memory>

#include <QObject>
#include <QtDBus/QtDBus>

#include "dbus_defines.hpp"
#include "fsaction.h"

namespace fs
{
//-----------------------------------------------------------------------------
class DBusFsHelper : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_SERVICE_NAME)
public:

    explicit DBusFsHelper(QObject *inParent = nullptr);
    virtual ~DBusFsHelper() override = default;

public slots:

    bool copyObject(const QString& inPath);
    bool cutObject(const QString& inPath);
    bool pasteObject(const QString& inPath);
    bool deleteObject(const QString& inPath);

private:

    std::unique_ptr<AbstractFsAction> m_buffAction;

};
//-----------------------------------------------------------------------------
} // namespace fs

#endif // DBUS_FSHELPER_H
