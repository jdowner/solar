set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${SOLAR_BIN_PATH})

include_directories(
  /usr/include/freetype2
  ${SOLAR_INC_PATH}
  )

link_directories(${SOLAR_LIB_PATH}/lib)

add_definitions(-std=c++11)
add_executable(solar
  ArgumentHandler.cpp
  ArgumentHandler.h
  DataStore.cpp
  DataStore.h
  Engine.cpp
  Engine.h
  GLFW.cpp
  GLFW.h
  main.cpp
  Renderer.cpp
  Renderer.h
  Texture.h
  TextureManager.cpp
  TextureManager.h
  Universe.cpp
  Universe.h
  UpdateContext.h
  )

target_link_libraries(solar GL GLU ${GLFW_LIBRARIES} png ftgl yaml-cpp)
