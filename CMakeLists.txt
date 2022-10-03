# CMake minimum version check
cmake_minimum_required(VERSION 3.11.0)

#C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# (Windows) Use folders
IF (WIN32)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
ENDIF()

# Global variables
set(ProjectName "negative-indexing")
set(ExeName     "main")
set(ExeFileName "main.cpp")

set(CONFIG_FILE "${CONFIG_PATH}config.cmake")

set(AllGTestProjects "")

# Project name
project(${ProjectName})
set(RootProjectPath "${PROJECT_SOURCE_DIR}")
message(STATUS "> Root Project Path: " ${RootProjectPath})

# Macros
include("${PROJECT_SOURCE_DIR}/cmake_config/macros.cmake")

# Enable testing
enable_testing()

# Compile options
## default
option(CompileWithOMP   "CompileWithOpenMP"     OFF)
option(CompileWithGTest "CompileWithGoogleTest" OFF)
option(CompileWithLibs  "CompileWithLibraries"  OFF)
if(CompileWithGTest)
    set(CompileWithLibs ON)
endif()
## print
message(STATUS "Compile options:")
message(STATUS "  | CompileWithOpenMP............" ${CompileWithOMP}  )
message(STATUS "  | CompileWithGoogleTest........" ${CompileWithGTest})
message(STATUS "  | CompileWithLibs.............." ${CompileWithLibs} )

# Include source code
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

# TODO All GTest projects
message(STATUS ${CMAKE_BINARY_DIR})
file(REMOVE ${CMAKE_BINARY_DIR}/tests_list.txt)
foreach(dir ${AllGTestProjects})
    write_file(${CMAKE_BINARY_DIR}/tests_list.txt ${dir} APPEND)
endforeach()