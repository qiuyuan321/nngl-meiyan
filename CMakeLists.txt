cmake_minimum_required (VERSION 3.8.1)
project(nngldemo)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED Core Widgets Gui OpenGL)
set(NNGLSDK_PATH ${PROJECT_SOURCE_DIR}/nnglsdk)
set(OPENCV_PATH  ${PROJECT_SOURCE_DIR}/opencv)

set(nngldemo_SOURCES
    main.cpp
    BeautySdkDemo.cpp
	MyGlView.cpp
    mainwindowdemo.cpp)

set(nngldemo_HEADERS
	BeautySdkDemo.h
	MyGlView.h
    mainwindowdemo.h)
    
set(nngldemo_UI
	BeautySdkDemo.ui
    mainwindowdemo.ui)


set(CMAKE_CXX_FLAGS_RELEASE "/MD")
set(CMAKE_CXX_FLAGS_DEBUG "/MDd /ZI /Od")

include_directories(${OPENCV_PATH}/include ${NNGLSDK_PATH}/include)
    
qt5_wrap_ui(nngldemo_UI_HEADERS ${nngldemo_UI})
# qt5_add_resources(nngldemo_QRC_SOURCES ${obs_QRC})

add_executable(nngldemo WIN32
    ${nngldemo_SOURCES}
	${nngldemo_HEADERS}
    ${nngldemo_UI_HEADERS})

target_link_libraries(nngldemo PRIVATE 
    debug ${OPENCV_PATH}/lib/opencv_world460d.lib
    optimized ${OPENCV_PATH}/lib/opencv_world460.lib
    ${NNGLSDK_PATH}/lib/nnglsdk.lib
    Qt5::Core
	Qt5::Widgets
    Qt5::Gui
    Qt5::OpenGL)

# install(TARGETS nngldemo)
