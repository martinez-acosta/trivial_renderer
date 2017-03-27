project (trenderer)
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)

cmake_minimum_required(VERSION 3.7.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tdraw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tinput)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tmodel)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/timage)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tmath)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lodepng)

set(TSOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/tdraw/tdraw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tinput/tinput.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tinput/cmdline.c
  ${CMAKE_CURRENT_SOURCE_DIR}/tmodel/tmodel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/timage/timage.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tmath/tmatrix4x4.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tmath/tvector3d.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tmath/tvector4d.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(trender ${TSOURCES})
