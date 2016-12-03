#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include <math.h>
#include <time.h>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define SPACEBAR 32

CCamera Camera;
using namespace std;

enum Color { R, G, B, Y, M, E };
int debug = 0;

//starting values
int points = 50;
int lives = 3;
int remcubes = 0;
int dimension = 0;


//initCubeLayout
char ***cubeLayout;
char rgb[] = { 'R','G','B','Y' };
char colorPicker();

//player position
int playerPosx;
int playerPosy;
int playerPosz;

//Player View Dir
GLfloat viewDirx;
GLfloat viewDiry;
GLfloat viewDirz;
SF3dVector CalcNextBoxPos();

//lights
void initLights();
int lights = 1; //light switch

int gameOver = 1;

void drawText(int x, int y, char *string); 
void drawBox(int x, int y, int z, char color); 
void addBox();
void DrawNet();

void initCubeLayout();
void initLights();
void init(void);

void Display(void);
void viewAngle();

void KeyDown(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void moveInY();
void reset();

void calculateE();
void calculateQ();
void calculateR();
void kickBox();
int outOfBoundsForward();
int outOfBoundsBackward();
void GameOver();
void Debug();