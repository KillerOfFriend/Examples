#ifndef POINT_H
#define POINT_H

#include <cstdint>

#include "PathWalker_glob.h"

class PATHWALKER_LIB TPoint
{
public:
    TPoint(); // Конструктор по умолчанию
    TPoint(const std::int32_t inX, const std::int32_t inY); // Инициализирующий конструктор
    TPoint(const TPoint& inOther); // Копирующий конструктор

    TPoint& operator = (const TPoint& inOther); // Оператор копирования

    bool operator == (const TPoint& inOther); // Оператор равенства
    bool operator != (const TPoint& inOther); // Оператор неравенства

    void setX(const std::int32_t inX); // Метод задаст Х
    void setY(const std::int32_t inY); // Метод задаст Y

    std::int32_t x() const; // Метод вернёт X
    std::int32_t y() const; // Метод вернёт Y

private:
    std::int32_t fX = 0;
    std::int32_t fY = 0;

};

#endif // POINT_H
