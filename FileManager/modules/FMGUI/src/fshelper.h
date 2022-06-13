#ifndef FsHelper_H
#define FsHelper_H

#include <QObject>
#include <QDir>

//-----------------------------------------------------------------------------
///
/// \brief The FsHelper class - Вспомогательный класс для управления файловой системой
///
class FsHelper : public QObject
{
    Q_OBJECT
public:

    ///
    /// \brief FsHelper - Конструктор по умолчанию
    /// \param inParent - Указатель на объект-предок
    ///
    explicit FsHelper(QObject *inParent = nullptr);

    ///
    /// \brief ~FsHelper - Перегруженный деструктор по умолчанию
    ///
    virtual ~FsHelper() override = default;

    // Запретим копирование и перемещение
    FsHelper(const FsHelper&) = delete;
    FsHelper(const FsHelper&&) = delete;

    FsHelper & operator=(const FsHelper&) = delete;
    FsHelper & operator=(const FsHelper&&) = delete;

    ///
    /// \brief copy - Метод инициирует копирование объекта файловой системы
    /// \param inPath - Путь к копируемому объекту
    ///
    Q_INVOKABLE void copy(const QString inPath);

    ///
    /// \brief cut - Метод инициирует "вырезание" объекта файловой системы
    /// \param inPath - Путь к вырезаемому объекту
    ///
    Q_INVOKABLE void cut(const QString inPath);

    ///
    /// \brief paste - Метод выполнит вставку объекта файловой системы
    /// \param inDir - Путь к директории назначения
    ///
    Q_INVOKABLE void paste(const QDir inDir);

    ///
    /// \brief remove - Метод выполнит удаление объекта файловой системы
    /// \param inPath - Genm r elfkztvjve j,]trne
    ///
    Q_INVOKABLE void remove(const QString inPath);

};
//-----------------------------------------------------------------------------

#endif // FsHelper_H
