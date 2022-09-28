
# Take all headers, cpps and CMakeLists
set(HeaderList
    "box.h"
    "log.h"
    "NDArray.h"
    "NDArray_impl.h"
    "NDVector.h"
    "NDVector_impl.h"
    "typedef.h"
)

set(SRCList
    "log.cpp"
)

SET(CML "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")

SetLibrary()
