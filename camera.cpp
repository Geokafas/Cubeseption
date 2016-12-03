#include "camera.h"
#include "math.h"
#include <iostream>
#include <stdio.h>

SF3dVector F3dVector(GLfloat x, GLfloat y, GLfloat z)
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}
SF3dVector AddF3dVectors(SF3dVector* u, SF3dVector* v)
{
	SF3dVector result;
	result.x = u->x + v->x;
	result.y = u->y + v->y;
	result.z = u->z + v->z;
	return result;
}
SI3dVector I3dVector(int x, int y, int z)
{
	SI3dVector pos;
	pos.x = x;
	pos.y = y;
	pos.z = z;
	return pos;
}

void AddF3dVectorToVector(SF3dVector * Dst, SF3dVector * V2)
{
	Dst->x += V2->x;
	Dst->y += V2->y;
	Dst->z += V2->z;
}


/***************************************************************************************/

CCamera::CCamera()
{
	Position = F3dVector(0.0,//initialize camera Position
		1.0,
		0.0);
	ViewDir = F3dVector(0.0,//and view diraction
		0.0,
		0.0);
	ViewDirChanged = false;
	
	RotatedX = RotatedY = RotatedZ = 0.0;
}

void CCamera::SetPlayerPos(GLfloat x, GLfloat y, GLfloat z) { //Sets the player position inside the game
	Position.x = x;
	Position.y = y;
	Position.z = z;
}

SI3dVector CCamera::GetPlayerPos(void) {//feeds player Position into the game
	SI3dVector pos;
	pos.x = Position.x;
	pos.y = Position.y;
	pos.z = Position.z + 1;
	return pos;
}

SF3dVector CCamera::GetPlayerViewDir(void) {//feeds player view direction to the game
	SF3dVector view;
	view.x = cos((RotatedY + 90.0) * PIdiv180);
	view.y = ViewDir.y;
	view.z = -sin((RotatedY + 90.0) * PIdiv180);
	return view;
}


void CCamera::GetViewDir(void)
{
	SF3dVector Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos((RotatedY + 90.0) * PIdiv180);
	Step1.z = -sin((RotatedY + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos(RotatedX * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(RotatedX * PIdiv180);
	ViewDir = Step2;
}
void CCamera::Move(SF3dVector Direction) //vertical movement
{
	AddF3dVectorToVector(&Position, &Direction);
}

void CCamera::RotateY(GLfloat Angle)
{
	RotatedY += Angle;
	ViewDirChanged = 1;
}



void CCamera::Render(void)
{
	glRotatef(-RotatedX, 1.0, 0.0, 0.0);
	glRotatef(-RotatedY, 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ, 0.0, 0.0, 1.0);
	glTranslatef(-Position.x, -Position.y, -Position.z);
}

void CCamera::MoveForwards(GLfloat Distance)
{
	if (ViewDirChanged == 1) GetViewDir();
	SF3dVector MoveVector;
	MoveVector.x = ViewDir.x * -Distance;
	MoveVector.y = ViewDir.y * -Distance;
	MoveVector.z = ViewDir.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector);
}

//*******FOR DEBUGING************//

void CCamera::RotateX(GLfloat Angle)
{
	RotatedX += Angle;
	ViewDirChanged = 1;
}


void CCamera::StrafeRight(GLfloat Distance)
{
	if (ViewDirChanged) GetViewDir();
	SF3dVector MoveVector;
	MoveVector.z = -ViewDir.x * -Distance;
	MoveVector.y = 0.0;
	MoveVector.x = ViewDir.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector);
}