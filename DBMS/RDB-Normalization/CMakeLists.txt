cmake_minimum_required(VERSION 3.14)
project(Normalization VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")

include_directories(include)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)