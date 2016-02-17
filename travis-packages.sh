#!/bin/bash
set -e

# If we're compiling for GCC, download and install latest version
if [ "$CC" == "gcc" ]
then
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
    sudo apt-get update -q
    sudo apt-get install gcc-5 -y -qq
    sudo apt-get install g++-5 -y -qq
else
    # Clang has everything it needs, but we still need to update the APT package list
    sudo apt-get update -q
fi

# Download engine dependencies
sudo apt-get install -y -qq libfreeimage-dev libpugixml-dev libglew-dev libbullet-dev

# Download and compile GLFW, since it's not available in a Ubuntu repository on 14.04
sudo apt-get install -y -qq xorg-dev libglu1-mesa-dev
wget https://github.com/glfw/glfw/archive/3.1.2.tar.gz
tar -xzvf 3.1.2.tar.gz
cd glfw-3.1.2 && cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF ./ && make && sudo make install
cd ../
