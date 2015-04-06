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

#ifndef WINDOW_GUARD_HH
#define WINDOW_GUARD_HH
#include <string>

namespace Caffeina {

class Window {

private:
   std::string title;
   int width;
   int height;
   int xPosition;
   int yPosition;
   
public:
   Window();
   explicit Window(std::string title);
   Window(std::string title, int with, int height);
   Window(std::string title, int width, int height, int positionX, int positionY);
};

} // namespace Caffeina

#endif