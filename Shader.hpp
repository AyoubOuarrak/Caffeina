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

#ifndef _SHADER_HH_GUARD
#define _SHADER_HH_GUARD

#if ((defined(__MACH__)) && (defined(__APPLE__)))   
#include <cstdlib>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#else
#include <cstdlib>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#endif

#include <string>

namespace Caffeina {

class Shader {

private:
   unsigned int shader_id;
   unsigned int shader_fp;
   unsigned int shader_vp;

public:
   Shader();
   Shader(const char* vsFile, const char* fsFile);
   ~Shader();

   void init(const char* vsFile, const char* fsFile);
   void bind();
   void unBind();
   unsigned int id();
};

} // namespace Caffeina

#endif