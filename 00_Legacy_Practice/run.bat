@echo off
if "%1"=="" (
    echo Please provide the C++ filename as an argument.
    echo Example: run linkedlist.cpp
    pause
    exit /b 1
)
set file=%1
set name=%~n1

cd "C:\Users\Dell\OneDrive\Documents\C++ full course"

g++ "%file%" -o "%name%"
if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b 1
)

"%name%" < input.txt > output.txt
code output.txt
pause
