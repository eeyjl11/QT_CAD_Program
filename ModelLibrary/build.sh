#!/bin/sh
if ! [ -d "./src" ]; then
	echo "Src directory does not exist, are you in a wrong folder"
	exit 1
fi
if ! [ -d "./build" ]; then 
	echo "Build directory does not exist, creating"
	mkdir ./build
fi
cmake -B ./build -S ./src
cd ./build
make
