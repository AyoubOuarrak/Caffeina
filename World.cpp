#include "World.hpp"

namespace Caffeina {

GLuint World::_gridList;

World::World() {
   _light = Light();
   _camera = Camera();
}

World::World(Light l, Camera c) {
   _light = l;
   _camera = c;
}

void World::generateGrid(float gridSize, float gridStep) {
   // set the grid list to generate a list
   _gridList = glGenLists(1);
   // compile the new list
   glNewList(_gridList, GL_COMPILE);

   // How far on the Z-Axis and X-Axis the ground extends
   GLfloat fExtent = gridSize;
   // The size of the separation between points
   GLfloat fStep = gridStep;
   GLfloat y = -0.4f;
   GLint iLine;
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINES);
   
   for(iLine = -fExtent; iLine <= fExtent; iLine += fStep) {
      glVertex3f(iLine, y, fExtent);    // Draw Z lines
      glVertex3f(iLine, y, -fExtent);
      glVertex3f(fExtent, y, iLine);
      glVertex3f(-fExtent, y, iLine);
   }
   glEnd();
   glEndList();
}

void World::grid() {
   glCallList(_gridList);
}

Camera& World::camera() {
   return _camera;
}

Light& World::light() {
   return _light;
}
} // namespace Caffeina