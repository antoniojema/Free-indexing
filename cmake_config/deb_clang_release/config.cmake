set(FLAGS_DBG        "-ggdb -Wall -Wextra -Werror")
set(FLAGS_OPTIM_NONE "-O0")
set(FLAGS_OPTIM      "-O3 -Ofast")
set(FLAGS_STD        "-std=c++17")

set (CMAKE_CXX_FLAGS "${FLAGS_STD} ${FLAGS_OPTIM}")
