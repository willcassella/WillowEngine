# Core project cmake file
cmake_minimum_required(VERSION 2.8)
project(Core CXX)

# Private
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/source/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
add_definitions(-DCORE_BUILD)

# Dependencies
target_link_libraries(${PROJECT_NAME} dl)

# Public
set(${PROJECT_NAME}_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
