#pragma once

#include "NDVector_ND.h"
#include "assert.h"

/*********************/
/*    Constructor    */
/*********************/
template <typename T, size_t N>
/*inline*/ NDVector<T,N>::NDVector(const std::array<size_t, N>& size) {
    this->rebound(size);
}

template <typename T, size_t N>
/*inline*/ NDVector<T,N>::NDVector(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1) {
    this->rebound(i0, i1);
}

/**************/
/*    Copy    */
/**************/
template <typename T, size_t N>
/*inline*/ NDVector<T,N>::NDVector(const NDVector<T,N>& arr) {
    *this = arr;
}

template <typename T, size_t N>
/*inline*/ NDVector<T,N>& NDVector<T,N>::operator=(const NDVector<T,N>& rhs) {
    this->getVector() = rhs.getVector();
    this->lims = rhs.lims;
    this->moved_ptr = &this->getVector()[0];
    return *this;
}

/*************/
/*    All    */
/*************/
template <typename T, size_t N>
/*inline*/NDVector<T,N>& NDVector<T,N>::operator=(const T& value) {
    this->fill(value);
    return *this;
}

template <typename T, size_t N>
/*inline*/void NDVector<T,N>::fill(const T value) {
    for(auto& e: *this)
        e.fill(value);
}

/*****************/
/*    Rebound    */
/*****************/
template <typename T, size_t N>
/*inline*/ void NDVector<T,N>::rebound(const std::array<size_t,N>& size) {
    std::array<lim_t,N> i0;
    std::array<lim_t,N> i1;
    for (size_t i = 0; i < N; i++){
        i0[i] = 0;
        i1[i] = size[i];
    }
    this->rebound(i0, i1);
}

template <typename T, size_t N>
/*inline*/ void NDVector<T,N>::reboundFirstIndex(const std::array<lim_t,N>& i0_) {
    std::array<lim_t,N> i0;
    std::array<lim_t,N> i1;
    for (size_t i = 0; i < N; i++){
        i0[i] = i0_[i];
        i1[i] = i0_[i] + this->size(i);
    }
    this->rebound(i0, i1);
}

template <typename T, size_t N>
/*inline*/ void NDVector<T,N>::rebound(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1) {
    bool good = true;
    for (size_t i = 0; i < N; i++)
        if (i0[i] > i1[i]) {
            good = false;
            break;
        }
    if (good) {
        this->rebound1D(i0, i1);
        
        std::array<lim_t,N-1> i0_down;
        std::array<lim_t,N-1> i1_down;
        for (size_t i = 0; i < N-1; i++){
            i0_down[i] = i0[i+1];
            i1_down[i] = i1[i+1];
        }
        for (auto& e : *this)
            e.rebound(i0_down, i1_down);
    }
}

/****************/
/*    Resize    */
/****************/
template <typename T, size_t N>
/*inline*/ void NDVector<T,N>::resize(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1) {
    bool good = true;
    for (size_t i = 0; i < N; i++)
        if (i0[i] < i1[i]) {
            good = false;
            break;
        }
    if (good) {
        lim_t old_i0 = this->lims[0][0];
        lim_t old_i1 = this->lims[0][1];
        NDVector old_arr = *this;
        
        this->rebound1D(i0, i1);

        for (lim_t i = std::max(i0[0], old_i0); i < std::min(i1[0], old_i1); i++)
            (*this)[i] = old_arr[i];
        
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
/*inline*/ lim_t NDVector<T,N>::lim0(const size_t dim) {
    return lims[dim][0];
}

template <typename T, size_t N>
/*inline*/ lim_t NDVector<T,N>::lim1(const size_t dim) {
    return lims[dim][1];
}

template <typename T, size_t N>
/*inline*/ size_t NDVector<T,N>::size(const size_t dim) {
    return (size_t) (lims[dim][1]-lims[dim][0]);
}

/**********************/
/*    Push/Emplace    */
/**********************/
template <typename T, size_t N>
/*inline*/ void NDVector<T,N>::push_back(const ElementType& value) {
    this->getVector().push_back(value);
    this->lims[0][1] ++;
    this->movedPoint();
}

template <typename T, size_t N>
template<class... Args>
/*inline*/ void NDVector<T,N>::emplace_back(Args&&... args) {
    this->getVector().emplace_back(args...);
    this->lims[0][1] ++;
    this->movedPoint();
}

/***********************/
/*    Shrink To Fit    */
/***********************/
template <typename T, size_t N>
/*inline*/void NDVector<T,N>::shrink_to_fit() {
    this->getVector().shrink_to_fit();
    for (auto& e : *this)
        e.shrink_to_fit();
}

/****************/
/*    Access    */
/****************/
template <typename T, size_t N>
/*inline*/ typename NDVector<T,N>::ElementType& NDVector<T,N>::operator[](lim_t n) {
    //return this->moved_ptr[n];
    return *(this->moved_ptr + n);
}

template <typename T, size_t N>
/*inline*/ const typename NDVector<T,N>::ElementType& NDVector<T,N>::operator[](lim_t n) const {
    //return this->moved_ptr[n];
    return *(this->moved_ptr + n);
}

/********************/
/*    Get Vector    */
/********************/
template <typename T, size_t N>
/*inline*/ typename NDVector<T,N>::ContainerType& NDVector<T,N>::getVector() {
    return static_cast<ContainerType&>(*this);
}

template <typename T, size_t N>
/*inline*/ const typename NDVector<T,N>::ContainerType& NDVector<T,N>::getVector() const {
    return static_cast<const ContainerType&>(*this);
}

/*****************/
/*    Private    */
/*****************/
template <typename T, size_t N>
/*inline*/ void NDVector<T,N>::movedPoint() {
    this->moved_ptr = &this->getVector()[0] - this->lims[0][0];
}

template <typename T, size_t N>
/*inline*/ void NDVector<T,N>::rebound1D(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1) {
    for (size_t i = 0; i < N; i++) {
        this->lims[i][0] = i0[i];
        this->lims[i][1] = i1[i];
    }
    this->getVector().resize((size_t) (i1[0] - i0[0]));
    this->movedPoint();
}
