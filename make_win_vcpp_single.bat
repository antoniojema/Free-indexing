@echo off

cmake^
    -B./build/win-vcpp-single/ -S./ ^
    -DCONFIG_PATH=%~dp0cmake_config\win-vcpp\ ^
    -DCONFIG_NAME=WIN_VCPP_SINGLE ^
    -DCMAKE_TOOLCHAIN_FILE=%vcpkg_dir%\scripts\buildsystems\vcpkg.cmake ^
    -DCMAKE_CONFIGURATION_TYPES=Release;Debug;MPI_Release;MPI_Debug ^
    -DCompileWithOMP=OFF ^
    -DCompileWithGTest=OFF ^
    -DCompileWithLibs=OFF
