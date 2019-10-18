#include "PathWalker.h"

#include <iostream>
#include <algorithm>
#include <ctype.h>

#include "errors.h"

using namespace PathWalker;

//-----------------------------------------------------------------------------
/**
 * @brief TPathWalker::TPathWalker - Инициализирующий конструктор
 * @param inLabyrinthPath - Путь к файлу с описанием лабиринта
 */
TPathWalker::TPathWalker(const TString inLabyrinthPath)
{
    if (!loadLabyrinth(inLabyrinthPath))
    {
        std::cout << "TPathWalker::TPathWalker" << "Ошибка! Не удалось считать лаберинт из файла" << std::endl;
    }
}
//-----------------------------------------------------------------------------
/**
 * @brief TPathWalker::isValid - Метод вернёт флаг валидности лабиринта
 * @return Вернёт флаг валидности лабиринта
 */
bool TPathWalker::isValid() const
{
    return !fLabyrinth.empty();
}
//-----------------------------------------------------------------------------
/**
 * @brief TPathWalker::lastError - Метод вернёт код последней ошибки
 * @return Вернёт код последней ошибки
 */
std::error_code TPathWalker::lastError() const
{ return fLastError; }
//-----------------------------------------------------------------------------
bool TPathWalker::walkThePath(const TPosition inStartPos, const std::string inPath) // Метод пройт по указанному пути
{
    bool Result = true;
    fLastError.clear();
    fCurrentPos.reset(TPosition(0,0)); // Сбрасываем текущую позицию

    if (!isValid()) // Проверяем валидность лабиринта
    {
        fLastError = ErrLabyrinthIsEmpty;
        Result = false;
    }
    else
    {
        if (!containCell(inStartPos)) // Проверяем наличие старотовой ячейки
        {
            fLastError = ErrStartCellNotExist;
            Result = false;
        }
        else
        {
            if (!checkPathFormat(inPath)) // Проверяем корректность маршгрута
            {
                fLastError = ErrRouteCorrupted;
                Result = false;
            }
            else
            {
                fCurrentPos.reset(inStartPos);

                std::for_each(inPath.cbegin(), inPath.cend(), [this](const char & Char) // Проходим маршрут
                {
                    if (containCell(fCurrentPos.neighbore(static_cast<eMoveDirection>(toupper(Char))))) // Если в лабиринте есть соседняя секция
                        fCurrentPos.move(static_cast<eMoveDirection>(toupper(Char))); // Перемещаемся в неё
                });
            }
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
/**
 * @brief walkResult - Метод вернёт ссылку на класс, хранящий результат
 * @return Вернёт ссылку на класс, хранящий результат
 */
const TCurrentPos& TPathWalker::walkResult() const
{ return fCurrentPos; }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 * @brief TPathWalker::loadLabyrinth - Метод считает данные о лабиринте
 * @param inLabyrinthPath - Путь к файлу с описанием лабиринта
 * @return Вернёт признак успешности операции
 */
bool TPathWalker::loadLabyrinth(const TString inLabyrinthPath)
{
    fLastError.clear();

    bool Result = true;

    fLabyrinth.clear();

    std::string Data = "(-1,0),(0,0),(1,0),(0,1),(0,-1)";
    std::size_t Pos = Data.find(',');

    while (Pos != std::string::npos)
    {
        TCell NewCell;

        NewCell.setX( std::stoi(Data.substr(1, Pos - 1)) );
        Data = Data.substr(Pos + 1, Data.size());

        Pos = Data.find(',');

        NewCell.setY( std::stoi(Data.substr(0, Pos - 1)) );
        Data = Data.substr(Pos + 1, Data.size());

        Pos = Data.find(',');

        if (containCell(NewCell))
            std::cout << "[TPathWalker::loadLabyrinth]" << "Дубликат ячейки (" << NewCell.x() << "," << NewCell.y() << ") проигнорирован";
        else
            fLabyrinth.push_back(NewCell);
    }

    return Result;
}
//-----------------------------------------------------------------------------
/**
 * @brief TPathWalker::containCell - Метод проверит существование ячейки лабиринта
 * @param inCell - Искомая ячейка
 * @return Вернтё признак наличия ячейки в лабиринте
 */
bool TPathWalker::containCell(const TCell inCell) const
{
    auto findRes = std::find(fLabyrinth.begin(), fLabyrinth.end(), inCell); // Ищим ячейку в контейнире
    return findRes != fLabyrinth.end();
}
//-----------------------------------------------------------------------------
/**
 * @brief TPathWalker::checkPathFormat - Метод проверит формат пути
 * @param inPath - Полученный путь
 * @return Вернёт признак валидности маршрута
 */
bool TPathWalker::checkPathFormat(const std::string inPath) const
{
    bool Result = true;

    if (inPath.empty()) // Пустой маршрут не валиден
        Result = false;
    else
    {
        // Инициализируем множество допустимых шагов в маршруте
        const std::set<eMoveDirection> LegalPathChar {eMoveDirection::mdLeft, eMoveDirection::mdRight, eMoveDirection::mdUp, eMoveDirection::mdDown};

        auto Res = std::find_if(inPath.cbegin(), inPath.cend(), [&LegalPathChar](const char & Char) // Ищим невалидный символ
        {
            return LegalPathChar.find(static_cast<eMoveDirection>(toupper(Char))) == LegalPathChar.end();
        });

       Result = (Res == inPath.end()); // Если лишних символов не обнаружено, то валиден
    }

    return Result;
}
//-----------------------------------------------------------------------------
