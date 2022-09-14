// FAST RANDOM NUMBER GENERATOR
// For Ray Tracing in A Weekend, Peter Shirley
#ifndef _RNG_H_
#define _RNG_H_

// source: https://github.com/raylee/xorshf96
// A George Marsaglia generator, period 2^96-1
static unsigned long xorshf96(void) {
	static unsigned long x=123456789, y=362436069, z=521288629;
	unsigned long t;

	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;

	z = t ^ x ^ y;
	return z;
}

inline float rng(void) {
	return (float) xorshf96() / (float) (~0UL);
}

#endif
