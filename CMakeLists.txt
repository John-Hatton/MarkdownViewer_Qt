cmake_minimum_required(VERSION 3.28)
project(MarkdownViewer_Qt)

set(CMAKE_CXX_STANDARD 23)

# Set the location of the Qt6 cmake files
set(CMAKE_PREFIX_PATH "C:/devel/sdk/qt6/6.6.2/msvc2019_64/lib/cmake/Qt6")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt6 components
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

include_directories(include)

add_subdirectory(source)
add_subdirectory(test)