#ifndef __compiler_rt_int_t_h__
#define __compiler_rt_int_t_h__
#include <stdint.h>
#include <limits.h>
#ifdef _MSC_VER
#include <boost/multiprecision/cpp_int.hpp>
typedef boost::multiprecision::int128_t fixint_t;
typedef boost::multiprecision::uint128_t fixuint_t;
#else
typedef __int128 fixint_t;
typedef unsigned __int128 fixuint_t;
#endif

typedef union
{
	fixint_t all;
    struct
    {
        uint64_t low;
        int64_t high;
    }s;
} twords;

typedef union
{
	fixuint_t all;
    struct
    {
        uint64_t low;
        uint64_t high;
    }s;
} utwords;

typedef union
{
    uint64_t all;
    struct
    {
        uint32_t low;
        uint32_t high;
    }s;
} udwords;

typedef union
{
    udwords u;
    double  f;
} double_bits;


typedef fixint_t ti_int;
typedef fixuint_t tu_int;
inline ti_int __clzti2(ti_int a)
{
	twords x = {fixint_t(0)};
    x.all = a;
    const int64_t f = -(x.s.high == 0);

#ifdef _MSC_VER
	return __lzcnt64((x.s.high & ~f) | (x.s.low & f)) +
		((int32_t)f & ((int32_t)(sizeof(int64_t) * CHAR_BIT)));
#else
    return __builtin_clzll((x.s.high & ~f) | (x.s.low & f)) +
           ((int32_t)f & ((int32_t)(sizeof(int64_t) * CHAR_BIT)));
#endif
}

#endif// __compiler_rt_int_t_h__
