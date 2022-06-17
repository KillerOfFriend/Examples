#ifndef DBUS_FSHELPER_H
#define DBUS_FSHELPER_H

#include <QObject>
#include <QtDBus/QtDBus>

#include "dbus_defines.hpp"

//-----------------------------------------------------------------------------
///
/// \brief The efsAcrionType enum - Перечеслиение действий над объектами файловой системы
///
enum class efsAcrionType
{
    atUnknown = 0,  ///< Тип действия не орпределён
    atCopy = 1,     ///< Копирование объекта
    atMove = 2      ///< Перемещение объекта
};
//-----------------------------------------------------------------------------
///
/// \brief The fsAction struct - Струкрута, описывающая действие над объектом файловой системы
///
struct fsAction
{
    fsAction() = default;
    ~fsAction() = default;

    efsAcrionType m_actionType; ///< Тип действия
    QString m_objectPath;       ///< Путь к объекту
};
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

};
//-----------------------------------------------------------------------------

#endif // DBUS_FSHELPER_H
