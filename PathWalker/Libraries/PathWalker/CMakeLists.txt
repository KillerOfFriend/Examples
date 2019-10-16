cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Задание атрибутов приложения
set(PROJECT_NAME PathWalker)
project(${PROJECT_NAME} VERSION 1.0.0)

add_definitions(-DPATHWALKER_EXPORTS)

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Разрешаем работу с собственной папкой

# Ищим хидеры
file(GLOB_RECURSE SRC_H
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
# Ищим исходники
file(GLOB_RECURSE SRC_CPP
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_H} ${SRC_CPP}) # Создаём библиотеку

