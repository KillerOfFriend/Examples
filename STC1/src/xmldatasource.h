#ifndef XMLDATASOURCE_H
#define XMLDATASOURCE_H

#include <atomic>
#include <thread>
#include <mutex>

#include <QStringList>
#include <QByteArray>
#include <QFile>

#include "threadeddatasource.h"

//-----------------------------------------------------------------------------
typedef std::array<bool, CustomColumns::ccCount> ParamArray;
//-----------------------------------------------------------------------------
/**
 * @brief The XmlFileInfo struct - Информация о файлах
 */
struct XmlFileData : public BaseData
{
    XmlFileData() = default;
    XmlFileData(const QString& mPath) : BaseData(), mPath(mPath) {}
    virtual ~XmlFileData() override = default;

    QString mPath;          ///< Путь к файлу
    QByteArray mHash;       ///< Хеш файла
};
//-----------------------------------------------------------------------------
/**
 * @brief The XmlDataSource class - Класс описывает источник данных из группы XML файлов
 */
class XmlDataSource : public aThreadedDataSource
{
public:

    /**
     * @brief XmlDataSource - Инициализирующий конструктор
     * @param inFilesPaths - Пути к файлам
     */
    XmlDataSource(const QStringList& inFilesPaths);

    /**
     * @brief ~XmlDataSource - Виртуальный деструктор
     */
    virtual ~XmlDataSource() override = default;

private:

    /**
     * @brief updateInThread - Метод загрузки данных, выполняемый в отдельном потоке
     */
    virtual void updateInThread() override;

    /**
     * @brief uploadInThread - Метод выгрузки данных, выполняемый в отдельном потоке
     */
    virtual void uploadInThread() override;

    /**
     * @brief getFileHash - Метод вернёт хешсумму указанного файла
     * @param inFilePath - Путь к обрабатываемому файлу
     * @return Вернёт хешсумму указанного файла
     */
    QByteArray getFileHash(const QString& inFilePath) const;

    /**
     * @brief readXML - Метод считает содержимое файла
     * @param inFilPath - Путь к читаемому файлу
     * @param outData - Приёмник данных
     * @return Вернёт признак ошибки
     */
    std::error_code readXML(const QString& inFilPath, CustomData& outData);

    /**
     * @brief writeXML - Метод запишет данные в файл
     * @param inFilPath - Путь к записываемому файлу
     * @param outDat - Записываемые даннеые
     * @return Вернёт признак ошибки
     */
    std::error_code writeXML(const QString& inFilPath, CustomData& outDat) const;

    /**
     * @brief parseXml - Метод разбора Json
     * @param inXmlFile - Открытый файл
     * @param outErrorCode - Признак ошибки
     * @return Вернёт разобранные данные
     */
    CustomData parseXml(QFile& inXmlFile, std::error_code& outErrorCode) const;

    /**
     * @brief checkParams - Сетод проверит наличие всех параметров после разбора
     * @param inParam - Флаги параметров
     * @return Вернёт признак ошибки
     */
    std::error_code checkParams(const ParamArray& inParam) const;

};
//-----------------------------------------------------------------------------

#endif // XMLDATASOURCE_H
