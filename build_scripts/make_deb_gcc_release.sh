COMPILER_C="gcc"
COMPILER_CXX="g++"
CONFIG="Release"
CONFIG_NAME="deb_gcc_release"

PROJECT_DIR="$(dirname $(dirname $(readlink -f $0)))"
if [ "${PROJECT_DIR}" != "/" ] && [ "${PROJECT_DIR#${PROJECT_DIR%?}}" != "/" ]; then
    PROJECT_DIR="${PROJECT_DIR}/"
fi

cmake \
    -B"${PROJECT_DIR}build/${CONFIG_NAME}" -S"${PROJECT_DIR}" \
    -DCMAKE_BUILD_TYPE="$CONFIG" \
    -DCONFIG_PATH="${PROJECT_DIR}cmake_config/${CONFIG_NAME}/" \
    -DCMAKE_C_COMPILER="/usr/bin/$COMPILER_C" \
    -DCMAKE_CXX_COMPILER="/usr/bin/$COMPILER_CXX" \
    -DCompileWithOMP="OFF" \
    -DCompileWithGTest="ON" \
    -DCompileWithLibs="ON"
