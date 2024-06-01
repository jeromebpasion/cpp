cmake_minimum_required(VERSION 3.0.0)
project(Cpp20 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(
    SOURCES
    main.cpp
    )

add_executable(Scratch.exe
  ${SOURCES}
)