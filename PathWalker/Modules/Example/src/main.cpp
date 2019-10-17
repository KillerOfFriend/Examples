#include <iostream>
#include <algorithm>

#include "PathWalker.h"

int main(int argc, char *argv[])
{
    TString LabyrinthPath;
    TPathWalker PathWalker(LabyrinthPath);

    if (!PathWalker.isValid())
        std::cout << "Не удалось считать файл лабиринта!" << std::endl;
    else
    {
        std::string Path = "lrud";
        TCell Start(0,0);

        if (!PathWalker.walkThePath(Start, Path)) // При прохождении произошла ошибка
            std::cout << "Ошибка! Не удалось пройти оп заданному пути:" << PathWalker.lastError().message() << std::endl;
        else // Маршрут успешно пройден
        {
            const std::list<eMoveDirection>& PathTraveled = PathWalker.walkResult().pathTraveled();
            std::cout << "Пройдены шаги: ";

            std::for_each(PathTraveled.cbegin(), PathTraveled.cend(), [&](const eMoveDirection& Direct)
            {
                 std::cout << static_cast<char>(Direct);
            });

            std::cout << std::endl;
            //--
            std::cout << "Пройден маршрут: " << PathWalker.walkResult().pathStr()  << std::endl;
            //--
            TPosition Pos = PathWalker.walkResult().position();
            std::cout << "Финишная позиция:" << " (" << Pos.x() << ", " << Pos.y() << ") " << std::endl;
        }
    }

    return 0;
}
