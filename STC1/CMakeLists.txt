# Задание атрибутов приложения
set(PROJECT_NAME STC1)
project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)   # Разрешаем работу с собственной папкой
set(CMAKE_AUTOMOC ON)               # Разрешаем CMake  автоматический запуск moc при необходимости
set(CMAKE_AUTOUIC ON)               # Требуем создание кода из списка файлов Qt-дизайнера ui
set(CMAKE_CXX_STANDARD 17)          # Задаём стандарт

set(BUILD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})   # Путь к папке сборки
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})                               # Указываем путь к папке сборки бинарей

# Ищим библиотеки QT
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Sql CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

# Ищим хидеры
file(GLOB_RECURSE BIN_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )
# Ищим сорцы
file(GLOB_RECURSE BIN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )
# Ищим UI
file(GLOB_RECURSE BIN_UI
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
    )
# Ищим ресурсы
file(GLOB_RECURSE BIN_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc
    )

QT5_WRAP_UI(READY_UI ${BIN_UI}) # Подготавливаем инерфейс
QT5_ADD_RESOURCES(READY_RESOURCES ${BIN_RESOURCES}) # Подготавливаем ресурсы

# Формируем список подключаемых директорий
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    )

# Формируем список используемых модулей Qt
set(LINKING_LIBS
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Widgets
    )

if (NOT WIN32)
    list(APPEND LINKING_LIBS pthread) # Под posix системами подключаем соответствующие потоки
endif (WIN32)

# Собираем как бинарь
add_executable(${PROJECT_NAME} WIN32 ${BIN_HEADERS} ${BIN_SOURCES} ${READY_UI} ${READY_RESOURCES})
# Линкуем директории
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
# Линкуем библиотеки
target_link_libraries(${PROJECT_NAME} ${LINKING_LIBS})
