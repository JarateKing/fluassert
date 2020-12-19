echo BASIC.CPP
rm a.exe
g++ -g -O2 -std=gnu++17 -static basic.cpp
./a.exe

echo FAIL.CPP
rm a.exe
g++ -g -O2 -std=gnu++17 -static fail.cpp
./a.exe
