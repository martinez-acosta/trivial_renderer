project (trenderer)
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)

cmake_minimum_required(VERSION 3.7.2)

include_directories(tdraw tinput tmodel timage tmath lodepng)

add_executable(trender main.cpp)
