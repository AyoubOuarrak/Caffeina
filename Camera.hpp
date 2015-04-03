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

#ifndef CAMERA_GUARD_HH
#define CAMERA_GUARD_HH

#include "Vec3.hpp"

namespace Caffeina {

class Camera {

private:
   float distance; 
   float movementSpeed;
   Vec3<double>  position;
   Vec3<double>  rotation;

   static Vec3<double> lastPosition;

public:
   Camera();
   Camera(float distance);
   Camera(float distance, const Vec3<double>& pos);

   void handleMouse(int x, int y);
   void setMovementSpeed(float speed);
   void moveForward();
   void moveBackward();
   void moveLeft();
   void moveRight();
   void zoomIn();
   void zoomOut();
   void enable();

private:
   double toRad(const double& angle);
};

} // namespace Caffeina

#endif