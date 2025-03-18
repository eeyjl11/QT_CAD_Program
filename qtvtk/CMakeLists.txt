cmake_minimum_required(VERSION 3.8)

project(qtvtk)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# List source files & resources
file (GLOB Sources *.cpp)
file (GLOB Headers *.h)
file (GLOB Resources *.qrc)
file (GLOB UIs *.ui)

# Find package Qt
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# Use Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find package VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

# Build executable
add_executable(qtvtk-viewer ${Sources} ${Headers} ${Resources} ${UIs})

target_link_libraries(qtvtk-viewer PRIVATE Qt5::Widgets Qt5::OpenGL ${VTK_LIBRARIES} ourmodelib)
target_include_directories(qtvtk-viewer PRIVATE ourmodelib ${CMAKE_SOURCE_DIR}/ModelLibrary/src)
message("${CMAKE_SOURCE_DIR}")

