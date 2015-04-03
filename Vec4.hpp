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

#ifndef VEC4_GUARD_HH
#define VEC4_GUARD_HH

namespace Caffeina {

template <class T>
class Vec4 {
private:
   T _x;
   T _y;
   T _z;
   T _w;

public:
   // default constructor
   Vec4();
   // copy constructor
   Vec4(const Vec4&);
   // constructor of three parameters
   Vec4(const T& x, const T& y, const T& z, const T& w);
   // destructor
   ~Vec4();

   T x() const;
   T y() const;
   T z() const;
   T w() const;
   T norm() const;

   // add a value to all component of this
   void  add(const T&, const T&, const T&, const T&);
   // set all component of this to 0
   void  zero();
   // normalize the vector, after this operation all component are in the range [-1, 1]
   void  normalize();

   // static method to convert Vec4 to the T
   static T*   convert(const Vec4&);
   // static method to calculate the dot product between two vector (return a scalar value)
   static T    dotProduct(const Vec4&, const Vec4&);
   // static method to return the distance between two vectors in 3D space
   static T    distance(const Vec4&, const Vec4&);  
   
   // overload operators
   Vec4& operator=(const Vec4&);
   Vec4  operator+(const Vec4&) const;
   Vec4  operator-(const Vec4&) const;
   Vec4  operator*(const Vec4&) const;
   Vec4  operator*(const T&) const;
   Vec4  operator/(const T&) const;

   void  operator*=(const T&);
   void  operator-=(const Vec4&);
   void  operator+=(const Vec4&);
   void  operator/=(const T&);
};

} // namespace Caffeina

#include "Vec4.cpp"
#endif