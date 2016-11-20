# Set CMake Version Required
cmake_minimum_required(VERSION 2.8)

# Set Project Name
project(ImageViewer)

# Set Compiler
set(CMAKE_CXX_COMPILER "clang++")

# Set Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find Packages
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Turn On Automoc
set(CMAKE_AUTOMOC ON)

# Get Source Files
file(GLOB_RECURSE SOURCE_FILES SourceFiles/*.cpp)

# Add Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link Libraries
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)

# Copy Images
file(COPY Images DESTINATION ${CMAKE_BINARY_DIR})
