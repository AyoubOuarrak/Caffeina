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
#include "Camera.hpp"
#include "Light.hpp"

// camera
Caffeina::Camera camera;
// shader object
Caffeina::Shader shader;
// light object
Caffeina::Light light;


void DrawGround(){
   GLfloat fExtent = 10.0f;
   GLfloat fStep = 1.0f;
   GLfloat y = -0.4f;
   GLint iLine;
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_LINES);
   
   for(iLine = -fExtent; iLine <= fExtent; iLine += fStep) {
      glVertex3f(iLine, y, fExtent);    // Draw Z lines
      glVertex3f(iLine, y, -fExtent);
      glVertex3f(fExtent, y, iLine);
      glVertex3f(-fExtent, y, iLine);
   }
   glEnd();
}

void initScene() {
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glEnable(GL_SMOOTH);
   glShadeModel(GL_SMOOTH);
   shader.init("shader.vert", "shader.frag");
}

void draw() {

}

void renderScene() {
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();
   // turn on lights
   light.turnOn();
   // enable camera movement
   camera.enable();

   shader.bind();
   // draw ground
   DrawGround();
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
   camera.handleMouse(x, y);
}

void keyHandler(unsigned char key, int x, int y) {
   switch(key) {
      case 'A':
      case 'a':
         camera.moveLeft();
         break;

      case 'D':
      case 'd':
         camera.moveRight();
         break;

      case 's':
      case 'S':
         camera.moveBackward();
         break;

      case 'W':
      case 'w':
         camera.moveForward();
         break;

      case '+':
         camera.zoomIn();
         break;

      case '-':
         camera.zoomOut();
         break;
   }

}


int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(650, 500);
   glutInitWindowPosition(400, 400);
   glutCreateWindow("OpenGL");
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