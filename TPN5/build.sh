mkdir build
cd build
cmake ..
make
head -c 32 /dev/urandom | base64 > key.txt
cd ..

