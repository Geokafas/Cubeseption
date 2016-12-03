all:
	g++ -o Cubeseption.out -std=c++11 -Wall main.cpp camera.cpp -lGLU -lGL -lglut -lm 

clean:
	rm *.o
