# Asset Converter cmake file
cmake_minimum_required(VERSION 2.8)
project(AssetConverter CXX)

# Private
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/source/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Dependencies
include_directories(${Core_INCLUDE_DIRS} ${Resource_INCLUDE_DIRS} ${Engine_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Core Resource Engine)
