#include "threadeddatasource.h"

//-----------------------------------------------------------------------------
aThreadedDataSource::aThreadedDataSource(QObject *inParent) : iDataSource(inParent)
{
    std::atomic_init(&mIsReading, false);
    std::atomic_init(&mIsWriteing, false);
}
//-----------------------------------------------------------------------------
aThreadedDataSource::~aThreadedDataSource()
{
    if (mReadThread.joinable())
        mReadThread.join();

    if (mWriteThread.joinable())
        mWriteThread.join();
}
//-----------------------------------------------------------------------------
std::size_t aThreadedDataSource::rowCount() const
{
    return mDataStorage.size();
}
//-----------------------------------------------------------------------------
QVariant aThreadedDataSource::getData(const std::size_t inRow, const CustomColumns inCol)
{
    QVariant Result;

    if (inRow < mDataStorage.size() && inCol < CustomColumns::ccCount)
    {
//        update();

        std::lock_guard<std::mutex> lg(mDataDefender);

        switch (inCol)
        {
            case CustomColumns::ccTextEditor:       { Result = mDataStorage[inRow]->mData.mTextEditor; break; }
            case CustomColumns::ccFileFormats:      { Result = mDataStorage[inRow]->mData.mFileFormats; break; }
            case CustomColumns::ccEncoding:         { Result = mDataStorage[inRow]->mData.mEncoding; break; }
            case CustomColumns::ccHasIntelLisense:  { Result = mDataStorage[inRow]->mData.mHasIntelLisense; break; }
            case CustomColumns::ccHasPlugin:        { Result = mDataStorage[inRow]->mData.mHasPlugin; break; }
            case CustomColumns::ccCanCompile:       { Result = mDataStorage[inRow]->mData.mCanCompile; break; }

            default:  { Result = QVariant(); break; }
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool aThreadedDataSource::setData(const std::size_t inRow, const CustomColumns inCol, const QVariant& inData)
{
    bool Result = false;

    if (inRow < mDataStorage.size() && inCol < CustomColumns::ccCount) // Существуюая строка
    {
        Result = true;

        {
            std::lock_guard<std::mutex> lg(mDataDefender);

            switch (inCol) // Подбираем столбец
            {
                case CustomColumns::ccTextEditor:       { mDataStorage[inRow]->mData.mTextEditor = inData.toString(); break; }
                case CustomColumns::ccFileFormats:      { mDataStorage[inRow]->mData.mFileFormats = inData.toString(); break; }
                case CustomColumns::ccEncoding:         { mDataStorage[inRow]->mData.mEncoding = inData.toString(); break; }
                case CustomColumns::ccHasIntelLisense:  { mDataStorage[inRow]->mData.mHasIntelLisense = inData.toBool(); break; }
                case CustomColumns::ccHasPlugin:        { mDataStorage[inRow]->mData.mHasPlugin = inData.toBool(); break; }
                case CustomColumns::ccCanCompile:       { mDataStorage[inRow]->mData.mCanCompile = inData.toBool(); break; }

                default:  { Result = false; break; }
            }

            if (Result) // Если данные изменены
                mDataStorage[inRow]->mDataModified = true;
        }

        upload(); // Выгружаем
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool aThreadedDataSource::removeData(const std::size_t inRow)
{
    bool Result = false;

    if (inRow < mDataStorage.size()) // Существуюая строка
    {
        std::lock_guard<std::mutex> lg(mDataDefender);
        auto Pos = mDataStorage.begin();
        std::advance(Pos, inRow);
        mDataStorage.erase(Pos);
        Result = true;
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool aThreadedDataSource::update()
{
    bool Result = false;

    if (!mIsReading) // Чтение не идёт
    {
        mIsReading = true;

        if (mReadThread.joinable()) // Если поток на этапе завершения
            mReadThread.join(); // Страхуемся

        mReadThread = std::thread(&aThreadedDataSource::startUpdateInThread, this); // Создаём поток
        Result = mReadThread.joinable();
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool aThreadedDataSource::upload()
{
    bool Result = false;

    if (!mIsWriteing) // Запись не идёт
    {
        mIsWriteing = true;

        if (mWriteThread.joinable()) // Если поток на этапе завершения
            mWriteThread.join(); // Страхуемся

        mWriteThread = std::thread(&aThreadedDataSource::startUploadInThread, this); // Создаём поток
        Result = mReadThread.joinable();
    }

    return Result;
}
//---------------------------------------------------------------------------
void aThreadedDataSource::startUpdateInThread()
{
    updateInThread();
    mIsReading = false;
}
//---------------------------------------------------------------------------
void aThreadedDataSource::startUploadInThread()
{
    uploadInThread();
    mIsWriteing = false;
}
//---------------------------------------------------------------------------
