# Resource project cmake file
cmake_minimum_required(VERSION 3.2.2)
project(Resource LANGUAGES CXX)

# Private
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/source/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Dependencies
include_directories(${Core_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Core freeimage)

# Public
set(${PROJECT_NAME}_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
