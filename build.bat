@echo off
echo Check build results in files:
echo  - output.log 
echo  - error.log
g++ .\main.cpp -o main.exe 2> error.log
