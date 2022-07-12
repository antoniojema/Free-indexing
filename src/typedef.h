#pragma once

#include <type_traits>

using real_t = double;
using int_t = int;
using sint_t = char;
using usint_t = std::make_unsigned<sint_t>::type;
using ssize_t = std::make_signed<size_t>::type;

