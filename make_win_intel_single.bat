@echo off

cmake^
    -B./build/win-intel-single/ -S./ ^
    -T "Intel C++ Compiler 19.2" ^
    -DCMAKE_C_COMPILER=icx ^
    -DCMAKE_CXX_COMPILER=icx ^
    -DCONFIG_PATH=%~dp0cmake_config\win-intel\ ^
    -DCONFIG_NAME=WIN_INTEL_SINGLE ^
    -DCMAKE_TOOLCHAIN_FILE=%vcpkg_dir%\scripts\buildsystems\vcpkg.cmake ^
    -DCMAKE_CONFIGURATION_TYPES=Release;Debug;MPI_Release;MPI_Debug ^
    -DCompileWithOMP=ON ^
    -DCompileWithGTest=OFF ^
    -DCompileWithLibs=OFF
