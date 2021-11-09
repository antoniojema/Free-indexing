#pragma once

#include "NDVector_1D.h"

/*********************/
/*    Constructor    */
/*********************/
template <typename T>
/*inline*/NDVector<T,1>::NDVector(const size_t size) {
    this->rebound(size);
}

template <typename T>
/*inline*/NDVector<T,1>::NDVector(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1) {
    this->rebound(i0, i1);
}

template <typename T>
/*inline*/NDVector<T,1>::NDVector(const lim_t i0, const lim_t i1) {
    this->rebound(i0, i1);
}

/**************/
/*    Copy    */
/**************/
template <typename T>
/*inline*/NDVector<T,1>::NDVector(const NDVector& arr) {
    *this = arr;
}

template <typename T>
/*inline*/NDVector<T,1>& NDVector<T,1>::operator=(const NDVector& rhs) {
    this->getVector() = rhs.getVector();
    this->lims = rhs.lims;
    this->movedPoint();
    return *this;
}

/*************/
/*    All    */
/*************/
template <typename T>
/*inline*/NDVector<T,1>& NDVector<T,1>::operator=(const T& value) {
    this->fill(value);
    return *this;
}

template <typename T>
/*inline*/void NDVector<T,1>::fill(const T value) {
    for(auto& e: *this)
        e = value;
}

/********************/
/*    Get limits    */
/********************/
template <typename T>
/*inline*/lim_t NDVector<T,1>::lim0() {
    return this->lims[0];
}

template <typename T>
/*inline*/lim_t NDVector<T,1>::lim1() {
    return this->lims[1];
}

/*****************/
/*    Rebound    */
/*****************/
template <typename T>
/*inline*/void NDVector<T,1>::rebound(const size_t size) {
    this->rebound((lim_t) 0, (lim_t) size);
}

template <typename T>
/*inline*/void NDVector<T,1>::reboundFirstIndex(const lim_t i0) {
    this->rebound(i0, i0 + (lim_t) this->size());
}

template <typename T>
/*inline*/void NDVector<T,1>::rebound(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1) {
    this->rebound(i0[0], i1[0]);
}

template <typename T>
/*inline*/void NDVector<T,1>::rebound(const lim_t i0, const lim_t i1) {
    if (i1 >= i0) {
        this->lims = {i0, i1};
        this->getVector().resize((size_t) i1 - i0);
        this->movedPoint();
    }
}

/****************/
/*    Resize    */
/****************/
template <typename T>
/*inline*/void NDVector<T,1>::resize(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1) {
    this->resize(i0[0], i1[0]);
}

template <typename T>
/*inline*/void NDVector<T,1>::resize(const lim_t i0, const lim_t i1) {
    if (i1 >= i0) {
        lim_t old_i0 = this->lim0();
        lim_t old_i1 = this->lim1();
        NDVector old_arr = *this;
        
        this->rebound(i0, i1);
        for (lim_t i = std::max(i0, old_i0); i < std::min(i1, old_i1); i++)
            (*this)[i] = old_arr[i];
    }
}

/**********************/
/*    Push/Emplace    */
/**********************/
template <typename T>
/*inline*/void NDVector<T,1>::push_back(const T value) {
    this->getVector().push_back(value);
    this->lims[1] ++;
    this->movedPoint();
}

template <typename T>
/*inline*/void NDVector<T,1>::push_front(const T value) {
    this->getVector().push_front(value);
    this->lims[0] --;
    this->movedPoint();
}

template <typename T>
template<class... Args>
/*inline*/void NDVector<T,1>::emplace_back(Args&&... args) {
    this->getVector().emplace_back(args...);
    this->lims[1] ++;
    this->movedPoint();
}

template <typename T>
template<class... Args>
/*inline*/void NDVector<T,1>::emplace_front(Args&&... args) {
    this->getVector().emplace_front(args...);
    this->lims[0] --;
    this->movedPoint();
}

template <typename T>
/*inline*/void NDVector<T,1>::pop_back() {
    this->getVector().pop_back();
    this->lims[1] --;
    this->movedPoint();
}

template <typename T>
/*inline*/void NDVector<T,1>::pop_front() {
    this->getVector().pop_front();
    this->lims[0] ++;
    this->movedPoint();
}

/****************/
/*    Access    */
/****************/
template <typename T>
/*inline*/typename NDVector<T,1>::ElementType& NDVector<T,1>::operator[](lim_t n) {
    //return this->moved_ptr[n];
    return *(this->moved_ptr + n);
}

template <typename T>
/*inline*/const typename NDVector<T,1>::ElementType& NDVector<T,1>::operator[](lim_t n) const {
    //return this->moved_ptr[n];
    return *(this->moved_ptr + n);
}

/********************/
/*    Get Vector    */
/********************/
template <typename T>
/*inline*/typename NDVector<T,1>::ContainerType& NDVector<T,1>::getVector() {
    return static_cast<ContainerType&>(*this);
}

template <typename T>
/*inline*/const typename NDVector<T,1>::ContainerType& NDVector<T,1>::getVector() const {
    return static_cast<const ContainerType&>(*this);
}

/*********************/
/*    Moved point    */
/*********************/
template <typename T>
/*inline*/void NDVector<T,1>::movedPoint() {
    if (this->size() > 0)
        this->moved_ptr = &this->getVector()[0] - this->lims[0];
    else
        this->moved_ptr = nullptr;
}
