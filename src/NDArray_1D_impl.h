#pragma once

#include "NDArray_1D.h"

/*********************/
/*    Constructor    */
/*********************/
//template <typename T>
///*inline*/NDArray<T,1>::NDArray(const std::array<std::array<lim_t, 2>,1> lims) {
//    this->reserve((size_t) (lims[0][1] - lims[0][0]));
//    this->resize(lims);
//}

template <typename T>
/*inline*/NDArray<T,1>::NDArray(const size_t size) {
    this->reserve(size);
    this->resize(size);
}

template <typename T>
/*inline*/NDArray<T,1>::NDArray(const lim_t i0, const lim_t i1) {
    this->reserve((size_t) (i1 - i0));
    this->resize(i0, i1);
}

/**************/
/*    Copy    */
/**************/
template <typename T>
/*inline*/NDArray<T,1>::NDArray(const NDArray& arr) {
    *this = arr;
}

template <typename T>
/*inline*/NDArray<T,1>& NDArray<T,1>::operator=(const NDArray& rhs) {
    this->getVector() = rhs.getVector();
    this->lims = rhs.lims;
    this->movedPoint();
    return *this;
}

/****************/
/*    Resize    */
/****************/
template <typename T>
/*inline*/void NDArray<T,1>::resize(const size_t size) {
    this->resize((lim_t) 0, (lim_t) size);
}

template <typename T>
/*inline*/void NDArray<T,1>::resize(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1) {
    this->resize(i0[0], i1[0]);
}

template <typename T>
/*inline*/void NDArray<T,1>::resize(const lim_t i0, const lim_t i1) {
    if (i1 >= i0) {
        this->lims = {i0, i1};
        this->getVector().resize((size_t) i1 - i0);
        this->movedPoint();
    }
}

/********************/
/*    Get limits    */
/********************/
template <typename T>
/*inline*/lim_t NDArray<T,1>::lim0() {
    return this->lims[0];
}

template <typename T>
/*inline*/lim_t NDArray<T,1>::lim1() {
    return this->lims[1];
}

/*****************/
/*    Rebound    */
/*****************/
template <typename T>
/*inline*/void NDArray<T,1>::rebound(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1) {
    this->rebound(i0[0], i1[0]);
}

template <typename T>
/*inline*/void NDArray<T,1>::rebound(const lim_t i0, const lim_t i1) {
    if (i1 >= i0) {
        lim_t old_i0 = this->lim0();
        lim_t old_i1 = this->lim1();
        NDArray old_arr = *this;
        
        this->resize(i0, i1);
        for (lim_t i = std::max(i0, old_i0); i < std::min(i1, old_i1); i++)
            (*this)[i] = old_arr[i];
    }
}

/***************************/
/*    Push/Emplace back    */
/***************************/
template <typename T>
/*inline*/void NDArray<T,1>::push_back(const T value) {
    this->getVector().push_back(value);
    this->lims[1] ++;
    this->movedPoint();
}

template <typename T>
template<class... Args>
/*inline*/void NDArray<T,1>::emplace_back(Args&&... args) {
    this->getVector().emplace_back(args...);
    this->lims[1] ++;
    this->movedPoint();
}

/****************/
/*    Access    */
/****************/
template <typename T>
/*inline*/T& NDArray<T,1>::operator[](lim_t n) {
    //return this->moved_ptr[n];
    return *(this->moved_ptr + n);
}

template <typename T>
/*inline*/const T& NDArray<T,1>::operator[](lim_t n) const {
    //return this->moved_ptr[n];
    return *(this->moved_ptr + n);
}

/********************/
/*    Get Vector    */
/********************/
template <typename T>
/*inline*/std::vector<T>& NDArray<T,1>::getVector() {
    return static_cast<std::vector<T>&>(*this);
}

template <typename T>
/*inline*/const std::vector<T>& NDArray<T,1>::getVector() const {
    return static_cast<const std::vector<T>&>(*this);
}

/*********************/
/*    Moved point    */
/*********************/
template <typename T>
/*inline*/void NDArray<T,1>::movedPoint() {
    this->moved_ptr = &this->getVector()[0] - this->lims[0];
}
