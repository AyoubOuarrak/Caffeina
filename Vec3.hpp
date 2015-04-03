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

#ifndef VEC3_GUARD_HH
#define VEC3_GUARD_HH

namespace Caffeina {

template <class T>
class Vec3 {
private:
   T _x;
   T _y;
   T _z;

public:
   // default constructor
   Vec3();
   // copy constructor
   Vec3(const Vec3<T>&);
   // constructor of three parameters
   Vec3(const T& x, const T& y, const T& z);
   // destructor
   ~Vec3();

   // getter
   T x() const;
   T y() const;
   T z() const;

   // setter
   void setX(const T&);
   void setY(const T&);
   void setZ(const T&);

   T norm() const;

   // add a value to all component of this
   void  add(const T&, const T&, const T&);
   // set all component of this to 0
   void  zero();
   // normalize the vector, after this operation all component are in the range [-1, 1]
   void  normalize();
   // given three point, calculate the normal vector and return
   Vec3  normalVector(const Vec3<T>&, const Vec3<T>&, const Vec3<T>&);

   // static method to convert vec3 to the T
   static T*   convert(const Vec3<T>&);
   // static method to calculate the dot product between two vector (return a scalar value)
   static T    dotProduct(const Vec3<T>&, const Vec3<T>&);
   // static method to calculate the cross product between two vector (return a vector) 
   static Vec3<T> crossProduct(const Vec3<T>&, const Vec3<T>&);
   // static method to return the distance between two vectors in 3D space
   static T    distance(const Vec3<T>&, const Vec3<T>&);  
   
   // overload operators
   Vec3<T>& operator=(const Vec3<T>&);
   Vec3<T>  operator+(const Vec3<T>&) const;
   Vec3<T>  operator-(const Vec3<T>&) const;
   Vec3<T>  operator*(const Vec3<T>&) const;
   Vec3<T>  operator*(const T&) const;
   Vec3<T>  operator/(const T&) const;

   void  operator*=(const T&);
   void  operator-=(const Vec3<T>&);
   void  operator+=(const Vec3<T>&);
   void  operator/=(const T&);
};

} // namespace Caffeina

#include "Vec3.cpp"
#endif