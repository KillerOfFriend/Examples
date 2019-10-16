cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# Задание атрибутов приложения
set(PROJECT_NAME Example)
project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Разрешаем подключение собственной папки
set(SELF_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src) # Путь к исходным кодам модуля

include_directories( # Список подключаемых к проекту директорий
    ${SELF_SOURCE_PATH}
    ${PROJECT_ROOT_PATH}/Libraries/PathWalker/src
)

# Ищим хидеры
file(GLOB_RECURSE SRC_H
    ${SELF_SOURCE_PATH}/*.h
    ${SELF_SOURCE_PATH}/*.hpp)
# Ищим исходники
file(GLOB_RECURSE SRC_CPP
    ${SELF_SOURCE_PATH}/*.c
    ${SELF_SOURCE_PATH}/*.cpp)

add_executable(${PROJECT_NAME} WIN32 ${SRC_H} ${SRC_CPP}) # Создаём исполняемый файл
target_link_libraries(${PROJECT_NAME} PathWalker) # Линкуем библиотеки
