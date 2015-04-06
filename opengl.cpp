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
/*
   OPENGL TYPE OF SHAPES

   - GL_LINES
   - GL_LINES_STRIP
   - GL_LINE_LOOP
   - GL_POINTS
   - GL_POLYGON
   - GL_QUADS
   - GL_QUADS_STRIP
   - GL_TRIANGLES
   - GL_TRIANGLE_FAN
   - GL_TRIANGLE_STRIP
*/

// tranformation parametrs
float yRotationAngle = 0.0f;
float xRotationAngle = 0.0f;
float zRotationAngle = 0.0f;
float torusRot = 0.0f;

// shader object
Caffeina::Shader shader;
// light object
Caffeina::Light light;
// cube display list
GLuint cubeList;
// torus display list
GLuint torusList;

// camera parameters
float cRadius = 10.0f; // our radius distance from our character
float xCam = 0; 
float yCam = 0; 
float zCam = 0; 
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

void camera() {
   // rotate our camera on the x-axis (left and right)
   glRotatef(xCamRot, 1.0, 0.0, 0.0);  
   // rotate our camera on the y-axis (up and down)
   glRotatef(yCamRot, 0.0, 1.0, 0.0);  
   // translate the screento the position of our camera
   glTranslated(-xCam, -yCam, -zCam); 
}

void generateCube() {
   // set the cube list to generate a list
   cubeList = glGenLists(1);
   // compile the new list 
   glNewList(cubeList, GL_COMPILE);
   // draw cube
   glPushMatrix();
   glColor3f(0.0, 0.0, 0.9); 
   glutSolidCube(4);
   glPopMatrix();
   // end the list
   glEndList();
}

void generateTorus() {
   // set the torus list to generate a list
   torusList = glGenLists(1);
   // compile the new list
   glNewList(torusList, GL_COMPILE);
   //draw torus
   glColor3f(0.0, 0.6, 0.3);
   glutSolidTorus(0.3f, 0.7f, 40, 40);
   // end the list
   glEndList();
}

void initScene() {
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glEnable(GL_SMOOTH);
   glShadeModel(GL_SMOOTH);
   shader.init("shader.vert", "shader.frag");

   generateCube();
   generateTorus();
}

void render() {
   // call the cube list
   glCallList(cubeList);

   glTranslatef(3.0f, 0.0f, 0.0f); 
   glPushMatrix();
   glRotatef(torusRot, -1.0f, 1.0f, 1.0f);
   glCallList(torusList);
   glPopMatrix();

   glTranslatef(-3.0f, 3.0f, 0.0f); 
   glPushMatrix();
   glRotatef(torusRot, 1.0f, -1.0f, 1.0f);
   glCallList(torusList);
   glPopMatrix();

   glTranslatef(-3.0f, -3.0f, 0.0f); 
   glPushMatrix();
   glRotatef(torusRot, 1.0f, 1.0f, -1.0f);
   glCallList(torusList);
   glPopMatrix();

   glTranslatef(3.0f, -3.0f, 0.0f); 
   glPushMatrix();
   glRotatef(torusRot, 1.0f, -1.0f, 1.0f);
   glCallList(torusList);
   glPopMatrix();
   
   glTranslatef(0.0f, 3.0f, 3.0f); 
   glPushMatrix();
   glRotatef(torusRot, 1.0f, -1.0f, -1.0f);
   glCallList(torusList);
   glPopMatrix();

   glTranslatef(0.0f, 0.0f, -6.0f); 
   glPushMatrix();
   glRotatef(torusRot, 1.0f, 1.0f, 1.0f);
   glCallList(torusList);
   glPopMatrix();
}

void display() {
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();
   light.turnOn();
   
   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -cRadius);
   glRotatef(xCamRot,1.0,0.0,0.0);
   glColor3f(1.0f, 0.0f, 0.0f);
   glutSolidCube(1); //Our character to follow
   glRotatef(yCamRot, 0.0, 1.0, 0.0);  
   glTranslated(-xCam, 0.0f, -zCam); //translate the screen
   
   shader.bind();
   // draw primitives
   render();
   DrawGround();
   shader.unBind();
   
   glutSwapBuffers();

   // torus animation
   //xRotationAngle += 3.0f;
   if (xRotationAngle > 360.0f)
      xRotationAngle -= 360.0f;

   //yRotationAngle += 3.0f;
   if (yRotationAngle < 0.0f)
      yRotationAngle += 360.0f;

   torusRot += 10.0f;
   if (torusRot > 360.0f)
      torusRot -= 360.0f;

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

void keyHandler(unsigned char key, int x, int y) {
   switch(key) {
      case 's':
         float xrotrad, yrotrad;
         yrotrad = (yCamRot / 180 * 3.141592654f);
         xrotrad = (xCamRot / 180 * 3.141592654f); 
         xCam += float(sin(yrotrad));
         zCam -= float(cos(yrotrad));
         yCam -= float(sin(xrotrad));
         break;

      case 'w':
          float xrotrad1, yrotrad1;
         yrotrad1 = (yCamRot / 180 * 3.141592654f);
         xrotrad1 = (xCamRot / 180 * 3.141592654f); 
         xCam -= float(sin(yrotrad1));
         zCam += float(cos(yrotrad1)) ;
         yCam += float(sin(xrotrad1));
         break;

      case 'e':
         light.enableSpecularComponent();
         break;

      case 'E':
         light.disableSpecularComponent();
         break;

      case 'a':
         float yrotrad3;
         yrotrad3 = (yCamRot / 180 * 3.141592654f);
         xCam -= float(cos(yrotrad3)) * 0.5;
         zCam -= float(sin(yrotrad3)) * 0.5;
         break;

      case 'd':
         float yrotrad2;
         yrotrad2 = (yCamRot / 180 * 3.141592654f);
         xCam += float(cos(yrotrad2)) * 0.5;
         zCam += float(sin(yrotrad2)) * 0.5;
         break;
   }
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
   xCamRot += (float) diffy; 
   //set the xrot to yrot with the addition of the difference in the x position
   yCamRot -= (float) diffx;    
}

void specialKeyHandler(int key, int x, int y) {
   switch(key) {
      case GLUT_KEY_LEFT:
         yCamRot += 5;
         if (yCamRot > 360) 
            yCamRot -= 360;
         break;

      case GLUT_KEY_RIGHT:
         yCamRot -= 5;
         if (yCamRot < -360)
            yCamRot += 360;
         break;

      case GLUT_KEY_UP:
         xCamRot += 5;
         if (xCamRot > 360) 
            xCamRot -= 360;
         break;

      case GLUT_KEY_DOWN:
         xCamRot -= 5;
         if (xCamRot < -360) 
            xCamRot += 360;
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
   glutDisplayFunc(display);
   glutIdleFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyHandler);
   glutPassiveMotionFunc(mouseMovement);
   glutSpecialFunc(specialKeyHandler);
   glutMainLoop();
   return 0;
}