#pragma once

#include "NDArray_ND.h"

/*********************/
/*    Constructor    */
/*********************/
template <typename T, size_t N>
/*inline*/ NDArray<T,N>::NDArray(const std::initializer_list<size_t>& size) {
    if (lims.size() == N){
        this->reserve(size[0]);
        this->resize(size);
        }
}

template <typename T, size_t N>
/*inline*/ NDArray<T,N>::NDArray(const std::initializer_list<std::array<lim_t,2>>& lims) {
    if (lims.size() == N){
        this->reserve((size_t) (lims[0][1] - lims[0][0]));
        this->resize(lims);
    }
}

template <typename T, size_t N>
/*inline*/ NDArray<T,N>::NDArray(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1) {
    this->reserve((size_t) (i1[0] - i0[0]));
    this->resize(i0, i1);
}

///**************/
///*    Copy    */
///**************/
//template <typename T, size_t N>
///*inline*/ NDArray<T,N>::NDArray(const NDArray& arr) {
//    *this = arr;
//}
//
//template <typename T, size_t N>
///*inline*/ NDArray<T,N>& NDArray<T,N>::operator=(const NDArray& rhs) {
//    this->getVector() = rhs.getVector();
//    this->lims = rhs.lims;
//    this->moved_ptr = &this->getVector()[0];
//    return *this;
//}

/****************/
/*    Resize    */
/****************/
template <typename T, size_t N>
/*inline*/ void NDArray<T,N>::resize(const std::initializer_list<size_t>& size) {
    std::array<lim_t,N> i0;
    std::array<lim_t,N> i1;
    for (size_t i = 0; i < N; i++){
        i0_down[i] = 0;
        i1_down[i] = size[i];
    }
    this->resize(i0, i1)
}

template <typename T, size_t N>
/*inline*/ void NDArray<T,N>::resize(const size_t& size...) {
    // TODO
}

template <typename T, size_t N>
/*inline*/ void NDArray<T,N>::resize(const std::initializer_list<std::array<lim_t,2>>& lims) {
    std::array<lim_t,N> i0;
    std::array<lim_t,N> i1;
    for (size_t i = 0; i < N; i++){
        i0_down[i] = lims[i][0];
        i1_down[i] = lims[i][1];
    }
    this->resize(i0, i1)
}

template <typename T, size_t N>
/*inline*/ void NDArray<T,N>::resize(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1) {
    if (i1[0] >= i0[0]) {
        for (size_t i = 0; i < N; i++) {
            this->lims[i][0] = i0[i];
            this->lims[i][1] = i1[i];
        }
        
        this->getVector().resize((size_t) (i1[0] - i0[0]));
        this->movedPoint();
        
        std::array<lim_t,N-1> i0_down;
        std::array<lim_t,N-1> i1_down;
        for (size_t i = 0; i < N-1; i++){
            i0_down[i] = i0[i+1];
            i1_down[i] = i1[i+1];
        }
        for (auto& e : *this)
            e.resize(i0_down, i1_down);
    }
}

/********************/
/*    Get limits    */
/********************/
template <typename T, size_t N>
/*inline*/ lim_t NDArray<T,N>::lim0(const size_t dim) {
    return lims[dim][0];
}

template <typename T, size_t N>
/*inline*/ lim_t NDArray<T,N>::lim1(const size_t dim) {
    return lims[dim][1];
}

///*****************/
///*    Rebound    */
///*****************/
//template <typename T, size_t N>
///*inline*/ void NDArray<T,N>::rebound(const lim_t i0[N], const lim_t i1[N]) {
//    if (i1 >= i0) {
//        lim_t old_i0 = this->lim0();
//        lim_t old_i1 = this->lim1();
//        NDArray old_arr = *this;
//        
//        this->resize(i0, i1);
//        for (lim_t i = std::max(i0, old_i0); i < std::min(i1, old_i1); i++)
//            (*this)[i] = old_arr[i];
//        
//        for (lim_t i = this->lims[0][0]; i < this->lims[0][1]; i++)
//            (*this)[i].rebound(i0, i1);
//    }
//}
//
//template <typename T, size_t N>
///*inline*/ void NDArray<T,N>::rebound(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1) {
//    if (i1 >= i0) {
//        lim_t old_i0 = this->lim0();
//        lim_t old_i1 = this->lim1();
//        NDArray old_arr = *this;
//        
//        this->resize(i0, i1);
//        for (lim_t i = std::max(i0, old_i0); i < std::min(i1, old_i1); i++)
//            (*this)[i] = old_arr[i];
//        
//        for (lim_t i = this->lims[0][0]; i < this->lims[0][1]; i++)
//            (*this)[i].rebound(i0, i1);
//    }
//}
//
//template <typename T, size_t N>
///*inline*/ void NDArray<T,N>::rebound(const std::array<std::array<lim_t,2>,N>& lims) {
//    if (i1 >= i0) {
//        lim_t old_i0 = this->lim0();
//        lim_t old_i1 = this->lim1();
//        NDArray old_arr = *this;
//        
//        this->resize(lims);
//        for (lim_t i = std::max(i0, old_i0); i < std::min(i1, old_i1); i++)
//            (*this)[i] = old_arr[i];
//        
//        for (lim_t i = this->lims[0][0]; i < this->lims[0][1]; i++)
//            (*this)[i].rebound(lims);
//    }
//}

/****************/
/*    Access    */
/****************/
template <typename T, size_t N>
/*inline*/NDArray<T,N-1>& NDArray<T,N>::operator[](lim_t n) {
    //return this->moved_ptr[n];
    return *(this->moved_ptr + n);
}

template <typename T, size_t N>
/*inline*/const NDArray<T,N-1>& NDArray<T,N>::operator[](lim_t n) const {
    //return this->moved_ptr[n];
    return *(this->moved_ptr + n);
}

/********************/
/*    Get Vector    */
/********************/
template <typename T, size_t N>
/*inline*/ std::vector<NDArray<T,N-1>>& NDArray<T,N>::getVector() {
    return static_cast<std::vector<NDArray<T,N-1>>&>(*this);
}

template <typename T, size_t N>
/*inline*/ const std::vector<NDArray<T,N-1>>& NDArray<T,N>::getVector() const {
    return static_cast<const std::vector<NDArray<T,N-1>>&>(*this);
}

/*********************/
/*    Moved point    */
/*********************/
template <typename T, size_t N>
/*inline*/void NDArray<T,N>::movedPoint() {
    this->moved_ptr = &this->getVector()[0] - this->lims[0];
}
