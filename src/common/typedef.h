/*
    Developers: Miguel D. Ruiz-Cabello. Antonio J. Martin Valverde
    Institution: UGR, Electromagnetic group of Granada
    Proyect: FDTDpp
*/
#pragma once
#include <cstddef>
#include <type_traits>
#include <complex>
#include <vector>

using sg_t = unsigned char;

using real_t = double;
using cplx_t = std::complex<real_t>;
using ccplx_t = const std::complex<real_t>;
using creal_t = const real_t;
using int_t  = int;
using sint_t = short;

using matInt_t = unsigned short;


using uint_t = std::make_unsigned<int_t>::type;
using usint_t = std::make_unsigned<sint_t>::type;
using ssize_t = std::make_signed<size_t>::type;
using csize_t = const size_t;
using cssize_t = const ssize_t;

using MPICommEntry = std::vector<std::pair<size_t, size_t>>;
using CommunicationTable = std::vector<MPICommEntry>;
