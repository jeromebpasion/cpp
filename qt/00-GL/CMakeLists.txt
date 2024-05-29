cmake_minimum_required(VERSION 3.14)

project(00-GL LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(
    SOURCES
    src/windowgl.h
    src/windowgl.cpp
    src/geometrydraw.h
    src/geometrydraw.cpp
    main.cpp
    qrc/shaders.qrc
    )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)

#add_subdirectory(src)
#add_subdirectory(external)
#enable_testing()
#add_subdirectory(tests)

add_executable(00-GL.exe
  ${SOURCES}
)
target_link_libraries(00-GL.exe
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
    )
