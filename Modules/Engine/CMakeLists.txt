# Engine project cmake file
cmake_minimum_required(VERSION 3.2.2)
project(Engine LANGUAGES CXX)

# Private
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/source/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Dependencies
pkg_check_modules(Bullet bullet REQUIRED)
include_directories(SYSTEM ${Bullet_STATIC_INCLUDE_DIRS}) # Supress warnings from Bullet headers
include_directories(${Core_INCLUDE_DIRS} ${Resource_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Core Resource ${Bullet_STATIC_LIBRARIES})

# Public
set(${PROJECT_NAME}_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
