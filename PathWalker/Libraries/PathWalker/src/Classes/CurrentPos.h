#ifndef CURRENTPOS_H
#define CURRENTPOS_H

#include <list>
#include <string>

#include "PathWalkerTypes.h"

#include "PathWalker_glob.h"

namespace PathWalker
{
    /**
     * @brief The TCurrentPos class - Класс, описывающий текущую позицию
     */
    class PATHWALKER_LIB TCurrentPos
    {
    public:
        TCurrentPos(); // Конструктор по умолчанию

        void reset(const TPosition inStartPos); // Метод задаст позицию заного

        TPosition neighbore(const eMoveDirection inDirection) const; // Метод определит соседнюю позицию по заданному напралению
        void move(const eMoveDirection inDirection); // Метод переместит текущую позицию по заланному направлению

        TPosition startPosition() const; // Метод вернёт стартовую позицию
        TPosition position() const; // Метод вернёт текущую позицию

        const std::list<eMoveDirection>& pathTraveled() const; // Метод вернёт пройденый путь
        std::string pathStr() const; // Метод вернёт пройденый путь в виде строки

    private:
        TPosition fStartPos; // Стартовая позиция
        TPosition fPos; // Текущая позиция
        std::list<eMoveDirection> fPathTraveled; // Пройденый путь

        void regPathTraveled(const eMoveDirection inDirection); // Метод зарегестрирует следующий шаг маршрута
        TPosition shiftPos(const TPosition inPosition, const eMoveDirection inDirection) const; // Метод вернёт смещение указанной позиции
    };
}

#endif // CURRENTPOS_H
