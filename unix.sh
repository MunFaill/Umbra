#!/bin/bash

read -r -p "Whant to compile premake?(y/N): " pyn

if [[ "$pyn" == "Y" || "$pyn" == "y" ]]; then
	Vendor/premake-core/Bootstrap.sh
fi

read -r -p "Generate compile commands? (y/N): " ccyn

if [[ "$ccyn" == "Y" || "$ccyn" == "y" ]]; then
	Vendor/premake-core/bin/release/premake5 compilecommands
fi

#GLFW
cmake -S Vendor/glfw -B Vendor/glfw/build
make -C Vendor/glfw/build -j$(nproc)

#FLECS
cmake -S Vendor/flecs -B Vendor/flecs/build
make -C Vendor/flecs/build -j$(nproc)

Vendor/premake-core/bin/release/premake5 ninja
ninja -j$(nproc)