#pragma once
#include <cstdint>
#include <softfloat.hpp>

#ifdef _MSC_VER
#include <boost/multiprecision/cpp_int.hpp>
typedef boost::multiprecision::int128_t b_int128_t;
typedef boost::multiprecision::uint128_t b_uint128_t;
#else
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;
#endif

b_int128_t ___fixdfti(uint64_t);
b_int128_t ___fixsfti(uint32_t);
b_int128_t ___fixtfti(float128_t);
b_uint128_t ___fixunsdfti(uint64_t);
b_uint128_t ___fixunssfti(uint32_t);
b_uint128_t ___fixunstfti(float128_t);
double ___floattidf(b_int128_t);
double ___floatuntidf(b_uint128_t);

