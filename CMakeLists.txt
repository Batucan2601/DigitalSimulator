cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DIGITAL_SIM VERSION 1.0 LANGUAGES CXX)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(raylib )
set( MAIN_SRC  src/main.cpp
src/Map.cpp
src/Controls.cpp
src/LogicElements.cpp
src/LogicElementsDraw.cpp)

set( INCLUDE_FILES  include/Controls.h
include/Map.h
include/LogicElements.h
include/LogicElementsDraw.h)

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${INCLUDE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

target_include_directories(${PROJECT_NAME} PUBLIC include)
