cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(ProjectPathWalker)

set(CMAKE_CXX_STANDARD 11) # Задаём c++11

set(PROJECT_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}) # Запоминаем путь к корневой папке проекта

set(BUILD_PATH ${PROJECT_ROOT_PATH}/Build/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}) # Запоминаем путь к папке сборки

set(LIBRARY_OUTPUT_PATH ${BUILD_PATH})  # Указываем путь папке сборки библиотек
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH}) # Указываем путь к папке сборки бинарей

add_subdirectory(Libraries) # Собираем библиотеки
add_subdirectory(Modules) # Собираем модули
