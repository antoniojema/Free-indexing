/*
    Developers: Miguel D. Ruiz-Cabello. Antonio J. Martin Valverde
    Institution: UGR, Electromagnetic group of Granada
    Proyect: FDTDpp
*/
#pragma once
#include "typedef.h"

enum class Dir      : int_t {none = -1, x, y, z};
enum class Dim      : int_t {none = -1, undef=0, D1, D2, D3};
enum class TopoElem : int_t {none = -1, node, lin, surf, vol};
enum class Field    : int_t {none = -1, E, H};
enum class Bound    : int_t {none = -1, L, U};
enum class DirField : int_t {none = -1, Ex, Ey, Ez, Hx, Hy, Hz};
constexpr int_t DirI (const Dir  & dir) {return static_cast<int_t>(dir);}
constexpr Dir   DirI (const int_t& dir) {return static_cast<Dir>  (dir);}
constexpr int_t BoundI (const Bound &lu) {return static_cast<int_t>(lu);}

constexpr inline cplx_t cplxZero = std::complex<real_t>(0.0,0.0);
constexpr inline real_t realToleranze=1e-25; // diferencia maxima entre dos reales para ser considerados como diferentes

namespace Probe {
    constexpr inline size_t Precision = 10;
    constexpr inline size_t Size = Precision + 10;
}

constexpr char DirC(const Dir& dir, bool caps = true) {
    if (dir == Dir::x) return (caps) ? 'X' : 'x';
    if (dir == Dir::y) return (caps) ? 'Y' : 'y';
    if (dir == Dir::z) return (caps) ? 'Z' : 'z';
    return '-';
}
constexpr Dir DirC(const char& dir) {
    if (dir == 'x' || dir == 'X') return Dir::x;
    if (dir == 'y' || dir == 'Y') return Dir::y;
    if (dir == 'z' || dir == 'Z') return Dir::z;
    return Dir::none;
}
