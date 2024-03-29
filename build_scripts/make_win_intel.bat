@echo off

cmake^
    -B%~dp0..\build\win_intel\ -S%~dp0..\ ^
    -G "Visual Studio 17 2022" ^
    -T "Intel C++ Compiler 19.2" ^
    -DCMAKE_C_COMPILER=icx ^
    -DCMAKE_CXX_COMPILER=icx ^
    -DCONFIG_PATH=%~dp0..\cmake_config\win_intel\ ^
    -DCONFIG_NAME=WIN_INTEL ^
    -DCMAKE_TOOLCHAIN_FILE=%vcpkg_dir%\scripts\buildsystems\vcpkg.cmake ^
    -DCMAKE_CONFIGURATION_TYPES=Release;Debug;MPI_Release;MPI_Debug ^
    -DCompileWithOMP=ON ^
    -DCompileWithGTest=ON ^
    -DCompileWithLibs=ON
