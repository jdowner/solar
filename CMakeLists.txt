cmake_minimum_required(VERSION 2.6)

project(solar)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set(SOLAR_LIB_PATH ${CMAKE_BINARY_DIR}/lib)
set(SOLAR_BIN_PATH ${CMAKE_BINARY_DIR}/bin)
set(SOLAR_INC_PATH ${CMAKE_BINARY_DIR}/include)
set(SOLAR_RES_PATH ${CMAKE_BINARY_DIR}/share/solar)

set(SOLAR_ROOT ${CMAKE_BINARY_DIR})

option(USE_GLFW3 "Build solar using the GLFW3 library" OFF)

if(USE_GLFW3)
  add_definitions(-DUSE_GLFW3)
  find_package(GLFW3)
else()
  find_package(GLFW)
endif()

find_package(FTGL)

add_subdirectory(src)
add_subdirectory(resources)
