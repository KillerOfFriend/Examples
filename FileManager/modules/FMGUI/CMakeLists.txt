cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project(FMGUI VERSION ${HM_VERSION} LANGUAGES CXX)

#====================================================================
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Разрешаем работу с собственной папкой
#====================================================================

#====================================================================
# Ищим используемые библиотеки
find_package(Qt${QT_VERSION} COMPONENTS Core Widgets QuickControls2 DBus REQUIRED) # Ищим библиотеки QT
#====================================================================
# Формируем список используемых библиотек
set(LINKED_LIBRARYES
    Qt${QT_VERSION}::Core
    Qt${QT_VERSION}::Widgets
    Qt${QT_VERSION}::Quick
    Qt${QT_VERSION}::QuickControls2
    Qt${QT_VERSION}::DBus
    )
#====================================================================
# Генерируем файл глобальных объявлений в сборочной директории проекта
configure_file(
    "${COMMON_FOLDER_PATH}/templates/dbus_defines.hpp.in"
    "dbus_defines.hpp"
    )
#====================================================================
# Автогенерация интерфейса DBUS
qt5_add_dbus_interface(DBUS_SRC ${COMMON_FOLDER_PATH}/templates/${DBUS_SERVICE_NAME}.xml dbusfsinterface)
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
# Ищим сорцы
file(GLOB_RECURSE BIN_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.qrc
)
#====================================================================
# Создаём бинарь
add_executable(${PROJECT_NAME} ${BIN_HEADERS} ${BIN_SOURCES} ${BIN_RESOURCES} ${DBUS_SRC})
# Подключаем папки с хидерами
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
# Линкуем библиотеки
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINKED_LIBRARYES})
#====================================================================

