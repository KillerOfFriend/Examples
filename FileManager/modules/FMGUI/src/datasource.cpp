#include "datasource.h"

//-----------------------------------------------------------------------------
DataSource::DataSource(QObject *inParent) : QObject(inParent)
{

}
//-----------------------------------------------------------------------------
FsModel& DataSource::model()
{
    return fsModel;
}
//-----------------------------------------------------------------------------
QString DataSource::path() const
{
    return m_currentDir.path();
}
//-----------------------------------------------------------------------------
void DataSource::setPath(const QString& inPath)
{
    if (inPath.isEmpty())
        return;

    m_currentDir.cd(inPath);

    m_currentDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    fsModel.setDir(m_currentDir);

    pathChenged(m_currentDir.path());
}
//-----------------------------------------------------------------------------
void DataSource::dirUp()
{
    if (!m_currentDir.cdUp())
        return;

    m_currentDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    fsModel.setDir(m_currentDir);

    pathChenged(m_currentDir.path());
}
//-----------------------------------------------------------------------------
