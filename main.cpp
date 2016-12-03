#include "main.h"


void initCubeLayout(void) // intialazes the map-matrix
{
	int i, j, k;

	cubeLayout = new char**[dimension];
	for (i = 0; i < dimension; i++) {
		cubeLayout[i] = new char*[dimension];
		for (j = 0; j < dimension; j++) {
			cubeLayout[i][j] = new char[dimension];

		}
	}

	for (int i = 0; i < 1; i++) { /*Prints the cubeLayout matrix*/
		for (int j = 0; j < dimension; j++) {
			for (int k = 0; k < dimension; k++) {
				cubeLayout[i][j][k] = colorPicker();
				if (debug == 1) {
					cout << cubeLayout[i][j][k] << ",";
				}
			}
		}
		cout << "\n";
	}

	for (i = 1; i < dimension; i++) { // make levels from 1 to dimension empty
		for (j = 0; j < dimension; j++) {
			for (k = 0; k < dimension; k++) {
				cubeLayout[i][j][k] = 'E';
			}
		}
	}
}

char colorPicker(void) {//Picks a randoms color for the cubes
	return rgb[rand() % 4];
}

int outOfBoundsForward(void) { // checks if player is out of bounds
	SF3dVector bound;
	bound = CalcNextBoxPos();
	if (((bound.x > (dimension)) || bound.x < 0))
	{
		return 1;
	}
	else if (((bound.z) > dimension) || bound.z < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int outOfBoundsBackward(void) { // checks if player is out of bounds

	SF3dVector bound;
	bound.x = -viewDirx*(1.0);
	bound.y = viewDiry;
	bound.z = -viewDirz*(1.0);
	AddF3dVectorToVector(&bound, &Camera.Position); // calculates the oposite view Direction
	if (((bound.x > (dimension)) || bound.x < 0))
	{
		return 1;
	}
	else if (((bound.z) > dimension) || bound.z < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void DrawNet(void) //Draws the floor with the cubes
{
	glNormal3f(0.0, 1.0, 0.0);
	for (int i = 0; i < dimension; ++i) {
		for (int r = 0, width = 0; r < dimension; ++r, width += 1) {
			for (int c = 0, depth = 0; c < dimension; ++c, depth += 1) {
				if (width == (dimension / 2) && depth == (dimension / 2) && i == 0) {
					drawBox(width, i, depth, M);
				}
				else {
					if (cubeLayout[i][r][c] == 'R') {
						drawBox(width, i, depth, R);
					}
					else if (cubeLayout[i][r][c] == 'B') {
						drawBox(width, i, depth, B);
					}
					else if (cubeLayout[i][r][c] == 'G') {
						drawBox(width, i, depth, G);
					}
					else if (cubeLayout[i][r][c] == 'Y') {
						drawBox(width, i, depth, Y);
					}
					else {

					}
				}
			}
		}
	}
}


void reshape(int x, int y) { //camera function

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}


void Display(void) //renders the screen content
{
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearColor(0.196078f, 0.6f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera.Render();
	glTranslatef(0.0f, 0.8f, 0.0f);
	glColor3f(0.0, 0.0, 0.0);

	glutMouseFunc(mouseButton);

	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);

	DrawNet();

	glPopMatrix();
	glFlush();

	//*******SCREEN_TEXT********//

	char text[20] = "POINTS: ";
	char StringPoints[100];

	sprintf(StringPoints, "%d", points);
	strcat(text, StringPoints);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawText(350, 750, text);

	char text1[20] = "LIVES: ";
	char StringPoints1[100];

	sprintf(StringPoints1, "%d", lives);
	strcat(text1, StringPoints1);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawText(0, 750, text1);

	char text2[20] = "CUBES: ";
	char StringPoints2[100];

	sprintf(StringPoints2, "%d", remcubes);
	strcat(text2, StringPoints2);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawText(700, 750, text2);

	//*****LIGHTS******//
	if (lights == 1) {
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glShadeModel(GL_SMOOTH);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glClearColor(0.0, 0.0, 0.0, 1.0);
	}
	else if (lights == 0) {
		glDisable(GL_LIGHTING);
	}

	glutSwapBuffers();

}

void KeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: //ESC
		exit(1);
		break;
	case 'a':
		Camera.RotateY(5.0);
		viewAngle();
		CalcNextBoxPos();
		Display();
		break;
	case 'd':
		Camera.RotateY(-5.0);
		viewAngle();
		CalcNextBoxPos();
		Display();
		break;
	case 'w':
		if (outOfBoundsForward() == 0) {
			Camera.MoveForwards(-0.5);
		}
		playerPosx = (int)((Camera.GetPlayerPos().x));
		playerPosy = (int)((Camera.GetPlayerPos().y));
		playerPosz = (int)((Camera.GetPlayerPos().z) - 1);
		moveInY();
		if (debug == 1)
		{
			cout << "Playerposy: " << " " << playerPosy << " " << "Playerposx: " << " " << playerPosx << " " << "Playerposz: " << playerPosz << "\n";
		}
		Display();
		break;
	case 's':
		if (outOfBoundsBackward() == 0)
		{
			Camera.MoveForwards(0.5);
		}
		playerPosx = ((Camera.GetPlayerPos().x));
		playerPosy = ((Camera.GetPlayerPos().y));
		playerPosz = ((Camera.GetPlayerPos().z) - 1);
		moveInY();
		if (debug == 1)
		{
			cout << "Playerposy: " << " " << playerPosy << " " << "Playerposx: " << " " << playerPosx << " " << "Playerposz: " << playerPosz << "\n";

		}
		Display();
		break;
	case 'l':  //light switch

		if (debug == 1)
		{
			if (lights == 1) {
				lights = 0;
				Display();
				cout << "LIGHTS: OFF" << "\n";
			}
			else {
				lights = 1;
				Display();
				cout << "LIGHTS: ON" << "\n";
			}
		}

		break;
	case SPACEBAR:
		if (playerPosy >0 && points >= 5)
		{
			if (cubeLayout[playerPosy - 1][playerPosx][playerPosz] != 'B') {
				if (cubeLayout[playerPosy - 1][playerPosx][playerPosz] == 'G') {
					cubeLayout[playerPosy - 1][playerPosx][playerPosz] = 'R';
					points = points - 5;
					remcubes++;
					break;
				}
				else if (cubeLayout[playerPosy - 1][playerPosx][playerPosz] == 'R') {
					cubeLayout[playerPosy - 1][playerPosx][playerPosz] = 'Y';
					points = points - 5;
					remcubes++;
					break;
				}
				else if (cubeLayout[playerPosy - 1][playerPosx][playerPosz] == 'R') {
					cubeLayout[playerPosy - 1][playerPosx][playerPosz] = 'Y';
					points = points - 5;
					remcubes++;
					break;
				}
				else if (cubeLayout[playerPosy - 1][playerPosx][playerPosz] == 'Y') {
					cubeLayout[playerPosy - 1][playerPosx][playerPosz] = 'B';
					points = points - 5;
					remcubes++;
					break;
				}
			}
		}
		break;
	case 'q':
		calculateQ();
		Display();
		break;
	case 'e':
		calculateE();
		Display();
		break;
	case 'r':
		calculateR();
		Display();
		break;
	case 'x':
		if (debug == 1)
		{
			Camera.RotateX(5.0);
			Display();
		}
		break;
	case 'y':
		if (debug == 1)
		{
			Camera.RotateX(-5.0);
			Display();
		}
		break;
	case 'c':
		if (debug ==1)
		{
			Camera.StrafeRight(-0.1);
			Display();
		}
		break;
	case 'v':
		if (debug == 1)
		{
			Camera.StrafeRight(0.1);
			Display();
		}
		break;
	case 'f':
		if (debug == 1)
		{
			Camera.Move(F3dVector(0.0, -0.5, 0.0));
			Display();
		}
		break;
	case 't':
		if (debug == 1)
		{
			Camera.Move(F3dVector(0.0, 0.5, 0.0));
			Display();
		}
		break;
	}

}

void calculateE(void) { //The 'E' move
	if (points >= 20) { //at least 20P to function
		int remPosx, remPosz, i;
		SF3dVector addPos;
		addPos = CalcNextBoxPos();
		remPosx = (addPos.x);
		remPosz = (addPos.z);
		for (i = 0; i < dimension; i++) {
			if (remPosx < dimension && remPosx >= 0 && remPosz < dimension && remPosz >= 0) {
				if (cubeLayout[i][remPosx][remPosz] != 'E') {
					cubeLayout[i][remPosx][remPosz] = 'E';
				}
			}
		}
		lives++;
		points -= 20;
	}
}

void calculateR(void) { //The 'R' move
	for (int i = 1; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			for (int k = 0; k < dimension; k++) {
				if (cubeLayout[i][j][k] != 'E' && cubeLayout[i - 1][j][k] == 'E') {
					cubeLayout[i - 1][j][k] = cubeLayout[i][j][k];
					cubeLayout[i][j][k] = 'E';
				}
			}
		}
	}
}

void calculateQ(void) { //The 'Q' move
	int addCPosx, addCPosy, addCPosz;
	SF3dVector addCPos;
	addCPos = CalcNextBoxPos();
	addCPosx = (addCPos.x);
	addCPosy = addCPos.y;
	addCPosz = (addCPos.z);
	if (addCPosx < dimension && addCPosx >= 0 && addCPosz < dimension && addCPosz >= 0 && cubeLayout[addCPosy][addCPosx][addCPosz] != 'E') {
		cubeLayout[addCPosy][addCPosx][addCPosz] = 'E';
	}
}

void moveInY(void) {//Move the camera verticaly
	if (playerPosy < dimension) {
		if (cubeLayout[playerPosy][playerPosx][playerPosz] != 'E' && cubeLayout[playerPosy+1][playerPosx][playerPosz]=='E') {
			Camera.Move(F3dVector(0.0, 1.0, 0.0));
				points += 5;
			if (playerPosy == dimension - 1) { // +100P if cubes reach the top of the map
				lives++;
				points += 100;
			}
		}
		else if(cubeLayout[playerPosy][playerPosx][playerPosz] != 'E' && cubeLayout[playerPosy + 1][playerPosx][playerPosz] != 'E')
		{
			Camera.MoveForwards(1.0);
		}
	}
	if (playerPosy >=0)
	{
		float k = 0.0;
		for (int i = playerPosy - 1; i >= 0; i--) {
			if (cubeLayout[playerPosy][playerPosx][playerPosz] == 'E') {
				if (cubeLayout[i][playerPosx][playerPosz] == 'E') {
					k += 1.0;
				}
			}
		}
		if (cubeLayout[playerPosy - 1][playerPosx][playerPosz] == 'E' && cubeLayout[playerPosy][playerPosx][playerPosz] == 'E') {
			Camera.Move(F3dVector(0.0, -k, 0.0));
			Display();
			if ((points - 5 * ((int)k - 1)) < 0) {
				points -= 5 * ((int)k - 1);
				lives--;
				if (lives == 0) {
					gameOver = 1;
					GameOver();
				}
			}
			else {
				points -= 5 * ((int)k - 1);
			}
			reset();
		}
	}
}


void reset(void) { //Reset the player to x,z=dimension/2 , y=0
	playerPosy = Camera.GetPlayerPos().y;
	if (playerPosy <= 0) {
		lives--;
		Camera.SetPlayerPos((GLfloat)(dimension / 2), 1.0, (GLfloat)(dimension / 2));
		Display();
	}
	if (lives == 0) {
		gameOver = 1;
		GameOver();
	}
}


void drawOutline(int x, int y, int z) {  //outline of the cubes

	glColor3f(0, 0, 0);

	glBegin(GL_LINES);   //Front 
	glLineWidth(3.0);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y, z);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(3.0);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y + 1, z);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(3.0);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x, y + 1, z);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(3.0);
	glVertex3f(x, y + 1, z);
	glVertex3f(x, y, z);
	glEnd();


	glBegin(GL_LINES); // Back
	glLineWidth(3.0);
	glVertex3f(x, y, z + 1);
	glVertex3f(x + 1, y, z + 1);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(3.0);
	glVertex3f(x + 1, y, z + 1);
	glVertex3f(x + 1, y + 1, z + 1);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(3.0);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x, y + 1, z + 1);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(3.0);
	glVertex3f(x, y + 1, z + 1);
	glVertex3f(x, y, z + 1);
	glEnd();



	glBegin(GL_LINES); // Right 
	glLineWidth(3.0);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y, z + 1);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(3.0);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x + 1, y + 1, z);
	glEnd();



	glBegin(GL_LINES); // Left
	glLineWidth(3.0);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 1);
	glEnd();



	glBegin(GL_LINES);
	glLineWidth(3.0);
	glVertex3f(x, y + 1, z + 1);
	glVertex3f(x, y + 1, z);
	glEnd();



}



