#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cfloat>
#if defined(__USE_OPENMP__)
    #include <omp.h>
#endif
#include "include/sphere.h"
#include "include/hitable_list.h"
#include "include/camera.h"
#include "include/material.h"
#include "include/rng.h"
#include "include/bitmap.h"
#include "include/timer.h"

using namespace std;

#define OUTPUT_NAME ("output.ppm")
#define ROUND8(x)   int(255.99f * x)

vec3 trace(const ray & r, hitable * world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && 
            rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * trace(scattered, world, depth+1);
        else
            return vec3(0, 0, 0);
    }

    vec3 ud = normalize(r.direction());
    float t = 0.5 * (ud.y() + 1.0);
    return  (1.0-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

hitable * random_scene() {
    int n = 500;
    hitable ** list = new hitable*[n+1];
    list[0] =  new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1; 
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = rng();
            vec3 center(a+0.9*rng(), 0.2, b+0.9*rng()); 
            if ((center-vec3(4, 0.2, 0)).length() > 0.9) { 
                if (choose_mat < 0.8)       // diffuse
                    list[i++] = new sphere(center, 0.2, 
                                           new lambertian(vec3(rng()*rng(), 
                                                               rng()*rng(), 
                                                               rng()*rng())));
                else if (choose_mat < 0.95) // metal
                    list[i++] = new sphere(center, 0.2,
                                           new metal(vec3(0.5*(1 + rng()), 
                                                          0.5*(1 + rng()), 
                                                          0.5*(1 + rng())), 0.5*rng()));
                else                        // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
            }
        }
    }
    list[i++] = new sphere(vec3( 0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3( 4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list,i);
}

int main() {    
    int nx = 1280;      // scene width
    int ny = 720;       // scene height
    int ns = 100;       // #samples
    bitmap bmp;         // for saving the rendered result
    timer tm;           // for benchmarking purposes
    int current = 0,    // progress counter
        total = ny;

    cout << "Creating bitmap: ";
    if (!bmp.create(nx, ny)) {
        cout << "failed." << endl;
        return -1;
    }
    else
        cout << "ok (" << nx << " x " << ny << ")" << endl;
    cout << "No. samples    : " << ns << endl;

    // start timing
    tm.start();

    // camera setup
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10;
    float aperture = 0.1;
    camera cam( lookfrom, lookat, vec3(0, 1, 0), 20, float(nx)/float(ny),
                aperture, dist_to_focus);

    // generating scene
    hitable * world = random_scene();

    // display OpenMP info
    cout << fixed << setprecision(0);
    cout << "Use OpenMP     : ";
#if defined(__USE_OPENMP__)
    int nthreads = omp_get_max_threads();
    cout << "yes (max. " << nthreads << " threads)" << endl;
    #pragma omp parallel for
#else
    cout << "no" << endl;
#endif   

    // main rendering loop
    for (int j = ny-1; j >= 0; j--) {           // bottom-up scanlines
        for (int i = 0; i < nx; i++) {          // left-right pixel
            vec3 col(0, 0, 0);                  // current pixel color
            for (int s = 0; s < ns; s++) {      // sampling nearby pixels
                float u = float(i+rng())/float(nx);
                float v = float(j+rng())/float(ny);
                col += trace(cam.get_ray(u, v), world, 0);
            }  
            col /= float(ns);                   // average out
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            // set pixel onto the bitmap
            bmp.plot(i, ny-j-1, ROUND8(col[0]), ROUND8(col[1]), ROUND8(col[2]));
        }
        // pacifier :)
        current++;
        cout << "\rRendering scene: " << setw(4) << 100.0f * current/total << "%\r" << flush;
    }
    cout << endl;
    
    // stop timing
    tm.stop();

    // save rendered result
    cout << "Saving image   : ";
    if (bmp.save(OUTPUT_NAME))
        cout << "done! (" << OUTPUT_NAME << ")" << endl;
    else
        cout << "failed!" << endl;

    // display ellapsed time
    double ellapsed = tm.ellapsed();
    cout << "Ellapsed time  : " << setprecision(3) << ellapsed << endl;
    
    return 0;
}
