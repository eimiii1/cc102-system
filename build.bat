@echo off

if not exist build (
    mkdir build
)

g++ src\test.cpp src\Cinema.cpp src\Movie.cpp -Iinclude -o build\main.exe

if %ERRORLEVEL% == 0 (
    echo Compilation Successful!
    echo Running Program...
    build\main.exe
)

echo.
pause