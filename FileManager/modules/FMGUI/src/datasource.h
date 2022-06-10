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

private:
    QDir m_currentDir = QDir::home();
    FsModel fsModel;

public slots:
    void setPath(const QString& inPath);
    QString path();
    void dirUp();

};
//-----------------------------------------------------------------------------

#endif // DATASOURCE_H
