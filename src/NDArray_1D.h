#pragma once

#include "NDArray_ND.h"
#include "typedef.h"
#include <vector>
#include <array>

/*
  Class template NDArray<T,1>.
  Specialization of NDArray<T,N> that provides
  a 1-dimensional std::vector-like structure whose
  range may begin at any positive or negative index.
*/
template <typename T>
class NDArray<T,1> : public std::vector<T> {
public:
    NDArray() = default;
    
    //NDArray(const std::array<std::array<lim_t, 2>,1> lims);
    NDArray(const size_t size);
    NDArray(const lim_t i0, const lim_t i1);
    
    NDArray(const NDArray& rhs);
    NDArray& operator=(const NDArray& rhs);

    lim_t lim0();
    lim_t lim1();

    //void resize(const std::array<std::array<lim_t, 2>,1> lims);
    void resize(const size_t size);
    void resize(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1);
    void resize(const lim_t i0, const lim_t i1);
    
    void rebound(const std::array<lim_t,1>& i0, const std::array<lim_t,1>& i1);
    void rebound(const lim_t i0, const lim_t i1);

    void push_back(const T value);
    template<class... Args> void emplace_back(Args&&... args);
    
    T& operator[](lim_t n);
    const T& operator[](lim_t n) const;

//private:
    std::vector<T>& getVector();
    const std::vector<T>& getVector() const;

private:
    void movedPoint();

private:
    T* moved_ptr = nullptr;
    std::array<lim_t, 2> lims;

};

template <typename T>
class NDArray<T,0>{
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

