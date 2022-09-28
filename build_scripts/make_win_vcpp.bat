@echo off

cmake^
    -B%~dp0..\build\win_vcpp\ -S%~dp0..\ ^
    -DCONFIG_PATH=%~dp0..\cmake_config\win_vcpp\ ^
    -DCONFIG_NAME=WIN_VCPP ^
    -DCMAKE_TOOLCHAIN_FILE=%vcpkg_dir%\scripts\buildsystems\vcpkg.cmake ^
    -DCMAKE_CONFIGURATION_TYPES=Release;Debug;MPI_Release;MPI_Debug ^
    -DCompileWithOMP=OFF ^
    -DCompileWithGTest=ON ^
    -DCompileWithLibs=ON