void drawBox(int x, int y, int z, char color) { //Draws a cube

	if (color == R) {
		glColor3f(0.6f, 0.0f, 0.0f);
	}
	else if (color == G) {
		glColor3f(0.0f, 0.5f, 0.0f);
	}
	else if (color == B) {
		glColor3f(0.0f, 0.0f, 0.5f);
	}
	else if (color == Y) {
		glColor3f(1.0f, 1.0f, 0.0f);
	}
	else if (color == M) {
		glColor4f(1.0f, 0.0f, 1.0f, -1.0f);
	}



	glPushMatrix();

	glBegin(GL_QUADS);  //Front 
	glNormal3f(0.0, 0.0, 2.0);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x, y + 1, z);
	glEnd();



	glBegin(GL_QUADS);  //Back
	glNormal3f(0.0, 0.0, -2.0);
	glVertex3f(x, y, z + 1);
	glVertex3f(x + 1, y, z + 1);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x, y + 1, z + 1);
	glEnd();

	glBegin(GL_QUADS);  //Right 
	glNormal3f(2.0, 0.0, 0.0);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y, z + 1);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x + 1, y + 1, z);
	glEnd();

	glBegin(GL_QUADS); // Left
	glNormal3f(-2.0, 0.0, 0.0);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 1);
	glVertex3f(x, y + 1, z + 1);
	glVertex3f(x, y + 1, z);
	glEnd();

	glBegin(GL_QUADS); //Top
	glNormal3f(0.0, 2.0, 0.0);
	glVertex3f(x, y + 1, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x, y + 1, z + 1);
	glEnd();

	glBegin(GL_QUADS); //Bottom
	glNormal3f(0.0, -2.0, 0.0);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y, z + 1);
	glVertex3f(x, y, z + 1);
	glEnd();

	drawOutline(x, y, z);
	glPopMatrix();

}

