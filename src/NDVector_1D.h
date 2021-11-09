#pragma once

#include "NDVector_ND.h"
#include "typedef.h"
#include <deque>
#include <array>

/*
  Class template NDVector<T,1>.
  Specialization of NDVector<T,N> that provides
  a 1-dimensional std::deque-like structure whose
  range may begin at any positive or negative index.
*/
template <typename T>
class NDVector<T,1> : private std::deque<T> {
private:
    using ValueType = T;
    using ElementType = T;
    using ContainerType = std::deque<ElementType>;

public:
    NDVector() = default;
    
    NDVector(const size_t size);
    NDVector(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1);
    NDVector(const lim_t i0, const lim_t i1);
    
    NDVector(const NDVector& rhs);
    NDVector& operator=(const NDVector& rhs);
    
    NDVector& operator=(const T& value);
    void fill(const T value);

    lim_t lim0();
    lim_t lim1();
    using ContainerType::size;

    void rebound(const size_t size);
    void reboundFirstIndex(const lim_t i0);
    void rebound(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1);
    void rebound(const lim_t i0, const lim_t i1);
    
    void resize(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1);
    void resize(const lim_t i0, const lim_t i1);

    void push_back(const T value);
    void push_front(const T value);
    template<class... Args> void emplace_back(Args&&... args);
    template<class... Args> void emplace_front(Args&&... args);
    void pop_back();
    void pop_front();

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
    using ContainerType::shrink_to_fit;

//private:
    ContainerType& getVector();
    const ContainerType& getVector() const;

private:
    void movedPoint();

private:
    ElementType* moved_ptr = nullptr;
    std::array<lim_t, 2> lims;

};

template <typename T>
class NDVector<T,0>{
private:
    T value;
public:
    operator T () {return value;}
    operator T&() {return value;}
    operator const T () const {return value;}
    operator const T&() const {return value;}
    operator volatile T () volatile {return value;}
    operator volatile T&() volatile {return value;}
    operator const volatile T () const volatile {return value;}
    operator const volatile T&() const volatile {return value;}
};

