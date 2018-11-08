#ifndef __compiler_rt_fp_128_h__
#define __compiler_rt_fp_128_h__

#include <limits.h>
#include <stdint.h>
#include "../softfloat/source/include/softfloat.h"
#ifdef _MSC_VER
#include <boost/multiprecision/cpp_int.hpp>
typedef boost::multiprecision::int128_t int128_t;
typedef boost::multiprecision::uint128_t uint128_t;
#endif

#ifdef _MSC_VER
#define REP_C (int128_t)
#else
#define REP_C (__int128)
#endif
#define significandBits 112
#ifdef _MSC_VER
#define typeWidth       (sizeof(int128_t)*CHAR_BIT)
#else
#define typeWidth       (sizeof(__int128)*CHAR_BIT)
#endif
#define exponentBits    (typeWidth - significandBits - 1)
#define maxExponent     ((1 << exponentBits) - 1)
#define exponentBias    (maxExponent >> 1)

#define implicitBit     (REP_C(1) << significandBits)
#define significandMask (implicitBit - 1U)
#define signBit         (REP_C(1) << (significandBits + exponentBits))
#define absMask         (signBit - 1U)
#define exponentMask    (absMask ^ significandMask)
#define oneRep          ((rep_t)exponentBias << significandBits)
#define infRep          exponentMask
#define quietBit        (implicitBit >> 1)
#define qnanRep         (exponentMask | quietBit)

#ifdef _MSC_VER
static __inline int128_t toRep(float128_t x) {
	union { float128_t f; int128_t i; } rep = { x };
    return rep.i;
}
#else
static __inline __int28 toRep(float128_t x) {
	const union { float128_t f; __int28 i; } rep = { .f = x };
	return rep.i;
}
#endif

#endif //__compiler_rt_fp_h__
