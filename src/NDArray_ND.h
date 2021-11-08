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

    NDArray(const std::array<size_t,N>& size);
    NDArray(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);
    
    NDArray(const NDArray<T,N>& rhs);
    NDArray& operator=(const NDArray<T,N>& rhs);

    lim_t lim0(size_t dim);
    lim_t lim1(size_t dim);
    
    void resize(const std::array<size_t,N>& size);
    void resize(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);

    void push_back(const NDArray<T,N-1>& value);
    template<class... Args> void emplace_back(Args&&... args);
    
    void rebound(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);
    
    NDArray<T,N-1>& operator[](lim_t n);
    const NDArray<T,N-1>& operator[](lim_t n) const;

//private:
    std::vector<NDArray<T,N-1>>& getVector();
    const std::vector<NDArray<T,N-1>>& getVector() const;

private:
    void movedPoint();
    void resize1D(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);

private:
    NDArray<T,N-1>* moved_ptr = nullptr;
    std::array<std::array<lim_t, 2>, N> lims {};
};
