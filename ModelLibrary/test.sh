#!/bin/sh
if ! [ -d "./tests" ]; then
	echo "Tests directory does not exist, are you in a wrong folder"
	exit 1
fi
if ! [ -d "./tests/build" ]; then 
	echo "Build directory does not exist, creating"
	mkdir ./tests/build
fi
cmake -B ./tests/build -S ./tests
cd ./tests/build
make
cd ../../
./tests/build/test_ourmodelib $(pwd)/examples/ExampleModel1.mod $(pwd)/output.mod
