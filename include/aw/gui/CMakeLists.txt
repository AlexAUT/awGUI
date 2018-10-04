add_subdirectory(renderers)
add_subdirectory(widgets)

set(HEADER_FILES ${HEADER_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/gui.hpp
  PARENT_SCOPE)
