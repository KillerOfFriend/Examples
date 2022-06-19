set(CPACK_PACKAGE_NAME ${DBUS_SERVICE_INSTALL_DIR}
    CACHE STRING "The resulting package name"
)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple C++ test application"
    CACHE STRING "Package description for the package metadata"
)
set(CPACK_PACKAGE_VENDOR "KOF-Soft")

set(CPACK_VERBATIM_VARIABLES YES)

set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
SET(CPACK_OUTPUT_FILE_PREFIX "${BUILD_PATH}/deb")

set(CPACK_PACKAGING_INSTALL_PREFIX ${DBUS_SERVICE_INSTALL_PATH})

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT "KillerOfFriend@yandex.ru")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alekseev Sergey")

#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
#set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)

set(CPACK_DEB_COMPONENT_INSTALL YES)
# Список зависимостей
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libqt5core5a (>= 5.12)"
    "libqt5widgets5 (>= 5.12)"
    "libqt5gui5 (>= 5.12)"
    "libqt5network5 (>= 5.12)"
    "libqt5dbus5 (>= 5.12)"
    "libqt5qml5 (>= 5.12)"
    "libqt5quick5 (>= 5.12)"
    "libqt5quickcontrols2-5 (>= 5.12)"
    "libqt5quicktemplates2-5 (>= 5.12)"
    "qml-module-qtquick2 (>= 5.12)"
    "qml-module-qtquick-controls (>= 5.12)"
    "qml-module-qtquick-controls2 (>= 5.12)"
    "qml-module-qtquick-layouts (>= 5.12)"

    "libstdc++6"
    "libdbus-1-3"
    )

# Заменим разделитель для соответствия формату DEB пакета
string(REPLACE ";" "," CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}")

include(CPack)
