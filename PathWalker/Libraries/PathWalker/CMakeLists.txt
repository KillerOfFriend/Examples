cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# Задание атрибутов приложения
set(PROJECT_NAME PathWalker)
project(${PROJECT_NAME})

add_definitions(-DPATHWALKER_EXPORTS) # Заводим макрос импорта\экспорта бибилиотеки

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Разрешаем подключение собственной папки
set(SELF_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src) # Задаём путь к собственным исходным кодам бибилиотеки

include_directories( # Список подключаемых к проекту директорий
    ${SELF_SOURCE_PATH}
)

# Ищим хидеры
file(GLOB_RECURSE SRC_H
    ${SELF_SOURCE_PATH}/*.h
    ${SELF_SOURCE_PATH}/*.hpp)
# Ищим исходники
file(GLOB_RECURSE SRC_CPP
    ${SELF_SOURCE_PATH}/*.c
    ${SELF_SOURCE_PATH}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_H} ${SRC_CPP}) # Создаём библиотеку

