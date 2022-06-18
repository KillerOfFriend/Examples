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

    ///
    /// \brief DataSource - Конструктор по умолчанию
    /// \param inParent - Указатель на объект-предок
    ///
    explicit DataSource(QObject *inParent = nullptr);

    ///
    /// \brief ~DataSource - Перегруженный деструктор по умолчанию
    ///
    virtual ~DataSource() override = default;

    ///
    /// \brief model - Метод вернёт ссылку на модель данных
    /// \return Вернёт ссылку на модель данных
    ///
    FsModel& model();

    ///
    /// \brief setPath - Метод задаст текущий путь
    /// \param inPath - Новое значение текущего пути
    ///
    Q_INVOKABLE void setPath(const QString& inPath);

    ///
    /// \brief path - Метод вернёт текущий путь
    /// \return Вернёт текущий путь
    ///
    Q_INVOKABLE QString path() const;

    ///
    /// \brief dirUp - Метод "поднимет" текущий путь на уровень выше
    ///
    Q_INVOKABLE void dirUp();

private:
    QDir m_currentDir;  ///< Текущая директория
    FsModel fsModel;    ///< Модель представления данных

signals:
    ///
    /// \brief pathChenged - Сигнал об изменении текущего пути
    /// \param inNewPath - Новое значение текущего пути
    ///
    void pathChenged(QString inNewPath);

};
//-----------------------------------------------------------------------------

#endif // DATASOURCE_H
