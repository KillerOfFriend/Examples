#ifndef ERRORS_H
#define ERRORS_H

#include "Classes/ErrorCategory.h"

namespace PathWalker
{
    // По указанному пути не существует файла с лабиринтом
    static const TErrorCategory CatFileNotExist         ("PathWalker Error", std::string("Parse file not exist!"));
    static const std::error_code ErrFileNotExist        (1, CatFileNotExist);
    // Лабиринт пуст
    static const TErrorCategory CatLabyrinthIsEmpty     ("PathWalker Error", std::string("The labyrinth is empty!"));
    static const std::error_code ErrLabyrinthIsEmpty    (2, CatLabyrinthIsEmpty);
    // Не удалось разобрать файл с лабиринтом
    static const TErrorCategory CatFileParsError        ("PathWalker Error", std::string("Parse file error!"));
    static const std::error_code ErrFileParsError       (3, CatFileParsError);
    // Стартовой позиции маршрута не существует в лаберинте
    static const TErrorCategory CatStartCellNotExist    ("PathWalker Error", std::string("The specified cell does not exist!"));
    static const std::error_code ErrStartCellNotExist   (4, CatStartCellNotExist);
    // В маршруте обнаружены некорректные символы
    static const TErrorCategory CatRouteCorrupted       ("PathWalker Error", std::string("The route contains invalid characters!"));
    static const std::error_code ErrRouteCorrupted      (5, CatRouteCorrupted);
}

#endif // ERRORS_H
