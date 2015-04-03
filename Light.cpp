#include "Light.hpp"

namespace Caffeina {

Light::Light() {
   lightPosition = Vec4<float>(0.0f, 0.1f, 0.1f, 0.0f);
   specularComponent = Vec3<float>(1.0, 1.0, 1.0);
   ambientComponent = Vec3<float>(0.0, 0.0, 0.0);
   diffuseComponent = Vec3<float>(1.0, 1.0, 1.0);

   diffuseMaterial = Vec3<float>(1.0, 0.0, 0.0);
   specularMaterial = Vec3<float>(1.0, 1.0, 1.0);
   emissiveMaterial = Vec3<float>(0.0, 1.0, 0.0);
   blankMaterial = Vec3<float>(0.0, 0.0, 0.0);
}

Light::Light(const Vec4<float>& position) {
   lightPosition = position;

   specularComponent = Vec3<float>(1.0, 1.0, 1.0);
   ambientComponent = Vec3<float>(0.0, 0.0, 0.0);
   diffuseComponent = Vec3<float>(1.0, 1.0, 1.0);

   diffuseMaterial = Vec3<float>(1.0, 0.0, 0.0);
   specularMaterial = Vec3<float>(1.0, 1.0, 1.0);
   emissiveMaterial = Vec3<float>(0.0, 1.0, 0.0);
   blankMaterial = Vec3<float>(0.0, 0.0, 0.0);
}

void Light::turnOn() {
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_COLOR_MATERIAL);

   glLightfv(GL_LIGHT0, GL_SPECULAR, Vec3<float>::convert(specularComponent));
   glLightfv(GL_LIGHT1, GL_AMBIENT, Vec3<float>::convert(ambientComponent));
   glLightfv(GL_LIGHT0, GL_DIFFUSE, Vec3<float>::convert(diffuseComponent));
   glLightfv(GL_LIGHT0, GL_POSITION, Vec4<float>::convert(lightPosition));
}

void Light::enableSpecularComponent() {
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Vec3<float>::convert(specularMaterial));
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
}

void Light::disableSpecularComponent() {
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Vec3<float>::convert(blankMaterial));
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Vec3<float>::convert(blankMaterial));
}

} // namespace Caffeina