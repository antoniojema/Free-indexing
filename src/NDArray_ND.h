#pragma once

#include "typedef.h"
#include "NDVector.h"

template <typename T, size_t N>
class NDArray : private NDVector<T, N> {
private:
    using ContainerType = NDVector<T,N>;

public:
    NDArray() = default;
    
    NDArray(const std::array<size_t,N> size);
    NDArray(const std::array<lim_t,N> i0, const std::array<lim_t,N> i1);
    
    NDArray(const NDArray& rhs);

    void reset(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);
    
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

/********************/
/*   Constructor    */
/********************/
template <typename T, size_t N>
inline NDArray<T,N>::NDArray(const std::array<size_t,N> size) {
    std::array<lim_t, N> i0;
    std::array<lim_t, N> i1;
    for (size_t i = 0; i < N; i++) {
        i0[i] = 0;
        i1[i] = (lim_t) size[i];
    }
    this->reset(i0, i1);
}

template <typename T, size_t N>
inline NDArray<T,N>::NDArray(const std::array<lim_t,N> i0, const std::array<lim_t,N> i1) {
    this->reset(i0, i1);
}

/**************/
/*    Copy    */
/**************/
template <typename T, size_t N>
inline NDArray<T,N>::NDArray(const NDArray& rhs) {
    *this = rhs;
    this->getVector().shrink_to_fit();
}

/***************/
/*    Reset    */
/***************/
template <typename T, size_t N>
inline void NDArray<T,N>::reset(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1) {
    this->getVector().rebound(i0, i1);
    this->getVector().shrink_to_fit();
}

/********************/
/*    Get Vector    */
/********************/
template <typename T, size_t N>
inline typename NDArray<T,N>::ContainerType& NDArray<T,N>::getVector() {
    return static_cast<ContainerType&>(*this);
}

template <typename T, size_t N>
inline const typename NDArray<T,N>::ContainerType& NDArray<T,N>::getVector() const {
    return static_cast<const ContainerType&>(*this);
}

