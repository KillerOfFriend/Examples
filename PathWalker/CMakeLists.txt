cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(ProjectPathWalker)

set(CMAKE_CXX_STANDARD 11) # Задаём c++11

set(PROJECT_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # Запоминаем путь к корневой папке проекта

add_subdirectory(Libraries) # Собираем библиотеки
add_subdirectory(Modules) # Собираем модули
