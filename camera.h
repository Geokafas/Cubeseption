#include <GL/glut.h>

#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct SF3dVector  //Float 3d-vect, normally used
{
	GLfloat x, y, z;
};
struct SF2dVector
{
	GLfloat x, y;
};

struct SI3dVector
{
	int x, y, z;
};

SF3dVector F3dVector(GLfloat x, GLfloat y, GLfloat z);
SF3dVector AddF3dVectors(SF3dVector * u, SF3dVector * v);
SI3dVector I3dVector(int x, int y, int z);
void AddF3dVectorToVector(SF3dVector * Dst, SF3dVector * V2);

class CCamera
{
private:

	/*Not used for rendering the camera, but for "moveforwards"*/
	int ViewDirChanged = 0;
	GLfloat RotatedX, RotatedY, RotatedZ;

public:
	CCamera();				//inits the values (Position: (dimension/2|1|dimension/2))
	void Render(void);		
	void GetViewDir(void);
	SF3dVector ViewDir;
	void Move(SF3dVector Direction);
	void RotateY(GLfloat Angle);
	void MoveForwards(GLfloat Distance);
	SI3dVector GetPlayerPos();
	void SetPlayerPos(GLfloat x, GLfloat y, GLfloat z);
	SF3dVector GetPlayerViewDir();
	SF3dVector Position;
	void RotateX(GLfloat Angle);
	void StrafeRight(GLfloat Distance);
};
