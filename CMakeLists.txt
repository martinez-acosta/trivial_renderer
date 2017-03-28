project (trenderer)
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)

cmake_minimum_required(VERSION 3.7.0)

#add_subdirectory(tmath)
#add_subdirectory(tdraw)
#add_subdirectory(tinput)
#add_subdirectory(tmodel)
#add_subdirectory(lodepng)
#add_subdirectory(timage)
include_directories(include)
set(TSOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cmdline.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lodepng.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tdraw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/timage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tinput.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tmatrix4x4.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tmodel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tvector3d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tvector4d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tdraw.h
  )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(trender "${TSOURCES}")
#target_link_libraries(trender TMath TDraw TInput TModel Lodepng TImage)
