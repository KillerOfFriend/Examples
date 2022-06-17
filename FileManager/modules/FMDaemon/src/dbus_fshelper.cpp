#include "dbus_fshelper.h"

#include <QDir>

//-----------------------------------------------------------------------------
DBusFsHelper::DBusFsHelper(QObject *inParent) : QObject(inParent)
{

}
//-----------------------------------------------------------------------------
bool DBusFsHelper::copyObject(const QString& inPath)
{
    return true;
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::cutObject(const QString& inPath)
{
   return true;
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::pasteObject(const QString& inPath)
{
    return true;
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::deleteObject(const QString& inPath)
{
    return true;
}
//-----------------------------------------------------------------------------
