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
Vec4<T>::Vec4() : _x(0), _y(0), _z(0), _w(0) {

}

/**
   Default destructor
*/
template <class T>
Vec4<T>::~Vec4() {
   // nothing to do here
}

/**
   Copy constructor
*/
template <class T>
Vec4<T>::Vec4(const Vec4& v) : _x(v.x), _y(v.y), _z(v.z), _w(v.w){

}


/**
   Constructor with 3 parameters
   
   @param x1 x component
   @param y1 y component
   @param z1 z component
   @param w1 w component
*/
template <class T>
Vec4<T>::Vec4(const T& x1, const T& y1, const T& z1, const T& w1) : _x(x1), _y(y1), _z(z1), _w(w1) {

}

/**
   return x component
*/
template <class T>
T Vec4<T>::x() const {
   return _x;
}

/**
   return y component
*/
template <class T>
T Vec4<T>::y() const {
   return _y;
}

/**
   return z component
*/
template <class T>
T Vec4<T>::z() const {
   return _z;
}

/**
   return w component
*/
template <class T>
T Vec4<T>::w() const {
   return _w;
}

/**
   reset vec
*/
template <class T>
void Vec4<T>::zero(){
   _x = _y = _z = _w = 0;
}

/**
   return the lenght of the vector
*/
template <class T>
T Vec4<T>::norm() const {
   return (T)sqrt((_x * _x) + (_y * _y) + (_z * _z) + (_w * _w));
}

/**
   add value to this vector

   @param value value to add
*/
template <class T>
void Vec4<T>::add(const T& x1, const T& y1, const T& z1, const T& w1) {
   _x += x1; 
   _y += y1;
   _z += z1;
   _w += w1;
}

/**
   calculate and return the scalar dot product of two vectors

   @param vec1 first vector
   @param vec2 second vector 
*/
template <class T>
T Vec4<T>::dotProduct(const Vec4& vec1, const Vec4& vec2) {
   return vec1.x() * vec2.x() + 
          vec1.y() * vec2.y() + 
          vec1.z() * vec2.z() + 
          vec1.w() * vec2.w();
}

/**
   return the distance between two vector

   @param vec1 second vector
   @param vec2 second vector 
*/
template <class T>
T Vec4<T>::distance(const Vec4& v1, const Vec4& v2) {
   T dx = v2.x() - v1.x();
   T dy = v2.y() - v1.y();
   T dz = v2.z() - v1.z();
   T dw = v2.w() - v1.w();
 
   return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

/**
   return the lenght of vector
*/
template <class T>
void Vec4<T>::normalize() {
   scale(1.0f / norm());
}

/**
   convert Vec4 to array 
*/
template <class T>
T* Vec4<T>::convert(const Vec4& v) {
   T* vF = new T[4];
   vF[0] = v.x(); 
   vF[1] = v.y(); 
   vF[2] = v.z();
   vF[3] = v.w();
   return vF;
}

/**
   overload assignment operator
*/
template <class T>
Vec4<T>& Vec4<T>::operator=(const Vec4& v) {
   if(this == &v)
      return *this;

   _x = v.x();
   _y = v.y();
   _z = v.z();
   _w = v.w();

   return *this;
}

/**
   overload -= operator
*/
template <class T>
void Vec4<T>::operator-=(const Vec4& v1) {
   _x -= v1.x(); 
   _y -= v1.y();
   _z -= v1.z();
   _w -= v1.w();
}

/**
   overload += operator
*/
template <class T>
void Vec4<T>::operator+=(const Vec4& v1) {
   _x += v1.x(); 
   _y += v1.y();
   _z += v1.z();
   _w += v1.w();
}

/**
   overload minus operator
*/
template <class T>
Vec4<T> Vec4<T>::operator-(const Vec4& vector) const {
   return Vec4<T>(_x - vector.x(), 
                  _y - vector.y(), 
                  _z - vector.z(),
                  _w - vector.w());
}

/**
   overload plus operator
*/
template <class T>
Vec4<T> Vec4<T>::operator+(const Vec4& vector) const {
   return Vec4<T>(_x + vector.x(), 
                  _y + vector.y(), 
                  _z + vector.z(),
                  _w + vector.w());
}

/**
   Overloaded multiplication operator to multiply two Vec4s together
*/
template <class T>        
Vec4<T> Vec4<T>::operator*(const Vec4 &vector) const {
   return Vec4<T>(_x * vector.x(), 
                  _y * vector.y(), 
                  _z * vector.z(),
                  _w * vector.w());
}
 
/** 
   Overloaded multiply operator to multiply a vector by a scalar
*/
template <class T>
Vec4<T> Vec4<T>::operator*(const T &value) const {
   return Vec4<T>(_x * value, 
                  _y * value, 
                  _z * value,
                  _w * value);
}
 
/**   
   Overloaded multiply and assign operator to multiply a vector by a scalar
*/
template <class T>
void Vec4<T>::operator*=(const T &value) {
   _x *= value;
   _y *= value;
   _z *= value;
   _w *= value;
}
 
/**   
   Overloaded multiply operator to multiply a vector by a scalar
*/
template <class T>        
Vec4<T> Vec4<T>::operator/(const T &value) const {
   return Vec4<T>(_x / value, 
                  _y / value, 
                  _z / value,
                  _w / value);
}
 
/** 
   Overloaded multiply and assign operator to multiply a vector by a scalar
*/
template <class T>
void Vec4<T>::operator/=(const T &value) {
   _x /= value;
   _y /= value;
   _z /= value;
   _w /= value;
}

} // namespace Caffeina