void drawText(int x, int y, char *string) { //screen text
	char *c;
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 780, 0, 780, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);

}

void viewAngle(void) {
	SF3dVector viewAngle;
	viewAngle = Camera.GetPlayerViewDir();
	viewDirx = viewAngle.x;
	viewDiry = viewAngle.y;
	viewDirz = viewAngle.z;
}


SF3dVector CalcNextBoxPos(void) { /*Calculates the possition of the cube to be entered*/
	SF3dVector MoveVector;		/* based on where the camera looks*/
	MoveVector.x = viewDirx*(1.0);//viewdir is cameras view direction
	MoveVector.y = viewDiry;
	MoveVector.z = viewDirz*(1.0);
	AddF3dVectorToVector(&MoveVector, &Camera.Position); // adds the two vectors
	return MoveVector;
}


void addBox(void) {

	int addCPosx, addCPosy, addCPosz; //The 'Left-click' function
	SF3dVector addCPos;
	addCPos = CalcNextBoxPos();
	addCPosx = (GLint)(addCPos.x);
	addCPosy = (GLint)addCPos.y;
	addCPosz = (GLint)(addCPos.z);
	if (debug == 1)
	{
		cout << "addposy/realPosy: " << addCPosy << "/" << playerPosy << " " << "addCPosx/realPosx: " << addCPosx << "/" << playerPosx << " " << "addCPosz/realPosz: " << addCPosz << "/" << playerPosz << "\n";

	}	
	for (int i = 0; i < dimension - 1; i++)
	{
		if ((addCPosy + i)<(dimension))
		{
			if (cubeLayout[addCPosy + i][addCPosx][addCPosz] == 'E') { /*checks if the position for the cube to be added is empty*/
				cubeLayout[addCPosy + i][addCPosx][addCPosz] = colorPicker();/*if not puts it on top of the other cube*/
				int color = cubeLayout[addCPosy + i][addCPosx][addCPosz];
				drawBox(addCPosx, addCPosy + i, addCPosz, color);
				break;
			}
		}
	}

}

