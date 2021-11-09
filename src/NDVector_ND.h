#pragma once

#include "typedef.h"
#include <deque>
#include <array>

/*
  Class template NDVector<T,N>.
  Provides a N-dimensional std::deque-like structure whose
  ranges may begin at any positive or negative index.
*/
template <typename T, size_t N>
class NDVector : private std::deque<NDVector<T, N-1>> {
private:
    using ValueType = T;
    using ElementType = NDVector<T, N-1>;
    using ContainerType = std::deque<ElementType>;

public:
    NDVector() = default;

    NDVector(const std::array<size_t,N>& size);
    NDVector(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);
    
    NDVector(const NDVector<T,N>& rhs);
    NDVector& operator=(const NDVector<T,N>& rhs);
    
    NDVector& operator=(const T& value);
    void fill(const T value);

    lim_t lim0(size_t dim);
    lim_t lim1(size_t dim);
    size_t size(size_t dim);
    
    void rebound(const std::array<size_t,N>& size);
    void reboundFirstIndex(const std::array<lim_t,N>& i0);
    void rebound(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);
    
    void resize(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);

    void push_back(const ElementType& value);
    void push_front(const ElementType& value);
    template<class... Args> void emplace_back(Args&&... args);
    template<class... Args> void emplace_front(Args&&... args);
    void pop_back();
    void pop_front();

    void shrink_to_fit();
    
    ElementType& operator[](lim_t n);
    const ElementType& operator[](lim_t n) const;

    using ContainerType::begin;
    using ContainerType::end;
    using ContainerType::rbegin;
    using ContainerType::rend;
    using ContainerType::cbegin;
    using ContainerType::cend;
    using ContainerType::crbegin;
    using ContainerType::crend;

//private:
    ContainerType& getVector();
    const ContainerType& getVector() const;

private:
    void movedPoint();
    void rebound1D(const std::array<lim_t,N>& i0, const std::array<lim_t,N>& i1);

private:
    ElementType* moved_ptr = nullptr;
    std::array<std::array<lim_t, 2>, N> lims {};
};
