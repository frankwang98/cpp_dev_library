#!/bin/bash
cd ./build/ #&& rm -rf *
cmake ..
make
echo ----- Program compile complete! -----