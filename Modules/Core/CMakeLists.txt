# Core project cmake file
cmake_minimum_required(VERSION 3.2.2)
project(Core LANGUAGES CXX)

# Private
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/source/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
add_definitions(-DCORE_BUILD)

# Public
set(${PROJECT_NAME}_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
