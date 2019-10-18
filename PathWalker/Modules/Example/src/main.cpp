#include <iostream>
#include <algorithm>

#include "PathWalker.h"

int main(int argc, char *argv[])
{
    ENCODINGSETUP(CP_UTF8);

    filesystem::path LabyrinthPath;
    PathWalker::TPathWalker PathWalker(LabyrinthPath);

    if (!PathWalker.isValid())
        std::cout << "Не удалось считать файл лабиринта!" << std::endl;
    else
    {
        std::string Path = "lrud";
        PathWalker::TCell StartCell(0,0);

        std::cout << "Запускаем поиск по маршруту:" << Path << std::endl;

        if (!PathWalker.walkThePath(StartCell, Path)) // При прохождении произошла ошибка
            std::cout << "Ошибка! Не удалось пройти оп заданному пути:" << PathWalker.lastError().message() << std::endl;
        else // Маршрут успешно пройден
        {
            const std::list<PathWalker::eMoveDirection>& PathTraveled = PathWalker.walkResult().pathTraveled();
            std::cout << "Пройдены шаги: ";

            std::for_each(PathTraveled.cbegin(), PathTraveled.cend(), [&](const PathWalker::eMoveDirection& Direct)
            {
                 std::cout << static_cast<char>(Direct);
            });

            std::cout << std::endl;
            //--
            std::cout << "Пройден маршрут: " << PathWalker.walkResult().pathStr()  << std::endl;
            //--
            PathWalker::TPosition Pos = PathWalker.walkResult().position();
            std::cout << "Финишная позиция:" << " (" << Pos.x() << ", " << Pos.y() << ") " << std::endl;
        }
    }

    return 0;
}
