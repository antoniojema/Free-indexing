set(FLAGS_DEBUG_INFO  "/Zi")                  # Debug information in PDB file
set(FLAGS_WARN        "/W4 /WX-")             # All warnings and (not) treat them as errors
set(FLAGS_RTC         "/RTCc /RTCs /RTCu")    # Run time Checks
set(FLAGS_OPTIM_NONE  "/Od /Ob0")             # No optimizations nor inlining
set(FLAGS_OPTIM       "/O2 /Ob2 /Oi /Ot /Oy") # Optimizations (favor speed) and function inlining
set(FLAGS_OPTIM_WHOLE "/GL")                  # Whole program optimizations (link-time)
set(FLAGS_FP_FAST     "/fp:fast")             # Fast floating-point
set(FLAGS_NO_OMP      "/openmp-")             # Disable OpenMP

#########################
#    vvv  DEBUG  vvv    #
#########################

set(CMAKE_CXX_FLAGS_DEBUG
    "${FLAGS_DEBUG_INFO} ${FLAGS_WARN} ${FLAGS_RTC} ${FLAGS_OPTIM_NONE} ${FLAGS_NO_OMP}"
)

add_compile_definitions(
    "$<$<CONFIG:Debug>: _ALLOW_RTCc_IN_STL>"
    "$<$<CONFIG:Debug>: ${CONFIG_NAME}>"
)

#########################
#    ^^^  DEBUG  ^^^    #
#########################

###########################
#    vvv  RELEASE  vvv    #
###########################

set(CMAKE_CXX_FLAGS_RELEASE
    "${FLAGS_OPTIM} ${FLAGS_OPTIM_WHOLE} ${FLAGS_FP_FAST} ${FLAGS_NO_OMP}"
)

add_compile_definitions(
    "$<$<CONFIG:Release>: _ALLOW_RTCc_IN_STL>"
    "$<$<CONFIG:Release>: ${CONFIG_NAME}>"
)

###########################
#    ^^^  RELEASE  ^^^    #
###########################

#############################
#    vvv  MPI DEBUG  vvv    #
#############################

set(CMAKE_CXX_FLAGS_MPI_DEBUG
    "${FLAGS_DEBUG_INFO} ${FLAGS_WARN} ${FLAGS_RTC} ${FLAGS_OPTIM_NONE} ${FLAGS_NO_OMP}"
)

add_compile_definitions(
    "$<$<CONFIG:MPI_Debug>: _ALLOW_RTCc_IN_STL>"
    "$<$<CONFIG:MPI_Debug>: CompileWithMPI>"
    "$<$<CONFIG:MPI_Debug>: ${CONFIG_NAME}>"
)

target_include_directories(
    ${TargetName}
    PUBLIC
    "$<$<CONFIG:MPI_Debug>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\include>"
)

target_link_directories(
    ${TargetName}
    PUBLIC
    "$<$<CONFIG:MPI_Debug>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\lib\\debug>"
    "$<$<CONFIG:MPI_Debug>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\lib>"
)

target_link_libraries(
    ${TargetName}
    "$<$<CONFIG:MPI_Debug>:impi.lib>"
    "$<$<CONFIG:MPI_Debug>:impicxx.lib>"
)

#############################
#    ^^^  MPI DEBUG  ^^^    #
#############################

###############################
#    vvv  MPI RELEASE  vvv    #
###############################

set(CMAKE_CXX_FLAGS_MPI_RELEASE
    "${FLAGS_OPTIM} ${FLAGS_OPTIM_WHOLE} ${FLAGS_FP_FAST} ${FLAGS_NO_OMP}"
)

add_compile_definitions(
    "$<$<CONFIG:MPI_Release>: _ALLOW_RTCc_IN_STL>"
    "$<$<CONFIG:MPI_Release>: CompileWithMPI>"
    "$<$<CONFIG:MPI_Release>: ${CONFIG_NAME}>"
)

target_include_directories(
    ${TargetName}
    PUBLIC
    "$<$<CONFIG:MPI_Release>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\include>"
)

target_link_directories(
    ${TargetName}
    PUBLIC
    "$<$<CONFIG:MPI_Release>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\lib\\release>"
    "$<$<CONFIG:MPI_Release>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\lib>"
)

target_link_libraries(
    ${TargetName}
    "$<$<CONFIG:MPI_Release>:impi.lib>"
    "$<$<CONFIG:MPI_Release>:impicxx.lib>"
)

###############################
#    ^^^  MPI RELEASE  ^^^    #
###############################
