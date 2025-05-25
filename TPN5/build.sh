mkdir build
cd build
cmake .. -DIS_SERVER=1 -DUSE_UDP=0
make
cmake .. -DIS_SERVER=1 -DUSE_UDP=1
make
cmake .. -DIS_SERVER=0 -DUSE_UDP=0
make
cmake .. -DIS_SERVER=0 -DUSE_UDP=1
make
cd ..

