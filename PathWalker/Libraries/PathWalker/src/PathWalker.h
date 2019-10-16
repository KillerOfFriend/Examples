#ifndef PATHWALKER_H
#define PATHWALKER_H

#include <list>
#include <cmath>

#include "os_dependence.h"
#include "errors.h"
#include "Classes/Point.h"

#include "PathWalker_glob.h"

typedef TPoint TCell;

/**
 * @brief The TPathFinder class Класс,описывающий библиотеку перемещения в лаберинте
 */
class PATHWALKER_LIB TPathWalker
{
public:
    TPathWalker(const TString inLabyrinthPath); // Инициализирующий конструктор

    bool isValid() const; // Метод вернёт флаг валидности лабиринта
    std::error_code lastError() const; // Метод вернёт код последней ошибки

private:
    std::error_code fLastError; // Код последней ошибки
    std::list<TCell> fLabyrinth; // Контейнер, описывающий секции лабиринта

    bool loadLabyrinth(const TString inLabyrinthPath); // Метод считает данные о лабиринте
    bool containCell(const TCell inCell) const; // Метод проверит существование ячейки лабиринта

};

#endif // PATHWALKER_H
