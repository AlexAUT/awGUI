cmake_minimum_required(VERSION 3.6)

project(awGUI VERSION 0.0.1 DESCRIPTION "Gui from the AW eco system")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

set(AW_REVOLT_PROJECT_DIR "" CACHE PATH "Folder of awRevolt repository")
set(AW_BUILD_GRAPHICS OFF)
set(AW_BUILD_ENGINE OFF)
set(AW_BUILD_REFLECTION OFF)
add_subdirectory(${AW_REVOLT_PROJECT_DIR} "awRevolt")

set(INC_DIR "include")
set(SRC_DIR "src")

set(INC_DIR_GUI "${INC_DIR}/aw/gui")
set(SRC_DIR_GUI "${SRC_DIR}/aw/gui")

set(HEADER_FILES)
set(SOURCE_FILES)

add_subdirectory(${INC_DIR_GUI})
add_subdirectory(${SRC_DIR_GUI})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

include_directories(${INC_DIR})
include_directories("/usr/local/include")
include_directories(${GLM_INCLUDE_PATH})
#link_directories("/usr/local/lib64")

add_subdirectory(dependencies)

include_directories(${NANOVG_INC_DIR})

add_definitions(-DNANOVG_GL3_IMPLEMENTATION)

target_link_libraries(${PROJECT_NAME}
  nanovg
  awUtils
)

# Install library
include (GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install (
  DIRECTORY ${INC_DIR_GUI}
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*")
install (
  DIRECTORY ${INC_DIR_GUI}
  DESTINATION include
  FILES_MATCHING PATTERN "*.inl")


set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${NANOVG_INC_DIR})

#enable warnings
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif(MSVC)

if(BUILD_EXAMPLES)
  add_subdirectory("examples")
endif()

