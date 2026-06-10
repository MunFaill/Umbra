#!/bin/bash

read -r -p "Whant to compile premake?(y/N): " pyn

if [[ "$pyn" == "Y" || "$pyn" == "y" ]]; then
	Vendor/premake-core/Bootstrap.sh
fi

read -r -p "Gen compile commands? (y/N): " ccyn

if [[ "$ccyn" == "Y" || "$ccyn" == "y" ]]; then
	Vendor/premake-core/bin/release/premake5 compilecommands
fi

Vendor/premake-core/bin/release/premake5 ninja
ninja -j$(nproc)