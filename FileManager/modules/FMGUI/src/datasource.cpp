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
QString DataSource::path()
{
    return m_currentDir.path();
}
//-----------------------------------------------------------------------------
void DataSource::setPath(const QString& inPath)
{
    m_currentDir.cd(inPath);

    m_currentDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    fsModel.setDir(m_currentDir);
}
//-----------------------------------------------------------------------------
void DataSource::dirUp()
{
    m_currentDir.cdUp();

    m_currentDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    fsModel.setDir(m_currentDir);
}
//-----------------------------------------------------------------------------
