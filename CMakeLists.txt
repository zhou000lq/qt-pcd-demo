cmake_minimum_required(VERSION 3.1.0)

project(loadAndShow VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()



set(Qt5_DIR /opt/Qt5.5.1/5.5/gcc_64/lib/cmake/Qt5) #find Qt5 install path
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(VTK_DIR /usr/local/lib/cmake/vtk-6.3) #find VTK install path
FIND_PACKAGE(VTK REQUIRED)

set(PCL_DIR /usr/local/share/pcl-1.9) #find VTK install path
find_package(PCL REQUIRED)

#load VTK path variables
INCLUDE(${VTK_USE_FILE})

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

INCLUDE_DIRECTORIES(${VTK_INCLUDES})
add_executable(loadAndShow
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)

target_link_libraries(loadAndShow Qt5::Widgets ${PCL_LIBRARIES} ${VTK_LIBRARIES})
