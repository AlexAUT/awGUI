add_subdirectory(renderers)
add_subdirectory(widgets)

set(SOURCE_FILES ${SOURCE_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/gui.cpp
  PARENT_SCOPE)
