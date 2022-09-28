# set(FLAGS_DEBUG_INFO   "/Zi")                           # Debug information in PDB file
# set(FLAGS_WARN         "/W5")                           # All warnings and (not) treat them as errors
# set(FLAGS_RTC          "/RTCc /RTCs /RTCu")             # Run time Checks
# set(FLAGS_OPTIM_NONE   "/Od /Ob0")                      # No optimizations nor inlining
# set(FLAGS_OPTIM        "/O3 /Ob2 /Oi /Ot")              # Optimizations (favor speed) and function inlining
# set(FLAGS_OPTIM_PARAL  "/Qparallel")                    # Optimizations: parallel
# set(FLAGS_OPTIM_INTEL  "/Quse-intel-optimized-headers") # Optimizations: use intel optimized headers
# set(FLAGS_OPTIM_MATMUL "/Qopt-matmul")                  # Optimizations: matrix multiplication
# set(FLAGS_OPTIM_WHOLE  "/Qipo /GA")                     # Whole program optimizations (link-time)
# set(FLAGS_FP_FAST      "/fp:fast=2")                    # Fast floating-point
# set(FLAGS_CXX_STANDARD "/std:c++17 /Qstd=c++17")        # C++ standard
# if(CompileWithOMP)
#     set(FLAGS_OMP "/openmp /Qopenmp")                   # Enable OpenMP
#     set(DEFINE_OMP "CompileWithOMP")
# endif()

# #########################
# #    vvv  DEBUG  vvv    #
# #########################

# set(CMAKE_CXX_FLAGS_DEBUG
#     "${FLAGS_DEBUG_INFO} ${FLAGS_WARN} ${FLAGS_RTC} ${FLAGS_OPTIM_NONE} ${FLAGS_CXX_STANDARD}"
# )

# add_compile_definitions(
#     "$<$<CONFIG:Debug>: _ALLOW_RTCc_IN_STL>"
#     "$<$<CONFIG:Debug>: ${CONFIG_NAME}>"
# )

# #########################
# #    ^^^  DEBUG  ^^^    #
# #########################

# ###########################
# #    vvv  RELEASE  vvv    #
# ###########################

# set(CMAKE_CXX_FLAGS_RELEASE
#     "${FLAGS_OPTIM} ${FLAGS_OPTIM_WHOLE} ${FLAGS_OPTIM_PARAL} ${FLAGS_OPTIM_INTEL} ${FLAGS_OPTIM_MATMUL} ${FLAGS_OPTIM_WHOLE} ${FLAGS_FP_FAST} ${FLAGS_OMP} ${FLAGS_CXX_STANDARD}"
# )

# add_compile_definitions(
#     "$<$<CONFIG:Release>: _ALLOW_RTCc_IN_STL>"
#     "$<$<CONFIG:Release>: ${CONFIG_NAME}>"
#     "$<$<CONFIG:Release>: ${DEFINE_OMP}>"
# )

# ###########################
# #    ^^^  RELEASE  ^^^    #
# ###########################

# #############################
# #    vvv  MPI DEBUG  vvv    #
# #############################

# set(CMAKE_CXX_FLAGS_MPI_DEBUG
#     "${FLAGS_DEBUG_INFO} ${FLAGS_WARN} ${FLAGS_RTC} ${FLAGS_OPTIM_NONE} ${FLAGS_CXX_STANDARD}"
# )

# add_compile_definitions(
#     "$<$<CONFIG:MPI_Debug>: _ALLOW_RTCc_IN_STL>"
#     "$<$<CONFIG:MPI_Debug>: CompileWithMPI>"
#     "$<$<CONFIG:MPI_Debug>: ${CONFIG_NAME}>"
# )

# target_include_directories(
#     ${TargetName}
#     PUBLIC
#     "$<$<CONFIG:MPI_Debug>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\include>"
# )

# target_link_directories(
#     ${TargetName}
#     PUBLIC
#     "$<$<CONFIG:MPI_Debug>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\lib\\debug>"
#     "$<$<CONFIG:MPI_Debug>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\lib>"
# )

# target_link_libraries(
#     ${TargetName}
#     "$<$<CONFIG:MPI_Debug>:impi.lib>"
#     "$<$<CONFIG:MPI_Debug>:impicxx.lib>"
# )

# #############################
# #    ^^^  MPI DEBUG  ^^^    #
# #############################

# ###############################
# #    vvv  MPI RELEASE  vvv    #
# ###############################

# set(CMAKE_CXX_FLAGS_MPI_RELEASE
#     "${FLAGS_OPTIM} ${FLAGS_OPTIM_WHOLE} ${FLAGS_OPTIM_PARAL} ${FLAGS_OPTIM_INTEL} ${FLAGS_OPTIM_MATMUL} ${FLAGS_OPTIM_WHOLE} ${FLAGS_FP_FAST} ${FLAGS_OMP} ${FLAGS_CXX_STANDARD}"
# )

# add_compile_definitions(
#     "$<$<CONFIG:MPI_Release>: _ALLOW_RTCc_IN_STL>"
#     "$<$<CONFIG:MPI_Release>: CompileWithMPI>"
#     "$<$<CONFIG:MPI_Release>: ${CONFIG_NAME}>"
#     "$<$<CONFIG:MPI_Release>: ${DEFINE_OMP}>"
# )

# target_include_directories(
#     ${TargetName}
#     PUBLIC
#     "$<$<CONFIG:MPI_Release>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\include>"
# )

# target_link_directories(
#     ${TargetName}
#     PUBLIC
#     "$<$<CONFIG:MPI_Release>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\lib\\release>"
#     "$<$<CONFIG:MPI_Release>:D:\\Program Files (x86)\\Intel\\oneAPI\\mpi\\2021.3.0\\lib>"
# )

# target_link_libraries(
#     ${TargetName}
#     "$<$<CONFIG:MPI_Release>:impi.lib>"
#     "$<$<CONFIG:MPI_Release>:impicxx.lib>"
# )

# ###############################
# #    ^^^  MPI RELEASE  ^^^    #
# ###############################
