# Задание атрибутов приложения
project(Taypit1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)   # Разрешаем работу с собственной папкой
set(CMAKE_CXX_STANDARD 14)          # Задаём стандарт

# Запрещаем ASIO обращение к BOOST
add_definitions(-DASIO_STANDALONE)

set(BUILD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})   # Путь к папке сборки
set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH})                               # Указываем путь к папке сборки бинарей

# Ищим хидеры
file(GLOB_RECURSE BIN_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    )
# Ищим сорцы
file(GLOB_RECURSE BIN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    )

list(APPEND BIN_SOURCES main.cpp)

# Формируем список подключаемых директорий
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
    )

if (NOT WIN32)
    list(APPEND LINKING_LIBS pthread) # Под posix системами подключаем соответствующие потоки
endif (WIN32)

# Собираем как бинарь
add_executable(${PROJECT_NAME} ${BIN_HEADERS} ${BIN_SOURCES})
# Линкуем директории
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
# Линкуем библиотеки
target_link_libraries(${PROJECT_NAME} ${LINKING_LIBS})
