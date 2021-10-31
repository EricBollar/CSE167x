#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GLUT/glut.h>
#include "Transform.h"

using namespace std;
#include "variables.h"
#include "readfile.h"

void matransform(stack<mat4> &transfstack, float* values)
{
    mat4 transform = transfstack.top();
    vec4 valvec = vec4(values[0],values[1],values[2],values[3]);
    vec4 newval = transform * valvec;
    for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack)
{
    mat4 &T = transfstack.top();
    T = T * M;
}

bool readvals(stringstream &s, const int numvals, float* values)
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

string readfile(const char* filename)
{
    string str, cmd, fname;
    ifstream in;
    in.open(filename);
    if (in.is_open()) {
        
        stack <mat4> transfstack;
        transfstack.push(mat4(1.0));  // identity
        
        getline (in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                
                stringstream s(str);
                s >> cmd;
                int i;
                float values[10];
                bool validinput;
                
                if (cmd == "light") {
                    if (numused == numLights) { // No more Lights
                        cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
                    } else {
                        validinput = readvals(s, 8, values); // Position/color for lts.
                        if (validinput) {
                            
                            for (i = 0; i < 4; i++) {
                                lightposn[i+4*numused] = values[i];
                                lightcolor[i+4*numused] = values[i+4];
                            }
                            
                            ++numused;
                        }
                    }
                }
                
                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            ambient[i] = values[i];
                            
                        }
                        ambient[3] = 1;
                    }
                } else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            diffuse[i] = values[i];
                        }
                        diffuse[3] = 1;
                    }
                } else if (cmd == "specular") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            specular[i] = values[i];
                        }
                        specular[3] = 1;
                    }
                } else if (cmd == "emission") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            emission[i] = values[i];
                        }
                        specular[3] = 1;
                    }
                } else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        shininess = values[0];
                    }
                } else if (cmd == "size") {
                    validinput = readvals(s,2,values);
                    if (validinput) {
                        w = (int) values[0]; h = (int) values[1];
                    }
                } else if (cmd == "output") {
                    s >> fname;
                    if (s.fail()) {
                        cout << "Failed reading value filename";
                    }
                } else if (cmd == "maxdepth") {
                    validinput = readvals(s,1,values);
                    if (validinput) {
                        maxdepth = values[0];
                    }
                } else if (cmd == "directional") {
                    validinput = readvals(s,6,values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            lightposn[i+4*numused] = values[i];
                            lightcolor[i+4*numused] = values[i+3];
                        }
                        lightposn[3+4*numused] = 0;
                        lightcolor[3+4*numused] = 1;
                        ++numused;
                    }
                } else if (cmd == "point") {
                    validinput = readvals(s,6,values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            lightposn[i+4*numused] = values[i];
                            lightcolor[i+4*numused] = values[i+3];
                        }
                        lightposn[3+4*numused] = 1;
                        lightcolor[3+4*numused] = 1;
                        ++numused;
                    }
                } else if (cmd == "attenuation") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            attenuation[i] = values[i];
                        }
                    }
                } else if (cmd == "camera") {
                    validinput = readvals(s,10,values);
                    if (validinput) {
                        
                        vec3 lookfrom = vec3(values[0],values[1],values[2]);
                        vec3 lookat = vec3(values[3],values[4],values[5]);
                        
                        center = lookat;
                        
                        eyeinit = lookfrom;
                        
                        vec3 directionEye = lookat - lookfrom;
                        upinit = glm::normalize(vec3(values[6],values[7],values[8]));
                        upinit = Transform::upvector(upinit,directionEye);
                        fovy = values[9];
                    }
                }
                else if(cmd == "vertex"){
                    validinput = readvals(s, 3, values);
                    vertex[numvertex]= vec3(values[0],values[1],values[2]);
                    ++numvertex;
                }
                
                else if (cmd == "sphere" || cmd == "cube" || cmd == "teapot" || cmd == "tri") {
                    if (numobjects == maxobjects) { // No more objects
                        cerr << "Reached Maximum Number of Objects " << numobjects << " Will ignore further objects\n";
                    } else {
                        object * obj = &(objects[numobjects]);
                        
                        for (i = 0; i < 4; i++) {
                            (obj->ambient)[i] = ambient[i];
                            (obj->diffuse)[i] = diffuse[i];
                            (obj->specular)[i] = specular[i];
                            (obj->emission)[i] = emission[i];
                        }
                        obj->shininess = shininess;
                        
                        obj->transform = transfstack.top();
                        
                        if (cmd == "sphere") {
                            validinput = readvals(s, 4, values);
                            if (validinput) {
                                obj->type = sphere;
                                (obj->center)[0] = values[0];
                                (obj->center)[1] = values[1];
                                (obj->center)[2] = values[2];
                                obj->size = values[3];
                            }else{
                                cerr << "ERROR sphere";
                            }
                        } else if (cmd == "cube") {
                            obj->type = cube;
                        } else if (cmd == "teapot") {
                            obj->type = teapot;
                        } else if (cmd == "tri") {
                            validinput = readvals(s, 3, values);
                            if (validinput) {
                                obj->type = triangle;
                                (obj->indices)[0] = values[0];
                                (obj->indices)[1] = values[1];
                                (obj->indices)[2] = values[2];
                            }else{
                                cerr << "ERROR triangle";
                            }
                        }
                        ++numobjects;
                    }
                }
                
                else if (cmd == "translate") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        
                        *(&transfstack.top())= transfstack.top() * Transform::translate(values[0],values[1] ,values[2]);
                        
                    }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        
                        *(&transfstack.top())= transfstack.top() * Transform::scale(values[0],values[1] ,values[2]);
                        
                    }
                }
                else if (cmd == "rotate") {
                    validinput = readvals(s,4,values);
                    if (validinput) {
                        vec3 axis=vec3(values[0],values[1],values[2]);
                        *(&transfstack.top())= transfstack.top() * mat4(Transform::rotate(values[3], axis));
                        
                    }
                }
                
                else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top());
                } else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n";
                    } else {
                        transfstack.pop();
                    }
                }
                
                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline (in, str);
        }
        
        
        eye = eyeinit;
        up = upinit;
        amount = amountinit;
        sx = sy = 1.0;
        tx = ty = 0.0;
        useGlu = false;
        
    } else {
        cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
    return fname;
}
