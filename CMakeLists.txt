cmake_minimum_required(VERSION 3.23)
project(game)

set(CMAKE_CXX_STANDARD 98)

file(GLOB SOURCES *.cpp *.h)
add_executable(game ${SOURCES} ghost.h)
target_link_libraries(game PUBLIC winmm.lib)
target_link_libraries(game PUBLIC urlmon.lib)
