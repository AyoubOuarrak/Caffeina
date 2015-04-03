/*
*  Copyright (C) 2014 Ayoub Ouarrak, ouarrakayoub@gmail.com
*
*  This file is part of Caffeina.
*
*  Caffeina is free software: you can redistribute it and/or modify it under the terms of 
*  the GNU General Public License as published by the Free Software Foundation, either 
*  version 3 of the License, or (at your option) any later version. Caffeina is distributed 
*  in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
*  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
*  Public License for more details. You should have received a copy of the GNU General 
*  Public License along with Caffeina. If not, see http://www.gnu.org/licenses/.
*/

#ifndef LIGHT_GUARD_HH
#define LIGHT_GUARD_HH

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#elif defined __linux__ || defined _WIN32 || defined _WIN64
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <algorithm>
#include <iostream>
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace Caffeina {

class Light {

private:
   Vec4<float> lightPosition;
   Vec3<float> specularComponent;
   Vec3<float> ambientComponent;
   Vec3<float> diffuseComponent;

   Vec3<float> diffuseMaterial; 
   Vec3<float> specularMaterial; 
   Vec3<float> emissiveMaterial; 
   Vec3<float> blankMaterial;
   
   // set the shininess of the material
   float mShininess[1] = {128}; 

public:
   Light();
   Light(const Vec4<float>& position);

   void turnOn();
   void enableSpecularComponent();
   void disableSpecularComponent();
};

} // namespace Caffeina

#endif