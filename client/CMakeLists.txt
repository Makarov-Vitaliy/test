cmake_minimum_required(VERSION 3.5)

project(client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Network Widgets Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Widgets Svg REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        camera_field.cpp
        camera_field.h
        rowgroup.cpp
        rowgroup.h
        mainwindow.h
        column_combo.cpp
        column_combo.h
        constants.h
        constants.cpp
        udpreciever.h
        udpreciever.cpp
        resources.qrc
)
#qt5_add_resources(SOURCES resources.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(client
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(client SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(client
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Svg)
