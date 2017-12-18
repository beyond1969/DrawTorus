/*
	Made by Hyeokjung Kim
	e-mail : beyond1969@gmail.com

	A : Add a Circle
	S :	Delete a Circle
	J : Add a Line for circles
	K : Delete a Line for circles
	ESC : Exit
	Right-Click : Menu to change 2x2, 3x3 rotation matrix
*/

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
// 삼각함수 사용을 위함
#include <math.h>
#include "MatrixOperator.h"

#define PI 3.14159

static Vector3 p[36][18];
int n[36][18];
static Matrix3 circleRotate;
static double circle2X2[2][2];	// 2x2 변환 매트릭스
static Matrix3 torusRotate;

static int controlCircle;
static int controlTorus;

bool controlMatrix;	// 2x2, 3x3 변환용

void init() {
	controlMatrix = false;
	controlCircle = 0;
	controlTorus = 0;

	Vector3 circleO = Vector3(0.8, 0.8, 0);	// circle center point
	// Initializing first point
	p[0][0].setVector3(1, 1, 0);

	// Setting Circle Rotation Matrix 3x3
	circleRotate.setCol1(cos(20 * PI / 180), sin(20 * PI / 180), 0);
	circleRotate.setCol2(-1 * sin(20 * PI / 180), cos(20 * PI / 180), 0);
	circleRotate.setCol3(0, 0, 1);
	// Setting Circle Rotation Matrix 2x2
	circle2X2[0][0] = cos(20 * PI / 180);	circle2X2[0][1] = -1 * sin(20 * PI / 180);
	circle2X2[1][0] = sin(20 * PI / 180);	circle2X2[1][1] = cos(20 * PI / 180);

	// Initializing all circle points
	for (int i = 1; i < 18; i++) {
		if (!controlMatrix)
			p[0][i] = (circleRotate * (p[0][i - 1] - circleO)) + circleO;
		else
			p[0][i].setVector3(((p[0][i - 1] - circleO).getVector31() * circle2X2[0][0]) + ((p[0][i - 1] - circleO).getVector32()*circle2X2[0][1]),
			((p[0][i - 1] - circleO).getVector31() * circle2X2[1][0]) + ((p[0][i - 1] - circleO).getVector32()*circle2X2[1][1]),
				(p[0][i - 1] - circleO).getVector33());
	}

	// Setting Torus Rotation Matrix
	torusRotate.setCol1(cos(10 * PI / 180), 0, -1 * sin(10 * PI / 180));
	torusRotate.setCol2(0, 1, 0);
	torusRotate.setCol3(sin(10 * PI / 180), 0, cos(10 * PI / 180));

	// Initializing all torus points
	for(int i = 1; i < 36; i++)
		for (int j = 0; j < 18; j++) {
			p[i][j] = (torusRotate * p[i - 1][j]);
			n[i][j] = 0;
		}
}

void keyboard(unsigned char c, int x, int y) {
	switch (c) {
	case 'a' | 'A':
		controlTorus++;
		if (controlTorus > 36)
			controlTorus = 0;
		glutPostRedisplay();
		break;
	case 's' | 'S':
		controlTorus--;
		if (controlTorus < 0)
			controlTorus = 36;
		glutPostRedisplay();
		break;
	case 'j' | 'J':
		controlCircle++;
		if (controlCircle > 18)
			controlCircle = 0;
		glutPostRedisplay();
		break;
	case 'k' | 'K':
		controlCircle--;
		if (controlCircle < 0)
			controlCircle = 18;
		glutPostRedisplay();
		break;
	case VK_ESCAPE:
		exit(0);
		break;
	}
}

