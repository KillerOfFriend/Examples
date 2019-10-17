#include "Point.h"

//-----------------------------------------------------------------------------
TPoint::TPoint()
{

}
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::TPoint - Инициализирующий конструктор
 * @param inX - Значение X
 * @param inY - Значение Y
 */
TPoint::TPoint(const std::int32_t inX, const std::int32_t inY)
{
    fX = inX;
    fY = inY;
}
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::TPoint - Копирующий конструктор
 * @param inOther - Копируемый объект
 */
TPoint::TPoint(const TPoint& inOther)
{
    fX = inOther.fX;
    fY = inOther.fY;
}
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::operator = - Оператор копирования
 * @param inOther - Копируемый объект
 * @return Вернёт копию объекта
 */
TPoint& TPoint::operator = (const TPoint& inOther)
{
    if (this == &inOther)
        return *this;

    fX = inOther.fX;
    fY = inOther.fY;

    return *this;
}
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::operator == Оператор равенства
 * @param inOther - Сравниваемый объект
 * @return Вернёт признак равенства
 */
bool TPoint::operator == (const TPoint& inOther) const
{ return (fX == inOther.fX) && (fY == inOther.fY); }
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::operator != - Оператор неравенства
 * @param inOther - Сравниваемый объект
 * @return Вернёт признак неравенства
 */
bool TPoint::operator != (const TPoint& inOther) const
{ return !(*this == inOther); }
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::setX - Метод задаст Х
 * @param inX - Значение X
 */
void TPoint::setX(const std::int32_t inX)
{ fX = inX; }
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::setY - Метод задаст Y
 * @param inY - Значение Y
 */
void TPoint::setY(const std::int32_t inY)
{ fY = inY; }
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::x - Метод вернёт X
 * @return - Вернёт X
 */
std::int32_t TPoint::x() const
{ return fX; }
//-----------------------------------------------------------------------------
/**
 * @brief TPoint::y - Метод вернёт Y
 * @return Вернёт Y
 */
std::int32_t TPoint::y() const
{ return fY; }
//-----------------------------------------------------------------------------
std::ostream &operator << (std::ostream& outStream, const TPoint& inPoint)
{
    outStream << "(" << inPoint.fX << ", " << inPoint.fY << ")";
    return outStream;
}
//-----------------------------------------------------------------------------
