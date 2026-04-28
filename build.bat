@echo off

if not exist build (
    mkdir build
)

g++ src\main.cpp build\main.exe

if %ERRORLEVEL% == 0 (
    echo Compilation Successful!
    echo Running Program...
    build\main.exe
) else (
    echo Compilaton failed!
    echo Closing Program...
)

echo.
pause