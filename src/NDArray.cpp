#include "NDArray_1D_impl.h"
#include "NDArray_ND_impl.h"
#include "typedef.h"

template class NDArray<real_t, 1>;
template class NDArray<real_t, 2>;
template class NDArray<real_t, 3>;

template class NDArray<int64_t, 1>;
template class NDArray<int64_t, 2>;
template class NDArray<int64_t, 3>;

template class NDArray<int32_t, 1>;
template class NDArray<int32_t, 2>;
template class NDArray<int32_t, 3>;
