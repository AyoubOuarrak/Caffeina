main: example4.o Shader.o Light.o Camera.o World.o
	  g++  -std=c++11 -g -Wall -Wextra example4.o World.o Shader.o Light.o Camera.o -o main -framework GLUT -framework OpenGL -framework Cocoa

example4.o:
	g++ -c example4.cpp -o example4.o     

World.o:
	g++ -c World.cpp -o World.o
    
Shader.o:
	g++ -c Shader.cpp -o Shader.o

Light.o:
	g++ -c Light.cpp -o Light.o  

Camera.o:
	g++ -c Camera.cpp -o Camera.o

clean:
	-rm -f *.o main                                                             
