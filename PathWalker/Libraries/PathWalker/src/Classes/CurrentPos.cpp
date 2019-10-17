#include "CurrentPos.h"

#include <algorithm>

//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::TCurrentPos - Конструктор по умолчанию
 */
TCurrentPos::TCurrentPos()
{

}
//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::reset - Метод задаст позицию заного
 * @param inStartPos - Начальная позиция
 */
void TCurrentPos::reset(const TPosition inStartPos)
{
    fStartPos = inStartPos;
    fPos = inStartPos;
    fPathTraveled.clear();
}
//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::neighbore - Метод определит соседнюю позицию по заданному напралению
 * @param inDirection - Направление
 * @return Вернёт сеседнюю позицию по направлению
 */
TPosition TCurrentPos::neighbore(const eMoveDirection inDirection) const
{
    return shiftPos(fPos, inDirection); // Получаем смещение == соседа
}
//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::move - Метод переместит текущую позицию по заланному направлению
 * @param inDirection - Направление
 */
void TCurrentPos::move(const eMoveDirection inDirection)
{
    TPosition NewPos = shiftPos(fPos, inDirection); // Получаем смещение

    if (NewPos != fPos) // Если смещение произошло
    {
        fPos = NewPos; // Запоминаем новую позицию
        regPathTraveled(inDirection); // Регистрируем шаг маршрута
    }
}
//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::startPosition - Метод вернёт стартовую позицию
 * @return Вернёт стартовую позицию
 */
TPosition TCurrentPos::startPosition() const
{ return fStartPos; }
//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::position - Метод вернёт текущую позицию
 * @return Вернёт текущую позицию
 */
TPosition TCurrentPos::position() const
{ return fPos; }
//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::distanceTraveled - Метод вернёт пройденый путь
 * @return Вернёт пройденый путь
 */
const std::list<eMoveDirection>& TCurrentPos::pathTraveled() const
{ return fPathTraveled; }
//-----------------------------------------------------------------------------
#include <sstream>
#include <iostream>

/**
 * @brief TCurrentPos::pathStr - Метод вернёт пройденый путь в виде строки
 * @return Вернёт пройденый путь в виде строки
 */
std::string TCurrentPos::pathStr() const
{
    std::string Result = "";

    if (!fPathTraveled.empty()) // Только если в маршруте что то есть
    {
        TPoint Pos = fStartPos; // С начальной позиции
        std::stringstream StringStream; // Готовим текстовый поток

        StringStream << Pos;

        // Формируем весь маршрут
        std::for_each(fPathTraveled.begin(), fPathTraveled.end(), [&](const eMoveDirection & Direct)
        {
            StringStream << " -> ";
            Pos = shiftPos(Pos, Direct);
            StringStream << Pos;

        });

        Result =StringStream.str();
    }

    return Result;
}
//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::regPathTraveled - Метод зарегестрирует следующий шаг маршрута
 * @param inDirection - Регистрируемое направление
 */
void TCurrentPos::regPathTraveled(const eMoveDirection inDirection)
{
    fPathTraveled.push_back(inDirection); // Добавляем новый маршрута
}
//-----------------------------------------------------------------------------
/**
 * @brief TCurrentPos::shiftPos - Метод вернёт смещение указанной позиции
 * @param inPosition - Позиция
 * @param inDirection - Смещение
 * @return Вернёт смещение указанной позиции
 */
TPosition TCurrentPos::shiftPos(const TPosition inPosition, const eMoveDirection inDirection) const
{
    TPosition Result;

    switch (inDirection) // Проверяем направление
    {
        case eMoveDirection::mdLeft:    { Result = TPosition(inPosition.x() + 1, inPosition.y()); break; };
        case eMoveDirection::mdRight:   { Result = TPosition(inPosition.x() - 1, inPosition.y()); break; };
        case eMoveDirection::mdUp:      { Result = TPosition(inPosition.x(), inPosition.y() + 1); break; };
        case eMoveDirection::mdDown:    { Result = TPosition(inPosition.x(), inPosition.y() - 1); break; };
        // Нет направления, корабль не плывёт
        default: { Result = inPosition;  break; }
    }

    return Result;
}
//-----------------------------------------------------------------------------
