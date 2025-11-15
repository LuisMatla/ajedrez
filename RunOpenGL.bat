REM How to Use this bat file 
REM Follow step by step below
:: Install or Download MinGW and save it in a specific folder
:: Download Freeglut and config it below
::   -copy include and bin folder into MinGW
::   -go to "bin folder" and copy freeglut.dll into System32 and SysWOW64
:: Extract the bat.(zip) and copy it into your folder
:: Set your project name like this "main.c"
:: Run This.bat 
:: Done


REM
echo "Running \m"
gcc -c -o main.o main.c -I"C:\MinGW\include"
cls
echo "Compiling Graphic"
gcc -o main.exe main.o -L"C:\MinGW\lib" -lopengl32 -lglu32 -lfreeglut
cls
echo "App Running"
main
