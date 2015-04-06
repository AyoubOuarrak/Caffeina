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
#include "Shader.hpp"
#include "Light.hpp"
#include <cmath>

// shader object
Caffeina::Shader shader;
// light object
Caffeina::Light light;

// camera parameters
float cRadius = 5.0f; // our radius distance from our character
float xCam = 5; 
float yCam = 5; 
float zCam = 5; 
float xCamRot = 0; 
float yCamRot = 0; 
float camAngle = 0.0;
float lastx, lasty;

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

/*void camera() {
   // rotate our camera on the x-axis (left and right)
   glRotatef(xCamRot, 1.0, 0.0, 0.0);  
   // rotate our camera on the y-axis (up and down)
   glRotatef(yCamRot, 0.0, 1.0, 0.0);  
   // translate the screento the position of our camera
   glTranslated(-xCam, -yCam, -zCam); 
}
*/
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


   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -cRadius);
   glRotatef(xCamRot,1.0,0.0,0.0);
   glRotatef(yCamRot, 0.0, 1.0, 0.0);  
   glTranslated(-xCam, 0.0f, -zCam); //translate the screen

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
   //check the difference between the current x and the last x position
   int diffx = x-lastx; 
   //check the difference between the current y and the last y position
   int diffy = y-lasty; 
   //set lastx to the current x position
   lastx = x; 
   //set lasty to the current y position
   lasty = y; 
   //set the xrot to xrot with the addition of the difference in the y position
   xCamRot -= (float) diffy; 
   //set the xrot to yrot with the addition of the difference in the x position
   yCamRot -= (float) diffx;    

      // Limit loking up to vertically up
   if(xCamRot < 0) {
      xCamRot = 0;
   }
 
   // Limit looking down to vertically down
   if (xCamRot > 90) {
      xCamRot =  90;
   }
}

void keyHandler(unsigned char key, int x, int y) {
   switch(key) {
      case 'A':
      case 'a':
         float yrotrad3;
         yrotrad3 = (yCamRot / 180 * 3.141592654f);
         xCam -= float(cos(yrotrad3)) * 0.5;
         zCam -= float(sin(yrotrad3)) * 0.5;
         break;

      case 'D':
      case 'd':
         float yrotrad2;
         yrotrad2 = (yCamRot / 180 * 3.141592654f);
         xCam += float(cos(yrotrad2)) * 0.5;
         zCam += float(sin(yrotrad2)) * 0.5;
         break;

      case 's':
      case 'S':
         float xrotrad1, yrotrad1;
         yrotrad1 = (yCamRot / 180 * 3.141592654f);
         xrotrad1 = (xCamRot / 180 * 3.141592654f); 
         xCam -= float(sin(yrotrad1)) * 0.5;
         zCam += float(cos(yrotrad1)) * 0.5;
         yCam += float(sin(xrotrad1)) * 0.5;
         break;

      case 'W':
      case 'w':
         float xrotrad, yrotrad;
         yrotrad = (yCamRot / 180 * 3.141592654f);
         xrotrad = (xCamRot / 180 * 3.141592654f); 
         xCam += float(sin(yrotrad)) * 0.5;
         zCam -= float(cos(yrotrad)) * 0.5;
         yCam -= float(sin(xrotrad)) * 0.5;
         break;

      case '+':
         cRadius -= 0.5f;
         break;

      case '-':
          cRadius += 0.5f;
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