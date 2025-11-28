@echo off
REM === Build script for C++ project ===

set SRC=main.cpp
set OUT=myprogram.exe

echo Compiling %SRC% ...
g++ -Wall -O2 -std=c++17 %SRC% -o %OUT%

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)

echo Build successful! Run with: %OUT%
