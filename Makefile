main: example3.o Shader.o Light.o Camera.o
	  g++  -std=c++11 -g -Wall -Wextra example3.o Shader.o Light.o Camera.o -o main -framework GLUT -framework OpenGL -framework Cocoa

example3.o:
	g++ -c example3.cpp -o example3.o     

Shader.o:
	g++ -c Shader.cpp -o Shader.o

Light.o:
	g++ -c Light.cpp -o Light.o  

Camera.o:
	g++ -c Camera.cpp -o Camera.o

clean:
	-rm -f *.o main                                                             
