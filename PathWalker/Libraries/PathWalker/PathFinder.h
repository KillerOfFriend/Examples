#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "os_dependence.h"
#include "PathWalker_glob.h"

/**
 * @brief The TPathFinder class Класс,описывающий библиотеку перемещения в лаберинте
 */
class PATHWALKER_LIB TPathFinder
{
public:
    TPathFinder(const TString inLabyrinthPath); // Конструктор по умолчанию

private:

    bool loadLabyrinth(const TString inLabyrinthPath); // Метод получит данные о лабиринте
};

#endif // PATHFINDER_H
