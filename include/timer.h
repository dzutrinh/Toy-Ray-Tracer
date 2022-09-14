#ifndef __TIMER_H__
#define __TIMER_H__

#if defined(__USE_OPENMP__)
    #include <omp.h>
#else
    #include <ctime>
#endif

class timer {
public:
    timer() { reset(); }
    ~timer() { reset(); }

    void reset() { start_time = stop_time = 0.0f; }
    
    void start() {
#if defined(__USE_OPENMP__)
        start_time = omp_get_wtime();
#else
        start_time = clock();
#endif
    }

    void stop() {
#if defined(__USE_OPENMP__)
        stop_time = omp_get_wtime();
#else
        stop_time = clock();
#endif
    }

    double ellapsed() {
        double e = double(stop_time - start_time);
#if !defined(__USE_OPENMP__)
        e /= CLOCKS_PER_SEC;
#endif
        return e;
    }

private:
#if defined(__USE_OPENMP__)
    double  start_time;
    double  stop_time;
#else
    clock_t  start_time;
    clock_t  stop_time;
#endif
};

#endif

