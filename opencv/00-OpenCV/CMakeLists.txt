cmake_minimum_required(VERSION 3.14)

project(00-OpenCV LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( 00-OpenCV.exe
  main.cpp
)
target_link_libraries(00-OpenCV.exe
    ${OpenCV_LIBS}
)