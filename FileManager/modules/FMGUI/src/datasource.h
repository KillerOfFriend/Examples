#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QDir>
#include <QObject>

#include "models/fsmodel.h"

//-----------------------------------------------------------------------------
class DataSource : public QObject
{
    Q_OBJECT
public:
    DataSource(QObject *inParent = nullptr);
    virtual ~DataSource() override = default;

    FsModel& model();

    Q_INVOKABLE void setPath(const QString& inPath);
    Q_INVOKABLE QString path();
    Q_INVOKABLE void dirUp();

private:
    QDir m_currentDir;
    FsModel fsModel;

signals:
    void pathChenged(QString inNewPath);

};
//-----------------------------------------------------------------------------

#endif // DATASOURCE_H
