# CMake minimum version check
cmake_minimum_required(VERSION 3.22.2)

#C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# (Windows) Use folders
IF (WIN32)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
ENDIF()

# Global variables
set(ProjectName "negative-indexing")
set(ExeName     "main.cpp")
set(ExeFileName "main.cpp")

if (WIN32)
    set(CONFIG_FILE "${CONFIG_PATH}config.cmake")
endif()

# Project name
project(${ProjectName})
set(RootProjectPath "${PROJECT_SOURCE_DIR}")
message(STATUS "> Root Project Path: " ${RootProjectPath})

# Macros
include("${PROJECT_SOURCE_DIR}/cmake_config/macros.cmake")

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
