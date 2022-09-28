/*
    Developers: Miguel D. Ruiz-Cabello. Antonio J. Martin Valverde
    Institution: UGR, Electromagnetic group of Granada
    Proyect: FDTDpp
*/

#pragma once
#include <array>
#include <initializer_list>
#include <iostream>
#include <tuple>
#include <algorithm>
#include "globaldef.h"
#include "typedef.h"


template <typename T, size_t D >
class Box {
public:
    // Attributes
    using TypeArray =  std::array<T, D>;

    std::array<std::array<T,D>, 2 > bounds;
    std::array<T,D> & i = bounds[0];
    std::array<T,D> & e = bounds[1];
    
    // Constructors
    Box(){}

    Box (const std::array<T,D> &_i, const std::array<T,D>  &_e ) {
        this->i = _i; this->e = _e;
    }
    
    Box (const Box & rhs) {
        *this = rhs;
    }
    Box& operator = (const Box &rhs){
        this->bounds = rhs.bounds;
        return *this;
    }

    // Logical operators
    bool operator == (const Box &rhs) const{
        for (size_t lu  = 0; lu  < 2; lu ++)
        for (size_t xyz = 0; xyz < D; xyz++)
            if (this->bounds[lu][xyz] != rhs[lu][xyz])
                return false;
        return true;
    }

    bool operator != (const Box &rhs) const{
        return !((*this) == rhs);
    }

    // AJMV: Esto es para la ordenacion de Boxes cuando sea necesario
    //       Prioriza el limite inferior y el primer eje (generalmente X)
    bool operator < (const Box &rhs) const{
        for (size_t lu  = 0; lu  < 2; lu ++)
        for (size_t xyz = 0; xyz < D; xyz++)
            if (this->bounds[lu][xyz] != rhs.bounds[lu][xyz])
                return this->bounds[lu][xyz] < rhs.bounds[lu][xyz];
        return false;
    }

    // Methods
    std::array<T,D>& operator [] (const int_t i){
        return bounds[i];
    }
    const std::array<T,D>& operator [] (const int_t i) const{
        return bounds[i];
    }

    bool contains(const std::array<T, D> point, bool exclude_end = false) const {
        T sub = (exclude_end) ? 1 : 0;
        for (size_t dir = 0; dir < D; dir++)
            if (point[dir] < this->i[dir] || this->e[dir]-sub < point[dir])
                return false;
        return true;
    }

    bool isSubsetOf(const Box<T, D>& other) const {
        for (size_t dir = 0; dir < D; dir++)
            if (this->i[dir] < other.i[dir] || this->e[dir] > other.e[dir] )
                return false;
        return true;
    }

    bool isSupersetOf(const Box<T, D>& other) const {
        return other.isSubsetOf(*this);
    }

    void addPadding (const T pad){
        for (size_t n=0; n<D; ++n){
            i[n]=i[n]-pad;
            e[n]=e[n]+pad;
        }
    }

    void addPadding (const std::array<T,D> pad){
        for (size_t n=0; n<D; ++n){
            i[n]=i[n]-pad[n];
            e[n]=e[n]+pad[n];
        }
    }
};
