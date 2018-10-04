add_definitions(-DNANOVG_GL3_IMPLEMENTATION)
add_definitions(-DAW_USE_OPENGL)
add_definitions(-DAW_DESKTOP)
add_executable(ex1 example1.cpp)
target_link_libraries(ex1
  nanovg
  awGUI
  )
