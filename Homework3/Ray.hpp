

#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>
#include <glm/glm.hpp>
using namespace glm;

class Ray
{
public:
    float alpha;
    float beta;
    vec3 p0;
    vec3 p1;
    Ray(float alphaIn, float betaIn, vec3 p1, vec3 p0);
    Ray();
    virtual ~Ray();
    
};


#endif /* Ray_hpp */
