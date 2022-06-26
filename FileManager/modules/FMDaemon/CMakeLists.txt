cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project(FMDaemon VERSION ${VERSION} LANGUAGES CXX)

#====================================================================
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Разрешаем работу с собственной папкой
#====================================================================

#====================================================================
# Ищим используемые библиотеки
#====================================================================
# Ищим используемые библиотеки
find_package(Qt${QT_VERSION} COMPONENTS Core DBus REQUIRED) # Ищим библиотеки QT
#====================================================================

#====================================================================
# Формируем список используемых библиотек
set(LINKED_LIBRARYES
    Qt${QT_VERSION}::Core
    Qt${QT_VERSION}::DBus
    )
#====================================================================
# Генерируем файл запуска DBus сервиса
configure_file(
    "${COMMON_FOLDER_PATH}/templates/dbus_service.in"
    "${EXECUTABLE_OUTPUT_PATH}/${DBUS_SERVICE_NAME}.service"
    )
#====================================================================
# Генерируем файл глобальных объявлений в сборочной директории проекта
configure_file(
    "${COMMON_FOLDER_PATH}/templates/dbus_defines.hpp.in"
    "dbus_defines.hpp"
    )
#====================================================================
# Формируем список подключаемых директорий
set(INCLUDE_DIRS
    ${COMMON_FOLDER_PATH}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
#====================================================================
# Ищим хидеры
file(GLOB_RECURSE BIN_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)
#====================================================================
# Ищим сорцы
file(GLOB_RECURSE BIN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
#====================================================================
# Создаём бинарь
add_executable(${PROJECT_NAME} ${BIN_HEADERS} ${BIN_SOURCES} ${BIN_RESOURCES})
# Подключаем папки с хидерами
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
# Линкуем библиотеки
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINKED_LIBRARYES})
#====================================================================
