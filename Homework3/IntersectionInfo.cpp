
#include "IntersectionInfo.hpp"
#include "Ray.hpp"
IntersectionInfo::IntersectionInfo(float t, int objindex, vec3 P, vec3 N, Ray * ray){
    this->t = t;
    this->objindex = objindex;
    this->P = P;
    this->N = N;
    this->ray = ray;
}

IntersectionInfo::~IntersectionInfo(){
    
}
