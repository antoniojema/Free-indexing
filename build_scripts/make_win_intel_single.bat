@echo off

cmake^
    -B%~dp0..\build\win_intel_single\ -S%~dp0..\ ^
    -T "Intel C++ Compiler 19.2" ^
    -DCMAKE_C_COMPILER=icx ^
    -DCMAKE_CXX_COMPILER=icx ^
    -DCONFIG_PATH=%~dp0..\cmake_config\win_intel\ ^
    -DCONFIG_NAME=WIN_INTEL_SINGLE ^
    -DCMAKE_TOOLCHAIN_FILE=%vcpkg_dir%\scripts\buildsystems\vcpkg.cmake ^
    -DCMAKE_CONFIGURATION_TYPES=Release;Debug;MPI_Release;MPI_Debug ^
    -DCompileWithOMP=ON ^
    -DCompileWithGTest=OFF ^
    -DCompileWithLibs=OFF