void mouseButton(int button, int state, int x, int y) {
	if (remcubes > 0) {
		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_UP) {
				addBox();
				remcubes--;
				points += 5;
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_UP) {
			kickBox();
		}

	}
}

void GameOver(void) { //Exits the game
	if (gameOver == 1) {

		exit(1);
	}
}



void kickBox(void) { //The 'Right-click function'
	int i, k, tempcolor, foundE;
	SF3dVector lookPos;
	lookPos = CalcNextBoxPos();
	SI3dVector firstEmptyBox;
	if (debug == 1)
	{
		cout << playerPosy << "/" << (GLint)lookPos.y << "," << playerPosx << "/" << (GLint)lookPos.x << "," << playerPosz << "/" << (GLint)lookPos.z << "\n";
	}

		if (playerPosx == (GLint)lookPos.x) { //moving on x-axis
		if (Camera.GetPlayerPos().z > lookPos.z) {
			//z-=1 x=x
			k = 1;
			foundE = 0;
			while (foundE == 0) {
				if ((playerPosz)-k <= 0) {
					cubeLayout[playerPosy][playerPosx][(playerPosz)-k] = 'E';
				}
				if (cubeLayout[playerPosy][playerPosx][(playerPosz)-k] == 'E') {
					firstEmptyBox.x = playerPosx;
					firstEmptyBox.y = playerPosy;
					firstEmptyBox.z = (playerPosz - k);
					foundE = 1;
				}
				k++;
			}
			for (i = firstEmptyBox.z, k = 1; i < playerPosz; i++, k++) {
				tempcolor = cubeLayout[firstEmptyBox.y][firstEmptyBox.x][firstEmptyBox.z + k];
				cubeLayout[firstEmptyBox.y][firstEmptyBox.x][(firstEmptyBox.z) + (k - 1)] = tempcolor;
				cubeLayout[firstEmptyBox.y][firstEmptyBox.x][firstEmptyBox.z + k] = 'E';
			}
		}
		else if (Camera.GetPlayerPos().z < lookPos.z) { 
			//z+=1 x=x
			k = 1;
			foundE = 0;
			while (foundE == 0) {
				if ((playerPosz)+k >= dimension - 1) {
					cubeLayout[playerPosy][playerPosx][(playerPosz)+k] = 'E';
				}
				if (cubeLayout[playerPosy][playerPosx][playerPosz + k] == 'E') {
					firstEmptyBox.x = playerPosx;
					firstEmptyBox.y = playerPosy;
					firstEmptyBox.z = (playerPosz + k);
					foundE = 1;
				}
				k++;
			}
			for (i = playerPosz + 1, k = 1; i <= firstEmptyBox.z; i++, k++) {
				tempcolor = cubeLayout[firstEmptyBox.y][firstEmptyBox.x][firstEmptyBox.z - k];
				cubeLayout[firstEmptyBox.y][firstEmptyBox.x][firstEmptyBox.z - (k - 1)] = tempcolor;
				cubeLayout[firstEmptyBox.y][firstEmptyBox.x][firstEmptyBox.z - k] = 'E';
			}
		}
	}
	else if (playerPosz == (GLint)lookPos.z) { // moving on z-axis
		if (Camera.GetPlayerPos().x > lookPos.x) {
			// x-=1 z=z
			k = 1;
			foundE = 0;
			while (foundE == 0) {
				if ((playerPosx)-k <= 0) {
					cubeLayout[playerPosy][(playerPosx)-k][playerPosz] = 'E';
				}
				if (cubeLayout[playerPosy][(playerPosx - k)][(playerPosz)] == 'E') {
					firstEmptyBox.x = (playerPosx - k);
					firstEmptyBox.y = playerPosy;
					firstEmptyBox.z = playerPosz;
					foundE = 1;
				}
				k++;
			}
			for (i = firstEmptyBox.x, k = 1; i < playerPosx; i++, k++) {
				tempcolor = cubeLayout[firstEmptyBox.y][firstEmptyBox.x + k][firstEmptyBox.z];
				cubeLayout[firstEmptyBox.y][firstEmptyBox.x + (k - 1)][firstEmptyBox.z] = tempcolor;
				cubeLayout[firstEmptyBox.y][firstEmptyBox.x + k][firstEmptyBox.z] = 'E';
			}
		}
		else if (Camera.GetPlayerPos().x < lookPos.x) {
			// x+=1 z=z
			k = 1;
			foundE = 0;
			while (foundE == 0) {
				if ((playerPosx + k) >= dimension - 1) {
					cubeLayout[playerPosy][(playerPosx + k)][(playerPosz)] = 'E';
				}
				if (cubeLayout[playerPosy][(playerPosx + k)][(playerPosz)] == 'E') {
					firstEmptyBox.x = (playerPosx + k);
					firstEmptyBox.y = playerPosy;
					firstEmptyBox.z = playerPosz;
					foundE = 1;
				}
				k++;
			}
			for (i = playerPosx + 1, k = 1; i < firstEmptyBox.x; i++, k++) {
				tempcolor = cubeLayout[firstEmptyBox.y][firstEmptyBox.x - k][firstEmptyBox.z];
				cubeLayout[firstEmptyBox.y][firstEmptyBox.x - (k - 1)][firstEmptyBox.z] = tempcolor;
				cubeLayout[firstEmptyBox.y][firstEmptyBox.x - k][firstEmptyBox.z] = 'E';
			}
		}
	}

}

