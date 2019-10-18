#ifndef PATHWALKER_H
#define PATHWALKER_H

#include <set>
#include <list>
#include <cmath>

#include "os_dependence.h"
#include "errors.h"
#include "PathWalkerTypes.h"
#include "Classes/CurrentPos.h"

#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;

#include "PathWalker_glob.h"

namespace PathWalker
{
    /**
     * @brief The TPathFinder class Класс,описывающий библиотеку перемещения в лаберинте
     */
    class PATHWALKER_LIB TPathWalker
    {
    public:
        TPathWalker(const filesystem::path inLabyrinthPath); // Инициализирующий конструктор

        bool isValid() const; // Метод вернёт флаг валидности лабиринта
        std::error_code lastError() const; // Метод вернёт код последней ошибки

        bool walkThePath(const TPosition inStartPos, const std::string inPath); // Метод пройт по указанному пути
        const TCurrentPos& walkResult() const; // Метод вернёт ссылку на класс, хранящий результат

    private:
        std::error_code fLastError; // Код последней ошибки
        std::list<TCell> fLabyrinth; // Контейнер, описывающий секции лабиринта

        TCurrentPos fCurrentPos; // Инициализируем позицию

        bool loadLabyrinth(const filesystem::path inLabyrinthPath); // Метод считает данные о лабиринте
        bool containCell(const TCell inCell) const; // Метод проверит существование ячейки лабиринта
        bool checkPathFormat(const std::string inPath) const; // Метод проверит формат пути

    };
}

#endif // PATHWALKER_H
