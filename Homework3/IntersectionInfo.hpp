
#ifndef IntersectionInfo_hpp
#define IntersectionInfo_hpp

#include <stdio.h>
#include "Ray.hpp"
#include <glm/glm.hpp>
using namespace glm;

class IntersectionInfo
{
public:
    float t;
    int objindex;
    vec3 P;
    vec3 N;
    Ray * ray;
    IntersectionInfo(float t,int objindex, vec3 P, vec3 N, Ray * ray);
    virtual ~IntersectionInfo();
    
};

#endif /* IntersectionInfo_hpp */