//*****************************************************************************//
//Lights



void init(void) {

	glEnable(GL_DEPTH_TEST);
	// Setup the view of the cube. 
	glMatrixMode(GL_PROJECTION);
	gluPerspective( 40.0,
		 1.0,
		 1.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  //eye is at (0,0,5) 
		0.0, 0.0, 0.0,      // center is at (0,0,0) 
		0.0, 1.0, 0.);      // up is in positive Y direction 

	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);

}

void initLights(void) {
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	GLfloat amb_light[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
	GLfloat spotPos1[] = { 0.0,(float)dimension,0.0,0 };
	GLfloat spotPos2[] = { (float)dimension,(float)dimension,0.0,0 };
	GLfloat spotPos3[] = { 0.0,(float)dimension,(float)dimension,0 };
	GLfloat spotPos4[] = { (float)dimension,(float)dimension,(float)dimension,0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_POSITION, spotPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_POSITION, spotPos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT2, GL_POSITION, spotPos3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT3, GL_POSITION, spotPos4);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);

}


void Debug(void) {
	char d;
	int i, j, k;
	printf("Activate Debuging printouts (y/n): ");
	cin >> d;

	if (d == 'y') {
		debug = 1;		
	}
	else {
		printf("Enjoy!! \n");
	}
}



int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	srand(time(0));

	printf("Set Grid dimension: ");
	scanf("%d", &dimension);
	while (dimension <= 0) {
		printf("Dimensions should be over 0!! \n Preferably greater than 5 \n Try again: ");
		scanf("%d", &dimension);
	}
	Debug();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(840, 624);
	glutCreateWindow("Cubeseption");

	Camera.Move(F3dVector(0.0, 0.0, 3.0));
	Camera.MoveForwards(1.0);

	initCubeLayout();

	Camera.SetPlayerPos((GLfloat)(dimension / 2), 1.0, (GLfloat)(dimension / 2));

	glutDisplayFunc(Display);
	glutIdleFunc(&Display);

	init();
	initLights();

	glutReshapeFunc(reshape);
	glutKeyboardFunc(KeyDown);
	glutMainLoop();

	for (int i = 0; i < dimension; ++i) { //clear the cubeLayout matrix and return
		delete[] cubeLayout[i];
	}
	delete[] cubeLayout;

	return 0;
}
