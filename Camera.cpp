#include "Camera.hpp"
#include <cmath>

namespace Caffeina {

Vec3<double> Caffeina::Camera::lastPosition;

Camera::Camera() : distance(5.0f), movementSpeed(0.5f) {
   position.zero();
   rotation.zero();
}

Camera::Camera(float d) : distance(d) {
   position.zero();
   rotation.zero();
}

Camera::Camera(float d, const Vec3<double>& pos) : distance(d), movementSpeed(0.5f) {
   position = pos;
   rotation.zero();
}

void Camera::handleMouse(int x, int y) {
   Vec3<double> diff(y - lastPosition.y(), x - lastPosition.x(), 0);

   Camera::lastPosition.setX(x); 
   Camera::lastPosition.setY(y); 
   rotation -= diff;

   // Limit loking up to vertically up
   if (rotation.x() < 0) {
      rotation.setX(0);
   }
   // Limit looking down to vertically down
   if (rotation.x() > 90) {
      rotation.setX(90);
   }
}

double Camera::toRad(const double& angle) {
   return angle * (3.141592654 / 180.0);
}

void Camera::enable() {
   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -distance);
   glRotatef(rotation.x(), 1.0, 0.0, 0.0);
   glRotatef(rotation.y(), 0.0, 1.0, 0.0);  
   glTranslated(-position.x(), 0.0f, -position.z()); 
}

void Camera::setMovementSpeed(float sp) {
   movementSpeed = sp;
}

void Camera::moveForward() {
   float x = sin(toRad(rotation.y())) * movementSpeed;
   float y = sin(toRad(rotation.x())) * movementSpeed;
   float z = cos(toRad(rotation.y())) * movementSpeed;

   position.add(x, -y, -z);
}
   
void Camera::moveBackward() {
   float x = sin(toRad(rotation.y())) * movementSpeed;
   float y = sin(toRad(rotation.x())) * movementSpeed;
   float z = cos(toRad(rotation.y())) * movementSpeed;

   position.add(-x, y, z);
}
   
void Camera::moveLeft() {
   float x = cos(toRad(rotation.y())) * movementSpeed;
   float z = sin(toRad(rotation.y())) * movementSpeed;

   position.add(-x, 0, -z);
}
   
void Camera::moveRight() {
   float x = cos(toRad(rotation.y())) * movementSpeed;
   float z = sin(toRad(rotation.y())) * movementSpeed;

   position.add(x, 0, z);
}
   
void Camera::zoomIn() {
   distance -= 0.5f;
}
   
void Camera::zoomOut() {
   distance += 0.5f;
}
} // namespace Caffeina




