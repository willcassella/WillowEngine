# Root CMake file
cmake_minimum_required(VERSION 2.8)

# Set output directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Set linux options
if(${UNIX})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic")
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    find_package(PkgConfig REQUIRED)
endif()
    
# Add Core projects
add_subdirectory(Modules/Core)
add_subdirectory(Tests/CoreTest)

# Add Resource project
add_subdirectory(Modules/Resource)

# Add engine project
add_subdirectory(Modules/Engine)

# Add AssetConverter project
add_subdirectory(Tools/AssetConverter)

# Add GLRender project
add_subdirectory(Services/GLRender)

# Add ExampleGame project
add_subdirectory(Games/ExampleGame)

# Add Client project
add_subdirectory(Runtimes/Client)
