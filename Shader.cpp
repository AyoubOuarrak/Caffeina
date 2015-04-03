#include "Shader.hpp"
#include <string.h>
#include <iostream>

namespace Caffeina {

static void validateShader(GLuint shader, const char* file = 0) {
   // size of the output buffer
   const unsigned int BUFFER_SIZE = 512;

   // output from our validation
   char buffer[BUFFER_SIZE];
   memset(buffer, 0, BUFFER_SIZE);

   // length of the buffer we get back from OpenGL.
   GLsizei length = 0;

   // read the shader log from opengl and store it in our buffer.
   glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

   // we have something to output.
   if (length > 0) {
      std::cerr << "Shader " << shader << "(" << (file?file:"") << ") Compile error: " << buffer << std::endl;
   }
}

static void validateProgram(GLuint program) {
   // size of the output buffer
   const unsigned int BUFFER_SIZE = 512;

   // output from our validation
   char buffer[BUFFER_SIZE];
   memset(buffer, 0, BUFFER_SIZE);

   // length of the buffer we get back from OpenGL.
   GLsizei length = 0;

   // read the shader log from opengl and store it in our buffer.
   glGetShaderInfoLog(program, BUFFER_SIZE, &length, buffer);

   if (length > 0) {
      std::cerr << "Program " << program << " Link error: " << buffer << std::endl;
   }

   // validate the program, and then use an integer to read back the status of the shader.
   glValidateProgram(program);
   GLint status;
   glGetProgramiv(program, GL_VALIDATE_STATUS, &status);

   if (status == GL_FALSE) {
      std::cerr << "Error validating shader: " << program << std::endl;
   }
}

static char* fileRead(const char* fileName) {
   char* text;

   if (fileName != NULL) {
      FILE* file = fopen(fileName, "rt");

      if (file != NULL) {
         fseek(file, 0, SEEK_END);
         int count = ftell(file);
         rewind(file);

         if (count > 0) {
            text = (char*) malloc( sizeof(char) * (count + 1));
            count = fread(text, sizeof(char), count, file);
            text[count] = '\0';
         }
         fclose(file);
      }
   }
   return text;
}


Shader::Shader() {
}

Shader::Shader(const char* vsFile, const char* fsFile) {
   init(vsFile, fsFile);
}

Shader::~Shader() {
   // detach our vertex shader and fragment shader from our shader project
   glDetachShader(shader_id, shader_fp);
   glDetachShader(shader_id, shader_vp);

   // delete all of the shaders and then deletes the shader program
   glDeleteShader(shader_fp);
   glDeleteShader(shader_vp);
   glDeleteProgram(shader_id);
}

void Shader::init(const char* vsFile, const char* fsFile) {
   // tell OpenGL to create a vertex shader and a fragment shader, and assign the id’s of these to our shader_vp 
   // and shader_fp variables.
   shader_vp = glCreateShader(GL_VERTEX_SHADER);
   shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

   // read the files that contains our shaders code
   const char* vsText = fileRead(vsFile);
   const char* fsText = fileRead(fsFile);

   // some checks
   if (vsText == NULL || fsText == NULL) {
      std::cerr << "Either vertex shader or fragment shader file not found." << std::endl;
      return;
   }

   // pass our shader file contents to OpenGL to attach it to our shaders. 
   glShaderSource(shader_vp, 1, &vsText, 0);
   glShaderSource(shader_fp, 1, &fsText, 0);

   // tells OpenGL to compile our shaders, which we have already bound the source code to. 
   glCompileShader(shader_vp);
   validateShader(shader_vp, vsFile);
   glCompileShader(shader_fp);
   validateShader(shader_fp, fsFile);

   // create our shader_id as a shader program. And then attach the vertex shader and the fragment shader to the 
   // shader program, and finally, link the program.
   shader_id = glCreateProgram();
   glAttachShader(shader_id, shader_fp);
   glAttachShader(shader_id, shader_vp);
   glLinkProgram(shader_id);
   validateProgram(shader_id);
}

unsigned int Shader::id() {
   return shader_id;
}

void Shader::bind() {
   glUseProgram(shader_id);
}

void Shader::unBind() {
   glUseProgram(0);
}

} // namespace Caffeina