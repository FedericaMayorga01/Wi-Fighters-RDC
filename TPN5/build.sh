mkdir build
cd build
cmake .. -DIS_SERVER=1
make
cmake .. -DIS_SERVER=0
make
cd ..

