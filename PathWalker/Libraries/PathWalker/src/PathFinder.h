#ifndef PATHWALKER_H
#define PATHWALKER_H

#include <set>

#include "os_dependence.h"
#include "Classes/Point.h"

#include "PathWalker_glob.h"

/**
 * @brief The TPathFinder class Класс,описывающий библиотеку перемещения в лаберинте
 */
class PATHWALKER_LIB TPathWalker
{
public:
    TPathWalker(const TString inLabyrinthPath); // Инициализирующий конструктор

private:
    std::set<TPoint> fLabyrinth; // Контейнер, описывающий секции лабиринта
    bool loadLabyrinth(const TString inLabyrinthPath); // Метод считает данные о лабиринте

};

#endif // PATHWALKER_H
