#####################################################################
#    Create Lib Target (called SetLibrary if CompileWithLibs=ON)    #
#####################################################################
MACRO(CreateLibTarget)
    # Establecemos el target de la libreria estatica
    GET_FILENAME_COMPONENT(LibName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(TargetName ${LibName})
    
    # Project
    project(${LibName})
    
    # Anadimos la libreria
    add_library(
        ${TargetName}
        ${HeaderList}
        ${SRCList}
        ${CML}
    )
    # Incluimos el directorio de src original
    target_include_directories(
        ${TargetName} PUBLIC
        ${RootProjectPath}/src/
    )

    # Linkeamos con todas las librerias previamente existentes
    target_link_libraries(${TargetName} ${AllLibraries})

    # Anadimos directorios internos a la build
    if(CompileWithGTest)
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/GTest)
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/GTest/CMakeLists.txt)
            add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GTest)
            message("   >> GTest: " ${CMAKE_CURRENT_SOURCE_DIR}/GTest)
        endif()
        endif()
    endif()

    if(CompileWithOMP AND UNIX)
        find_package(OpenMP REQUIRED)
        if (OPENMP_FOUND)
            message("  >> omp found")
            set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
            set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
        endif()
    endif()
    # (Windows) Gestionamos los codigos dentro del proyecto
    IF (WIN32)
        source_group("/" FILES ${SRCList} ${HeaderList})
        source_group("/CMakeLists/" FILES ${CML})
    ENDIF()

    # Parent scope
    LIST(APPEND AllLibraries ${TargetName})
    SET(AllLibraries ${AllLibraries} PARENT_SCOPE)

    # (Windows) Compile options
    IF (WIN32)
        INCLUDE(${CONFIG_FILE})
    ENDIF()
    
    # Set _DEBUG definition
    add_compile_definitions(
        "$<$<CONFIG:Debug>: _DEBUG>"
        "$<$<CONFIG:MPI_Debug>: _DEBUG>"
    )

    # (Windows) Establecemos la subcarpeta del proyecto en Visual Studio
    IF (WIN32)
        set_target_properties(
            ${TargetName}
            PROPERTIES
            FOLDER
            "src/${LibName}/"
        )
    ENDIF()

ENDMACRO()

