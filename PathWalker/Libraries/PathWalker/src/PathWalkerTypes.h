#ifndef PATHWALKERTYPES_H
#define PATHWALKERTYPES_H

#include "Classes/Point.h"

typedef TPoint TCell;       ///< Секция лабиринта
typedef TPoint TPosition;   ///< Позиция

/**
 * @brief The eMoveDirection enum - Перечисление направлений движения
 */
enum class eMoveDirection : char
{
    mdLeft      = 'L',      ///< Влево
    mdRight     = 'R',      ///< Вправо
    mdUp        = 'U',      ///< Вверх
    mdDown      = 'D'       ///< Вниз
};

#endif // PATHWALKERTYPES_H
