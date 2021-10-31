

#include "Ray.hpp"
using namespace glm;

Ray::Ray(float alphaIn, float betaIn, vec3 p1, vec3 p0){
    this->alpha = alphaIn;
    this->beta = betaIn;
    this->p1 = p1;
    this->p0 = p0;
    
    
}
Ray::~Ray(){
}

Ray::Ray(){
}