###############################################################
#    Add To Exe (called SetLibrary if CompileWithLibs=OFF)    #
###############################################################
MACRO(AddToExe)
    # Incluimos los archivos en el ejecutable
    GET_FILENAME_COMPONENT(LibName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    target_sources(
        ${ExeName} PUBLIC
        ${HeaderList}
        ${SRCList}
        ${CML}
    )

    # (Windows) Gestionamos los codigos dentro del proyecto
    IF (WIN32)
        source_group("/${LibName}" FILES ${SRCList} ${HeaderList})
        source_group("/${LibName}/CMakeLists/" FILES ${CML})
    ENDIF()
    
    # Parent scope
    LIST(APPEND AllLibraries ${LibName})
    SET(AllLibraries ${AllLibraries} PARENT_SCOPE)

    # AllFiles
    set(HeaderList_ "")
    foreach(file ${HeaderList})
        GET_FILENAME_COMPONENT(file_ "${file}" NAME)
        GET_FILENAME_COMPONENT(file__ "./${file_}" ABSOLUTE)
        LIST(APPEND HeaderList_ ${file__})
    endforeach()

    set(SRCList_ "")
    foreach(file ${SRCList})
        GET_FILENAME_COMPONENT(file_ "${file}" NAME)
        GET_FILENAME_COMPONENT(file__ "./${file_}" ABSOLUTE)
        LIST(APPEND SRCList_ ${file__})
    endforeach()

    GET_FILENAME_COMPONENT(CML_ "${CML}" NAME)
    GET_FILENAME_COMPONENT(CML__ "./${CML_}" ABSOLUTE)

    LIST(APPEND AllFiles ${HeaderList_} ${SRCList_} ${CML__})
    SET(AllFiles ${AllFiles} PARENT_SCOPE)
ENDMACRO()

#####################################################
#    Set Library (called in each library folder)    #
#####################################################
MACRO(SetLibrary)
    message(">> SetLibrary: "  ${CMAKE_CURRENT_SOURCE_DIR})
    if(CompileWithLibs)
        message(" >> CompileWithLibs: " ${CMAKE_CURRENT_SOURCE_DIR})
        CreateLibTarget()
    else()
        message(" >> AddToExe: " ${CMAKE_CURRENT_SOURCE_DIR})
        AddToExe()
    endif()
    message("<<")
ENDMACRO()

##########################################
#    Create Main Exe (called in src/)    #
##########################################
MACRO(CreateMainExe)
    # Add executable target
    set(TargetName ${ExeName})
    add_executable(
        ${TargetName}
        ${ExeFileName}
        "CMakeLists.txt"
        "../CMakeLists.txt"
    )

    # Include this directory for the compiler
    target_include_directories (
        ${TargetName}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    # Set variables to store all static library targets and files
    set(AllLibraries "")
    set(AllFiles "")

    # Add all the source code subdirectories
    foreach(subdir ${Subdirectories})
        add_subdirectory(${subdir})
    endforeach()

    # Linkeamos all the static libraries with executable
    IF(CompileWithLibs)
        message("--------------${AllLibraries}")
        target_link_libraries(${TargetName} ${AllLibraries})
    ENDIF()

    if(CompileWithOMP AND UNIX)
        find_package(OpenMP REQUIRED)
        target_link_libraries(${GTestExeName}  OpenMP::OpenMP_CXX)
    endif()
    # (Windows) Gestionamos los codigos dentro del proyecto
    IF (WIN32)
        source_group("" FILES ${ExeFileName} "CMakeLists.txt" "../CMakeLists.txt")
        source_group(TREE "./" FILES ${AllFiles})
        foreach(file ${AllFiles})
            message("-- File : ${file}")
        endforeach()
    ENDIF()

    # Compile options
    IF (WIN32)
        INCLUDE(${CONFIG_FILE})
    ENDIF()
    
    # Set _DEBUG definition
    add_compile_definitions(
        "$<$<CONFIG:Debug>: _DEBUG>"
        "$<$<CONFIG:MPI_Debug>: _DEBUG>"
    )
ENDMACRO()

###################################################################################
#    Create GTest Target (called in every GTest folder if CompileWithGTest=ON)    #
###################################################################################
MACRO(CreateGTestTarget)
    # Obtenemos el nombre del modulo a testear
    GET_FILENAME_COMPONENT(parent_folder "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
    GET_FILENAME_COMPONENT(module ${parent_folder} NAME)

    # Creamos projecto ejecutable
    set(GTestExeName "${module}_GTest")
    set(TargetName ${GTestExeName})
    add_executable(
        ${GTestExeName}
        ${SRCList}
        ${HeaderList}
        ${ExtraList}
        ${CML}
    )

    # (Windows) Establecemos la subcarpeta del proyecto de GTest en Visual Studio
    IF (WIN32)
        set_target_properties(
            ${GTestExeName}
            PROPERTIES
            FOLDER
            "src/${module}/"
        )
    ENDIF()

    # Incluimos el directorio raiz del proyecto para el compilador
    target_include_directories(
        ${GTestExeName} PUBLIC
        ${PROJECT_SOURCE_DIR}/src/
        ${parent_folder}
    )

    # Linkeamos con la libreria anterior
    target_link_libraries(${GTestExeName} ${module})
    
    if(CompileWithOMP AND UNIX)
        find_package(OpenMP REQUIRED)
        target_link_libraries(${GTestExeName}  OpenMP::OpenMP_CXX)
    endif()

    # (Windows) Gestionamos los codigos dentro del proyecto
    IF (WIN32)
        source_group("/" FILES ${SRCList} ${HeaderList})
        source_group("/CMakeLists/" FILES ${CML})
        source_group("/Extra/" FILES ${ExtraList})
    ENDIF ()

    #######################
    ###   Google Test   ###
    #######################
    find_package(GTest REQUIRED)
    target_link_libraries(
        ${GTestExeName}
        GTest::gtest
        GTest::gtest_main
    )
    # (Windows) Usamos vcpkg en VS
    IF (WIN32)
        set_target_properties(${GTestExeName} PROPERTIES VS_GLOBAL_VcpkgEnabled true)
    ENDIF()

    # (Windows) Compile options
    IF (WIN32)
        INCLUDE(${CONFIG_FILE})
    ENDIF()
    
    # Set _DEBUG definition
    add_compile_definitions(
        "$<$<CONFIG:Debug>: _DEBUG>"
        "$<$<CONFIG:MPI_Debug>: _DEBUG>"
    )

    #####################################################
ENDMACRO()