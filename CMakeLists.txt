cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Set the project name and version
project(DIGITAL_SIM VERSION 1.0 LANGUAGES CXX)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Set the project root directory (the directory where CMakeLists.txt is located)
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

# set(CMAKE_CXX_EXTENSIONS OFF) // not needed
set( IMGUI_FILES Libraries/imgui/imgui.cpp 
Libraries/imgui/imgui_draw.cpp
Libraries/imgui/imgui_tables.cpp 
Libraries/imgui/imgui_widgets.cpp 
#support for rlimgui 
Libraries/rlImGui/rlImGui.cpp
Libraries/ImGuiFileDialog/ImGuiFileDialog.cpp
)

add_library( ImGuiLib  ${IMGUI_FILES})
target_include_directories(ImGuiLib PUBLIC Libraries/raylib/src)
target_include_directories(ImGuiLib PUBLIC Libraries/imgui)
target_include_directories(ImGuiLib PUBLIC Libraries/rlImGui)
target_include_directories(ImGuiLib PUBLIC Libraries/ImGuiFileDialog)

add_subdirectory(Libraries/raylib)



# Define PROJECT_ROOT_DIR as a preprocessor macro for C++ code
add_definitions(-DPROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")

# Automatically find all source (.cpp) and header (.h) files in their respective directories
file(GLOB_RECURSE MAIN_SRC CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS include/*.h)
# # Optionally display found files for debugging purposes
# message(STATUS "Source files: ${MAIN_SRC}")
# message(STATUS "Include files: ${INCLUDE_FILES}")

# Create the executable
add_executable(${PROJECT_NAME} ${MAIN_SRC})

# Link raylib to the executable
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_link_libraries(${PROJECT_NAME} PUBLIC ImGuiLib)



# Include directories for headers
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC Libraries/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC Libraries/rlImGui)

