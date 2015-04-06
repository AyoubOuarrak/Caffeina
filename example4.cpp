#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#elif defined __linux__ || defined _WIN32 || defined _WIN64
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <algorithm>
#include <iostream>
#include <cmath>

#include "Shader.hpp"
#include "World.hpp"

// camera
Caffeina::World world;
// shader
Caffeina::Shader shader;


void initScene() {
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glEnable(GL_SMOOTH);
   glShadeModel(GL_SMOOTH);
   shader.init("shader.vert", "shader.frag");
   Caffeina::World::generateGrid();
}

void draw() {

}

void renderScene() {
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();
   // turn on lights
   world.light().turnOn();
   // enable camera movement
   world.camera().enable();

   shader.bind();
   // draw ground
   Caffeina::World::grid();

   // draw primitives
   draw();
   shader.unBind();
   
   glutSwapBuffers();
}


void reshape(int width, int height) {
   // Set our viewport to the size of our window  
   glViewport(0, 0, (GLsizei)width, (GLsizei)height); 
   // Switch to the projection matrix so that we can manipulate how our scene
   glMatrixMode(GL_PROJECTION); 
   // Reset the projection matrix to the identity matrix
   glLoadIdentity(); 
   // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
   gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); 
   // Switch back to the model view matrix, so that we can start drawing shapes correctly  
   glMatrixMode(GL_MODELVIEW); 
}

void mouseMovement(int x, int y) {
   world.camera().handleMouse(x, y);
}

void keyHandler(unsigned char key, int x, int y) {
   switch(key) {
      case 'A':
      case 'a':
         world.camera().moveLeft();
         break;

      case 'D':
      case 'd':
         world.camera().moveRight();
         break;

      case 's':
      case 'S':
         world.camera().moveBackward();
         break;

      case 'W':
      case 'w':
         world.camera().moveForward();
         break;

      case '+':
         world.camera().zoomIn();
         break;

      case '-':
         world.camera().zoomOut();
         break;
   }

}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(650, 500);
   glutInitWindowPosition(400, 400);
   glutCreateWindow("OpenGL");
   std::cout << "Controls: Use WSAD and the mouse to move around, + and - to zoom!" << std::endl;
   initScene();
   glutDisplayFunc(renderScene);
   glutIdleFunc(renderScene);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyHandler);
   glutMotionFunc(mouseMovement);
   //glutSpecialFunc(specialKeyHandler);
   glutMainLoop();
   return 0;
}