// RANDOM NUMBER GENERATOR
// For Ray Tracing in A Weekend, Peter Shirley
#ifndef _RNG_H_
#define _RNG_H_

#ifdef __APPLE__        // OSX ?
#   define rng  drand48
#else                   // MinGW, Linux
    double rng() {  
        return double(rand()) / RAND_MAX;
    }  
#endif

#endif