void renderSceneMatrix() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.5, 0.5, 0.5, 0, 0, 0, 0, 1, 0);

	// Coordinate Axis Lines
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		// Axis-x
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		// Axis-y
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		// Axis-z
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
	}
	glEnd();
	// Normal Vectors
	Vector3 normal;
	Vector3 center;
	glLineWidth(2);
	glColor3f(0, 0, 0);
	if (controlCircle != 0 && controlTorus != 0) {
		for (int j = 0; j < controlCircle; j++) {
			for (int i = 0; i < controlTorus; i++) {
				if (i + 1 < 36 && j + 1 < 18)
					normal = ((p[i][j] - p[i][j + 1]) * (p[i + 1][j + 1] - p[i][j + 1]));
				else if (i + 1 >= 36 && j + 1 < 18)
					normal = ((p[i][j] - p[i][j + 1]) * (p[0][j + 1] - p[i][j + 1]));
				else if (i + 1 < 36 && j + 1 >= 18)
					normal = ((p[i][j] - p[i][0]) * (p[i + 1][0] - p[i][0]));
				else
					normal = ((p[i][j] - p[i][0]) * (p[0][0] - p[i][0]));

				double length = sqrt(normal.getVector31()*normal.getVector31() + normal.getVector32()*normal.getVector32() + normal.getVector33() * normal.getVector33());
				normal.setVector3(normal.getVector31() / length, normal.getVector32() / length, normal.getVector33() / length);
				normal = normal.vecScalarMult(0.2);

				if (i + 1 < 36 && j + 1 < 18)
					center.setVector3((p[i][j].getVector31() + p[i][j + 1].getVector31() + p[i + 1][j].getVector31() + p[i + 1][j + 1].getVector31()) / 4.0f,
					(p[i][j].getVector32() + p[i][j + 1].getVector32() + p[i + 1][j].getVector32() + p[i + 1][j + 1].getVector32()) / 4.0f,
						(p[i][j].getVector33() + p[i][j + 1].getVector33() + p[i + 1][j].getVector33() + p[i + 1][j + 1].getVector33()) / 4.0f);
				else if (i + 1 >= 36 && j + 1 < 18)
					center.setVector3((p[i][j].getVector31() + p[i][j + 1].getVector31() + p[0][j].getVector31() + p[0][j + 1].getVector31()) / 4.0f,
					(p[i][j].getVector32() + p[i][j + 1].getVector32() + p[0][j].getVector32() + p[0][j + 1].getVector32()) / 4.0f,
						(p[i][j].getVector33() + p[i][j + 1].getVector33() + p[0][j].getVector33() + p[0][j + 1].getVector33()) / 4.0f);
				else if (i + 1 < 36 && j + 1 >= 18)
					center.setVector3((p[i][j].getVector31() + p[i][0].getVector31() + p[i + 1][j].getVector31() + p[i + 1][0].getVector31()) / 4.0f,
					(p[i][j].getVector32() + p[i][0].getVector32() + p[i + 1][j].getVector32() + p[i + 1][0].getVector32()) / 4.0f,
						(p[i][j].getVector33() + p[i][0].getVector33() + p[i + 1][j].getVector33() + p[i + 1][0].getVector33()) / 4.0f);
				else
					center.setVector3((p[i][j].getVector31() + p[i][0].getVector31() + p[0][j].getVector31() + p[0][0].getVector31()) / 4.0f,
					(p[i][j].getVector32() + p[i][0].getVector32() + p[0][j].getVector32() + p[0][0].getVector32()) / 4.0f,
						(p[i][j].getVector33() + p[i][0].getVector33() + p[0][j].getVector33() + p[0][0].getVector33()) / 4.0f);
				
				double dotProduct;
				Vector3 camera = Vector3(0.5, 0.5, 0.5);
				dotProduct = normal%camera;
				if (dotProduct < 0) {
					n[i][j] = -1;
				}
				else if (dotProduct >= 0) {
					n[i][j] = 1;
				}
				glBegin(GL_LINES);
				{
					glVertex3f(center.getVector31(), center.getVector32(), center.getVector33());
					glVertex3f(normal.getVector31() + center.getVector31(), normal.getVector32() + center.getVector32(), normal.getVector33() + center.getVector33());
				}
				glEnd();
			}
		}
	}
	
	// Torus Draw
	glLineWidth(1);
	for (int j = 0; j < controlCircle; j++) {
		for (int i = 0; i < controlTorus; i++) {
			if (n[i][j] < 0)
				glColor3f(1, 0, 0);
			else
				glColor3f(0, 0, 1);
			glBegin(GL_QUAD_STRIP);
			{
				glVertex3d(p[i][j].getVector31(), p[i][j].getVector32(), p[i][j].getVector33());

				if (j + 1 < 18)
					glVertex3d(p[i][j + 1].getVector31(), p[i][j + 1].getVector32(), p[i][j + 1].getVector33());
				else
					glVertex3d(p[i][0].getVector31(), p[i][0].getVector32(), p[i][0].getVector33());

				if (i + 1 < 36)
					glVertex3d(p[i + 1][j].getVector31(), p[i + 1][j].getVector32(), p[i + 1][j].getVector33());
				else
					glVertex3d(p[0][j].getVector31(), p[0][j].getVector32(), p[0][j].getVector33());

				if (i + 1 < 36 && j + 1 < 18)
					glVertex3d(p[i + 1][j + 1].getVector31(), p[i + 1][j + 1].getVector32(), p[i + 1][j + 1].getVector33());
				else if (i + 1 < 36 && j + 1 == 18)
					glVertex3d(p[i + 1][0].getVector31(), p[i + 1][0].getVector32(), p[i + 1][0].getVector33());
				else if (i + 1 == 36 && j + 1 < 18)
					glVertex3d(p[0][j + 1].getVector31(), p[0][j + 1].getVector32(), p[0][j + 1].getVector33());
				else
					glVertex3d(p[0][0].getVector31(), p[0][0].getVector32(), p[0][0].getVector33());
			}
			glEnd();
		}
	}
	// Polygon Lines
	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	for (int j = 0; j < controlCircle; j++) {
		glBegin(GL_QUAD_STRIP);
		{
			for (int i = 0; i <= controlTorus; i++) {
				if (i < 36) {
					glVertex3d(p[i][j].getVector31(), p[i][j].getVector32(), p[i][j].getVector33());
					if (j + 1 < 18)
						glVertex3d(p[i][j + 1].getVector31(), p[i][j + 1].getVector32(), p[i][j + 1].getVector33());
					else
						glVertex3d(p[i][0].getVector31(), p[i][0].getVector32(), p[i][0].getVector33());
				}
				else {
					glVertex3d(p[0][j].getVector31(), p[0][j].getVector32(), p[0][j].getVector33());
					if (j + 1 < 18)
						glVertex3d(p[0][j + 1].getVector31(), p[0][j + 1].getVector32(), p[0][j + 1].getVector33());
					else
						glVertex3d(p[0][0].getVector31(), p[0][0].getVector32(), p[0][0].getVector33());
				}
			}
		}
		glEnd();
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glFlush();
}

void ChangeSize(int w, int h) {
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* 3D screen */
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (float)h / (float)w, 2.0*(float)h / (float)w, -10.0, 10.0);
	else
		glOrtho(-2.0*(float)w / (float)h, 2.0*(float)w / (float)h, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void SetupRC() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void menu(int value) {
	if (value == 1) {
		controlMatrix = true;
	}
	else if (value == 2) {
		controlMatrix = false;
	}
	init();
	glutPostRedisplay();
}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("SIMPLE");
	glutDisplayFunc(renderSceneMatrix);
	glutReshapeFunc(ChangeSize);

	glutKeyboardFunc(keyboard);

	glutCreateMenu(menu);
	glutAddMenuEntry("2X2", 1);
	glutAddMenuEntry("3X3", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	SetupRC();

	glutMainLoop();
}