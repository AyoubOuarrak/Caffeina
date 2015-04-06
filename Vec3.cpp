#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#elif defined __linux__ || defined _WIN32 || defined _WIN64
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <cmath>

namespace Caffeina {

/**
   Default constructor
*/
template <class T>
Vec3<T>::Vec3() : _x(0), _y(0), _z(0) {

}

/**
   Default destructor
*/
template <class T>
Vec3<T>::~Vec3() {
   // nothing to do here
}

/**
   Copy constructor
*/
template <class T>
Vec3<T>::Vec3(const Vec3<T>& v) : _x(v.x()), _y(v.y()), _z(v.z()) {

}


/**
   Constructor with 3 parameters
   
   @param x1 x component
   @param y1 y component
   @param z1 z component
*/
template <class T>
Vec3<T>::Vec3(const T& x1, const T& y1, const T& z1) : _x(x1), _y(y1), _z(z1) {
   
}

/**
   return x component
*/
template <class T>
T Vec3<T>::x() const {
   return _x;
}

/**
   return y component
*/
template <class T>
T Vec3<T>::y() const {
   return _y;
}

/**
   return z component
*/
template <class T>
T Vec3<T>::z() const {
   return _z;
}

/**
   set x component

   @param value new x value
*/
template <class T>
void Vec3<T>::setX(const T& value) {
   _x = value;
}

/**
   set y component

   @param value new y value
*/
template <class T>
void Vec3<T>::setY(const T& value) {
   _y = value;
}

/**
   set z component

   @param value new z value
*/
template <class T>
void Vec3<T>::setZ(const T& value) {
   _z = value;
}

/**
   reset vec
*/
template <class T>
void Vec3<T>::zero(){
   _x = _y = _z = 0;
}

/**
   return the lenght of the vector
*/
template <class T>
T Vec3<T>::norm() const {
   return (T)sqrt((_x*_x) + (_y*_y) + (_z*_z));
}

/**
   add value to this vector

   @param value value to add
*/
template <class T>
void Vec3<T>::add(const T& v1, const T& v2, const T& v3) {
   _x += v1; 
   _y += v2;
   _z += v3;
}

/**
   calculate and return the scalar dot product of two vectors

   @param vec1 first vector
   @param vec2 second vector 
*/
template <class T>
T Vec3<T>::dotProduct(const Vec3<T>& vec1, const Vec3<T>& vec2) {
   return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
}

/**
   return the cross product 

   @param vec1 second vector
   @param vec2 second vector 
*/
template <class T>
Vec3<T> Vec3<T>::crossProduct(const Vec3<T>& vec1, const Vec3<T>& vec2) {
   return Vec3<T>(vec1.y() * vec2.z() - vec1.z() * vec2.y(), 
                  vec1.z() * vec2.x() - vec1.x() * vec2.z(), 
                  vec1.x() * vec2.y() - vec1.y() * vec2.x());
}

/**
   return the distance between two vector

   @param vec1 second vector
   @param vec2 second vector 
*/
template <class T>
T Vec3<T>::distance(const Vec3<T>& v1, const Vec3<T>& v2) {
   T dx = v2.x() - v1.x();
   T dy = v2.y() - v1.y();
   T dz = v2.z() - v1.z();
 
   return sqrt(dx * dx + dy * dy + dz * dz);
}

/**
   return the lenght of vector
*/
template <class T>
void Vec3<T>::normalize() {
   scale(1.0f / norm());
}

/**
   convert vec3 to array 
*/
template <class T>
T* Vec3<T>::convert(const Vec3<T>& v) {
   T* vF = new T[3];
   vF[0] = v.x(); 
   vF[1] = v.y(); 
   vF[2] = v.z();
   return vF;
}

/**
   Given three points on a plane in counter clockwise order, calculate the unit normal
   
   @param vP1 first point
   @param vP2 second point
   @param vP3 third point
*/
template <class T>
Vec3<T> Vec3<T>::normalVector(const Vec3<T>& vP1, const Vec3<T>& vP2, const Vec3<T>& vP3) {
   Vec3<T> v1;
   Vec3<T> v2;
   Vec3<T> vNormal;

   v1 = vP2 - vP1;
   v2 = vP3 - vP1;
   vNormal = v1.crossProduct(v2);
   vNormal.normalize();
   return vNormal;
}

/**
   overload assignment operator
*/
template <class T>
Vec3<T>& Vec3<T>::operator=(const Vec3<T>& v) {
   if(this == &v)
      return *this;

   _x = v.x();
   _y = v.y();
   _z = v.z();

   return *this;
}

/**
   overload -= operator
*/
template <class T>
void Vec3<T>::operator-=(const Vec3<T>& v1) {
   _x -= v1.x(); 
   _y -= v1.y();
   _z -= v1.z();
}

/**
   overload += operator
*/
template <class T>
void Vec3<T>::operator+=(const Vec3<T>& v1) {
   _x += v1.x(); 
   _y += v1.y();
   _z += v1.z();
}

/**
   overload minus operator
*/
template <class T>
Vec3<T> Vec3<T>::operator-(const Vec3<T>& vector) const {
   return Vec3<T>(_x - vector.x(), _y - vector.y(), _z - vector.z());
}

/**
   overload plus operator
*/
template <class T>
Vec3<T> Vec3<T>::operator+(const Vec3<T>& vector) const {
   return Vec3<T>(_x + vector.x(), _y + vector.y(), _z + vector.z());
}

/**
   Overloaded multiplication operator to multiply two Vec3s together
*/
template <class T>        
Vec3<T> Vec3<T>::operator*(const Vec3<T> &vector) const {
   return Vec3<T>(_x * vector.x(), _y * vector.y(), _z * vector.z());
}
 
/** 
   Overloaded multiply operator to multiply a vector by a scalar
*/
template <class T>
Vec3<T> Vec3<T>::operator*(const T &value) const {
   return Vec3<T>(_x * value, _y * value, _z * value);
}
 
/**   
   Overloaded multiply and assign operator to multiply a vector by a scalar
*/
template <class T>
void Vec3<T>::operator*=(const T &value) {
   _x *= value;
   _y *= value;
   _z *= value;
}
 
/**   
   Overloaded multiply operator to multiply a vector by a scalar
*/
template <class T>        
Vec3<T> Vec3<T>::operator/(const T &value) const {
   return Vec3<T>(_x / value, _y / value, _z / value);
}
 
/** 
   Overloaded multiply and assign operator to multiply a vector by a scalar
*/
template <class T>
void Vec3<T>::operator/=(const T &value) {
   _x /= value;
   _y /= value;
   _z /= value;
}

} // namespace Caffeina
