set(NANOVG_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nanovg/src" PARENT_SCOPE)
set(NANOVG_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nanovg/src")

target_include_directories(${PROJECT_NAME} PUBLIC ${NANOVG_INC_DIR})

set(NANOVG_SOURCE_FILES
  ${NANOVG_SOURCE_DIR}/nanovg.c
  )

add_library(nanovg SHARED ${NANOVG_SOURCE_FILES})
