#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <cfloat>
#include <ctime>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include "rng.h"

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
    int nx = 1280;  // scene width
    int ny = 720;   // scene height
    int ns = 100;   // samples
    std::ofstream of;
    clock_t start_time = clock();

    of.open("out.ppm", std::ios::out | std::ios::trunc);
    of << "P3" << std::endl << nx << " " << ny << std::endl << "255" << std::endl;

    // camera setup
    vec3 lookfrom(13, 2, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10;
    float aperture = 0.1;
    camera cam( lookfrom, lookat, vec3(0, 1, 0), 
                20, float(nx)/float(ny), 
                aperture, dist_to_focus);

    // generating scene
    hitable * world = random_scene();    

    // rendering
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i+rng())/float(nx);
                float v = float(j+rng())/float(ny);
                ray r = cam.get_ray(u, v);
                col += trace(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            of << ir << " " << ig << " " << ib << std::endl;
        }
        std::cout << ".";
    }
    of.close();

    std::cout << std::endl;
    clock_t stop_time = clock();
    std::cout << "Ellapsed: " << double(stop_time - start_time) / CLOCKS_PER_SEC << std::endl;
    return 0;
}
