rm a.exe
echo $1
g++ -g -O2 -std=gnu++17 -static $1
./a.exe
