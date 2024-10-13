rem @echo off
rem echo Check build results in files:
rem echo  - output.log 
rem echo  - error.log
rem g++ .\main.cpp -o main.exe 2> error.log

cd C:\repos\bank\build 
rm *.*
cmake -G "Unix Makefiles" ..
make

