cmake_minimum_required(VERSION 3.6)

project(awGUI VERSION 0.0.1 DESCRIPTION "Gui from the AW eco system")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")


set(INC_DIR "include")
set(SRC_DIR "src")

set(INC_DIR_GUI "${INC_DIR}/aw/gui")
set(SRC_DIR_GUI "${SRC_DIR}/aw/gui")

set(HEADER_FILES)
set(SOURCE_FILES)

add_subdirectory(${INC_DIR_GUI})
add_subdirectory(${SRC_DIR_GUI})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

include_directories("/usr/local/include")
#link_directories("/usr/local/lib64")

add_subdirectory(dependencies)

include_directories(${NANOVG_INC_DIR})

add_definitions(-DNANOVG_GL3_IMPLEMENTATION)
add_definitions(-DAW_USE_OPENGL)
add_definitions(-DAW_DESKTOP)

target_link_libraries(${PROJECT_NAME}
  assimp
  jsoncpp-d
  sfml-window
  sfml-system
  nanovg
  awRevolt
  GL
)

# Install library
include (GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install (
  DIRECTORY ${INC_DIR_AW}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*")
install (
  DIRECTORY ${INC_DIR_AW}
  DESTINATION include
  FILES_MATCHING PATTERN "*.inl")


set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})

#enable warnings
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif(MSVC)

if(BUILD_EXAMPLES)
  add_subdirectory("examples")
endif()

