@echo off

where /q cmake
if errorlevel 1 (
    echo Could not find CMake.
    exit /B
) else (
    echo CMake found.
)

cmake --build .\build

@echo on
