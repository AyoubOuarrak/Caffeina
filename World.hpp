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

#ifndef WORLD_GUARD_HH
#define WORLD_GUARD_HH

#include "Camera.hpp"
#include "Light.hpp"


namespace Caffeina {

class World {

private:
   static GLuint _gridList;
   Light _light;
   Camera _camera;

public:
   World();
   World(Light l, Camera c);

   Camera& camera();
   Light&  light();

   static void grid();
   static void generateGrid(float size = 30.0f, float step = 1.0f);

};

} // namespace Caffeina
#endif