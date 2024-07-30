cmake_minimum_required(VERSION 3.20)

project(AlwaysEnglish VERSION 1.0)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_subdirectory(FluentUI)
add_subdirectory(src)
