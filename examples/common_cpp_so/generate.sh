rm -rf build

mkdir build && cd build
cmake .. && make

sleep 1
./main