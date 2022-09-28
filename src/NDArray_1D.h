#pragma once

#include "typedef.h"
#include "NDVector.h"
#include "NDArray_ND.h"

template <typename T>
class NDArray<T,1> : private NDVector<T,1> {
private:
    using ContainerType = NDVector<T,1>;

public:
    NDArray() = default;
    
    NDArray(const size_t size);
    NDArray(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1);
    NDArray(const lim_t i0, const lim_t i1);
    
    NDArray(const NDArray& rhs);

    ~NDArray();

    void reset(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1);
    void reset(const lim_t i0, const lim_t i1);
    
    using ContainerType::operator[];
    using ContainerType::operator=;
    using ContainerType::fill;
    using ContainerType::lim0;
    using ContainerType::lim1;
    using ContainerType::size;
    using ContainerType::begin;
    using ContainerType::end;
    using ContainerType::rbegin;
    using ContainerType::rend;
    using ContainerType::cbegin;
    using ContainerType::cend;
    using ContainerType::crbegin;
    using ContainerType::crend;

private:
    ContainerType& getVector();
    const ContainerType& getVector() const;
};

/*********************/
/*    Constructor    */
/*********************/
template <typename T>
inline NDArray<T,1>::NDArray(const size_t size) {
    this->reset((lim_t) 0, (lim_t) size);
}

template <typename T>
inline NDArray<T,1>::NDArray(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1) {
    this->reset(i0[0], i1[0]);
}

template <typename T>
inline NDArray<T,1>::NDArray(const lim_t i0, const lim_t i1) {
    this->reset(i0, i1);
}

/**************/
/*    Copy    */
/**************/
template <typename T>
inline NDArray<T,1>::NDArray(const NDArray& rhs) {
    *this = rhs;
    this->getVector().shrink_to_fit();
}

/***************/
/*    Reset    */
/***************/
template <typename T>
inline void NDArray<T,1>::reset(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1) {
    this->reset(i0[0], i1[0]);
}

template <typename T>
inline void NDArray<T,1>::reset(const lim_t i0, const lim_t i1) {
    this->getVector().rebound(i0, i1);
    this->getVector().shrink_to_fit();
}

/********************/
/*    Get Vector    */
/********************/
template <typename T>
inline typename NDArray<T,1>::ContainerType& NDArray<T,1>::getVector() {
    return static_cast<ContainerType&>(*this);
}

template <typename T>
inline const typename NDArray<T,1>::ContainerType& NDArray<T,1>::getVector() const {
    return static_cast<const ContainerType&>(*this);
}
