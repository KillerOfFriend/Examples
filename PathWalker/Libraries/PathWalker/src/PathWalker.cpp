#include "PathWalker.h"

#include <iostream>
#include <algorithm>

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
    auto findRes = std::find(fLabyrinth.begin(), fLabyrinth.end(), inCell);
    return findRes != fLabyrinth.end();
}
//-----------------------------------------------------------------------------
