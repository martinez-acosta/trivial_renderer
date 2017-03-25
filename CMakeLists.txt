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
  tdraw/tdraw.cpp
  tinput/tinput.cpp
  tinput/cmdline.c
  tmodel/tmodel.cpp
  timage/timage.cpp
  tmath/tmatrix4x4.cpp
  tmath/tvector3d.cpp
  tmath/tvector4d.cpp
  lodepng/lodepng.cpp
  main.cpp
)
#set(CMAKE_CXX_STANDARD_REQUIRED 14)
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(trender ${TSOURCES})
