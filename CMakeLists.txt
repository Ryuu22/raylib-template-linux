cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
project(NewGame)

set(raylib_VERBOSE 1)

set(SHOW_CONSOLE ON)

# REMOVE CONSOLE
# ############################################################
if(NOT SHOW_CONSOLE AND WIN32)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows /entry:mainCRTStartup")
endif()

# ############################################################

# RAYLIB
# ############################################################
find_package(raylib 4.0.0 QUIET) # QUIET or REQUIRED

if(NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
  )
  FetchContent_GetProperties(raylib)

  if(NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# ############################################################
# PROJECT
# ############################################################
include_directories(
  ${PROJECT_SOURCE_DIR}/inc
  ${PROJECT_SOURCE_DIR}/src
)

file(GLOB_RECURSE all_SRCS CONFIGURE_DEPENDS
  ${PROJECT_SOURCE_DIR}/inc/*.h
  ${PROJECT_SOURCE_DIR}/src/*.cpp

)

add_executable(${PROJECT_NAME}
  ${all_SRCS}
)

add_custom_target(copy_assets
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake
)
add_dependencies(${PROJECT_NAME} copy_assets)

target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
# ############################################################
if(${PLATFORM} STREQUAL "Web")
  # Tell Emscripten to build an example.html file.
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()
