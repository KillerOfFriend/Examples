cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project(FMGUI VERSION ${HM_VERSION} LANGUAGES CXX)

#====================================================================
set(CMAKE_INCLUDE_CURRENT_DIR ON) # Разрешаем работу с собственной папкой
#====================================================================

#====================================================================
# Ищим используемые библиотеки
find_package(Qt${QT_VERSION} COMPONENTS Core Widgets QuickControls2 REQUIRED) # Ищим библиотеки QT
#====================================================================
# Формируем список используемых библиотек
set(LINCED_LIBRARYES
    Qt${QT_VERSION}::Core
    Qt${QT_VERSION}::Widgets
    Qt${QT_VERSION}::Quick
    Qt${QT_VERSION}::QuickControls2
    )
#====================================================================
# Формируем список подключаемых директорий
set(INCLUDE_DIRS
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
add_executable(${PROJECT_NAME} ${BIN_HEADERS} ${BIN_SOURCES} ${BIN_RESOURCES})
# Подключаем папки с хидерами
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
# Линкуем библиотеки
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINCED_LIBRARYES})
#====================================================================

