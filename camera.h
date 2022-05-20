// CAMERA CLASS FOR RAYTRACER
// From Ray Tracing in A Weekend, Peter Shirley
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ray.h"
#include "rng.h"

vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0*vec3(rng(), rng(), 0.0) - vec3(1, 1, 0);
    } while(dot(p, p) >= 1.0);
    return p;
}

class camera {
public:
    camera( vec3 lookfrom, vec3 lookat, vec3 vup, 
            float vfov, float aspect, float aperture, float focus_dist) {
        lens_radius = aperture / 2;
        float theta = vfov * M_PI/180.0;
        float half_height = tan(theta/2); 
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = normalize(lookfrom - lookat);
        u = normalize(cross(vup, w));
        v = cross(w, u);

        lower_left =    origin - 
                        half_width *  focus_dist * u - 
                        half_height * focus_dist * v - 
                                      focus_dist * w;
        horz = 2 * half_width * focus_dist * u;
        vert = 2 * half_height * focus_dist * v;
    }

    ray get_ray(float s, float t) {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin+offset, lower_left + s*horz + t*vert - origin - offset); 
    }

private:
    vec3 origin;
    vec3 lower_left;
    vec3 horz;
    vec3 vert;
    vec3 u, v, w;
    float lens_radius;
};

#endif
