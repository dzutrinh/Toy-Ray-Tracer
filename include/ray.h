// RAY CLASS FOR RAYTRACER
// From Ray Tracing in A Weekend, Peter Shirley
#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

class ray 
{
public:
    ray() {}
    ray(const vec3 & o, const vec3 & d) { ro = o; rd = d; }
    vec3 origin() const     { return ro; }
    vec3 direction() const  { return rd; }
    vec3 point_at_parameter(float t) const { return ro + t*rd; }

private:
    vec3 ro;     // origin
    vec3 rd;     // direction
};

#endif