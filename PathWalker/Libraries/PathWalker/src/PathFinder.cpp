#include "PathFinder.h"

#include <iostream>

//-----------------------------------------------------------------------------
/**
 * @brief TPathWalker::TPathWalker - Инициализирующий конструктор
 * @param inLabyrinthPath - Путь к файлу с описанием лабиринта
 */
TPathWalker::TPathWalker(const TString inLabyrinthPath)
{
    if (!loadLabyrinth(inLabyrinthPath))
    {
        std::cout << "TPathWalker::TPathWalker" << "Ошибка! Не удалось считать лаберинт из файла:" << inLabyrinthPath << std::endl;
    }
}
//-----------------------------------------------------------------------------
/**
 * @brief TPathWalker::loadLabyrinth - Метод считает данные о лабиринте
 * @param inLabyrinthPath - Путь к файлу с описанием лабиринта
 * @return Вернёт признак успешности операции
 */
bool TPathWalker::loadLabyrinth(const TString inLabyrinthPath)
{
    bool Result = true;

    fLabyrinth.clear();

    return Result;
}
//-----------------------------------------------------------------------------
