cmake_minimum_required(VERSION 3.5)

project(TSP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.12.12\\5.12.12\\mingw73_64\\lib\\cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    dialog/addCity/addCityDialog.cpp
    dialog/addRoad/addRoadDialog.cpp
    dialog/solutionInput/solutionInputDialog.cpp
    dialog/solutionOutput/solutionOutputDialog.cpp
    model/city/cityModel.cpp
    model/road/roadModel.cpp
    utils/graph/graph.cpp
    utils/scene/scene.cpp
    window/main/mainWindow.cpp
    main.cpp
)

set(PROJECT_HEADERS
    dialog/addCity/addCityDialog.h 
    dialog/addRoad/addRoadDialog.h 
    dialog/solutionInput/solutionInputDialog.h 
    dialog/solutionOutput/solutionOutputDialog.h 
    model/city/cityModel.h 
    model/road/roadModel.h 
    utils/graph/graph.h 
    utils/scene/scene.h 
    window/main/mainWindow.h
)

# В шапках возникнут проблемы, надо один раз скомпилить и скопировать шапки из
# build/{project_name}_autogen/include в корень, тогда отпустит.
set(PROJECT_FORMS
    dialog/addCity/addCityDialog.ui 
    dialog/addRoad/addRoadDialog.ui 
    dialog/solutionInput/solutionInputDialog.ui 
    dialog/solutionOutput/solutionOutputDialog.ui 
    window/main/mainWindow.ui
)

add_executable(TSP WIN32 ${PROJECT_FORMS} ${PROJECT_HEADERS} ${PROJECT_SOURCES})

target_link_libraries(TSP Qt5::Widgets -static-libstdc++)

set_target_properties(TSP PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER G.T  # пока побудет так
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
