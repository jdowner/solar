set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${SOLAR_BIN_PATH})

include_directories(
  /usr/include/freetype2
  ${SOLAR_INC_PATH}
  )

link_directories(${SOLAR_LIB_PATH}/lib)

configure_file(VersionConfig.h.in ${SOLAR_INC_PATH}/VersionConfig.h)

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
  Ray.h
  Renderer.cpp
  Renderer.h
  Texture.h
  TextureManager.cpp
  TextureManager.h
  Universe.cpp
  Universe.h
  UpdateContext.h
  VersionConfig.h.in
  )

target_link_libraries(solar GL GLU ${GLFW_LIBRARIES} png ftgl yaml-cpp)
