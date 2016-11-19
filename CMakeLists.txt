cmake_minimum_required(VERSION 2.8)
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

set(SOURCE_FILES SourceFiles/Main.cpp SourceFiles/MainWindow.cpp SourceFiles/MainWindow.h SourceFiles/MainWindow/ToolBar.cpp SourceFiles/MainWindow/ToolBar.h SourceFiles/MainWindow/ImageView.cpp SourceFiles/MainWindow/ImageView.h SourceFiles/MainWindow/StatusBar.cpp SourceFiles/MainWindow/StatusBar.h SourceFiles/PreferencesDialog.cpp SourceFiles/PreferencesDialog.h SourceFiles/PreferencesDialog/Control.cpp SourceFiles/PreferencesDialog/Control.h SourceFiles/PreferencesDialog/Slideshow.cpp SourceFiles/PreferencesDialog/Slideshow.h SourceFiles/MainWindow/Menu/File.cpp SourceFiles/MainWindow/Menu/File.h SourceFiles/MainWindow/Menu/Edit.cpp SourceFiles/MainWindow/Menu/Edit.h SourceFiles/MainWindow/Menu/View.cpp SourceFiles/MainWindow/Menu/View.h SourceFiles/Preferences.cpp SourceFiles/Preferences.h SourceFiles/PreferencesDialog/Display.cpp SourceFiles/PreferencesDialog/Display.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link Libraries
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
