#pragma once

#include "typedef.h"
#include <vector>
#include <array>

/*
  Class template NDArray<T,N>.
  Provides a N-dimensional std::vector-like structure whose
  ranges may begin at any positive or negative index.
*/
template <typename T, size_t N>
class NDArray : public std::vector<NDArray<T, N-1>> {
public:
    NDArray() = default;

    NDArray(const std::initializer_list<size_t>& size);
    NDArray(const std::initializer_list<std::array<lim_t,2>>& lims);
    NDArray(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);
    
    //NDArray(const NDArray& rhs);
    //NDArray& operator=(const NDArray& rhs);

    lim_t lim0(size_t dim);
    lim_t lim1(size_t dim);
    
    void resize(const std::initializer_list<size_t>& size);
    void resize(const size_t& size...);
    void resize(const std::initializer_list<std::array<lim_t,2>>& lims);
    void resize(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);
    
    //void rebound(const lim_t i0[N], const lim_t i1[N]);
    //void rebound(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);
    //void rebound(const std::array<std::array<lim_t,2>,N>& lims);
    
    NDArray<T,N-1>& operator[](lim_t n);
    const NDArray<T,N-1>& operator[](lim_t n) const;

//private:
    std::vector<NDArray<T,N-1>>& getVector();
    const std::vector<NDArray<T,N-1>>& getVector() const;

private:
    void movedPoint();

private:
    NDArray<T,N-1>* moved_ptr = nullptr;
    std::array<std::array<lim_t, 2>, N> lims {};
};
