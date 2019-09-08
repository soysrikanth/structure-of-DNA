#include <iostream>
#include <stdlib.h>
#include<math.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define PI 3.142f

GLfloat angleX=90.0f,angleY=0.0f,angleZ=0.0f, vertexes[4][3], normal[3],zoom=-40.0f;
static char text1[30]="DNA Structure";
using namespace std;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {

	case 27: //Escape key
		exit(0);
		break;

	case 'x':

		angleX += 10.0;
		glutPostRedisplay();
		break;

	case 'y':
		angleY += 10.0;
		glutPostRedisplay();
		break;

	case 'z':
		angleZ += 10.0;
		glutPostRedisplay();
		break;

	case 'd':
		zoom += 10.0f;
		glutPostRedisplay();
		break;

	case 'f':
		zoom += 10.0f;
		glutPostRedisplay();
		break;

	case 'g':
		zoom -= 10.0f;
		glutPostRedisplay();
		break;
	}
}

void normalize(float vector[3])
{
	float length;

	length = (float)sqrt((vector[0]*vector[0])+(vector[1]*vector[1])+(vector[2]*vector[2]));

	if (length == 0.0f)
		length = 1.0f;

	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}


void computeNormals(float v[3][3],float n[3])
{
	float v1[3], v2[3];

	//Vector1

	v1[0] = v[0][0] - v[1][0];
	v1[1] = v[0][1] - v[1][1];
	v1[2] = v[0][2] - v[1][2];

	//Vector2

	v2[0] = v[1][0] - v[2][0];
	v2[1] = v[1][1] - v[2][1];
	v2[2] = v[1][2] - v[2][2];

	//Normal

	n[0] = v1[1] * v2[2] - v1[2] * v2[1];
	n[1] = v1[2] * v2[0] - v2[2] * v1[0];
	n[2] = v1[0] * v2[1] - v1[1] * v2[0];

	normalize(n);

}

void drawHelix()
{
	GLfloat x, y, z, phi, theta, v, u, r;
	int twists = 10;

	GLfloat matColor[] = { 0.4f, 0.2f, 0.8f, 1.0f };
	GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLoadIdentity();

	gluLookAt(0, 5, 50, 0, 0, 0, 0, 1, 0);

	glPushMatrix();

	glTranslatef(0, 20, zoom);
	/*glRotatef(angle / 2.0f, 1, 0, 0);
	glRotatef(angle / 3.0f, 0, 1, 0);
	*/
	glRotatef(angleX,1,0,0);
	glRotatef(angleY, 1, 1, 0);
	glRotatef(angleZ, 0, 0, 1);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,matColor);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,matSpecular);

	r = 1.5f;

	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,0.0f);

		for (phi = 0; phi <= 360; phi += 20.0)
		{
			for (theta = 0; theta <= 360 * twists; theta += 20.0)
			{

				v = (phi / 180.0f*PI);
				u = (theta / 180.0f*PI);

				x = float(cos(u)*(2.0f + cos(v)))*r;
				y = float(sin(u)*(2.0f + cos(v)))*r;
				z = float(((u)+sin(v))*r);

				vertexes[0][0] = x;
				vertexes[0][1] = y;
				vertexes[0][2] = z;

				v = (phi / 180.0f*PI);
				u = ((theta + 20) / 180.0f*PI);

				x = float(cos(u)*(2.0f + cos(v)))*r;
				y = float(sin(u)*(2.0f + cos(v)))*r;
				z = float((u)+sin(v))*r;

				vertexes[1][0] = x;
				vertexes[1][1] = y;
				vertexes[1][2] = z;

				v = ((phi + 20) / 180.0f*PI);
				u = ((theta + 20) / 180.0f*PI);

				x = float(cos(u)*(2.0f + cos(v)))*r;
				y = float(sin(u)*(2.0f + cos(v)))*r;
				z = float((u)+sin(v))*r;

				vertexes[2][0] = x;
				vertexes[2][1] = y;
				vertexes[2][2] = z;

				v = ((phi + 20) / 180.0f*PI);
				u = ((theta) / 180.0f*PI);

				x = float(cos(u)*(2.0f + cos(v)))*r;
				y = float(sin(u)*(2.0f + cos(v)))*r;
				z = float((u)+sin(v))*r;

				vertexes[3][0] = x;
				vertexes[3][1] = y;
				vertexes[3][2] = z;

				computeNormals(vertexes, normal);

				glNormal3f(normal[0], normal[1], normal[2]);

				glVertex3f(vertexes[0][0], vertexes[0][1], vertexes[0][2]);
				glVertex3f(vertexes[1][0], vertexes[1][1], vertexes[1][2]);
				glVertex3f(vertexes[2][0], vertexes[2][1], vertexes[2][2]);
				glVertex3f(vertexes[3][0], vertexes[3][1], vertexes[3][2]);

			}
		}

		glEnd();
		//glPopMatrix();

		//glPushMatrix();
		glColor3f(0.0f,0.0f,1.0f);
		glTranslatef(0.0f,0.0f,90.0f);

		//glRotatef(angle / 2.0f, 1, 0, 0);
		//glRotatef(angle / 3.0f, 0, 1, 0);

		glBegin(GL_QUADS);
		//glColor3f(1.0f,1.0f,0.0f);

		for (phi = 0; phi <= 360; phi += 20.0)
		{
			for (theta = 0; theta >= -360 * twists; theta -= 20.0)
			{

				v = (phi / 180.0f*PI);
				u = (theta / 180.0f*PI);

				x = float(cos(u)*(2.0f + cos(v)))*r;
				y = float(sin(u)*(2.0f + cos(v)))*r;
				z = float(((u)+sin(v))*r);

				vertexes[0][0] =x;
				vertexes[0][1] = y;
				vertexes[0][2] = z;

				v = (phi / 180.0f*PI);
				u = ((theta + 20) / 180.0f*PI);

				x = float(cos(u)*(2.0f + cos(v)))*r;
				y = float(sin(u)*(2.0f + cos(v)))*r;
				z = float((u)+sin(v))*r;

				vertexes[1][0] = x;
				vertexes[1][1] = y;
				vertexes[1][2] = z;

				v = ((phi + 20) / 180.0f*PI);
				u = ((theta + 20) / 180.0f*PI);

				x = float(cos(u)*(2.0f + cos(v)))*r;
				y = float(sin(u)*(2.0f + cos(v)))*r;
				z = float((u)+sin(v))*r;

				vertexes[2][0] = x;
				vertexes[2][1] = y;
				vertexes[2][2] = z;

				v = ((phi + 20) / 180.0f*PI);
				u = ((theta) / 180.0f*PI);

				x = float(cos(u)*(2.0f + cos(v)))*r;
				y = float(sin(u)*(2.0f + cos(v)))*r;
				z = float((u)+sin(v))*r;

				vertexes[3][0] = x;
				vertexes[3][1] = y;
				vertexes[3][2] = z;

				computeNormals(vertexes, normal);

				glNormal3f(normal[0], normal[1], normal[2]);

				glVertex3f(vertexes[0][0], vertexes[0][1], vertexes[0][2]);
				glVertex3f(vertexes[1][0], vertexes[1][1], vertexes[1][2]);
				glVertex3f(vertexes[2][0], vertexes[2][1], vertexes[2][2]);
				glVertex3f(vertexes[3][0], vertexes[3][1], vertexes[3][2]);

			}
		}

		glEnd();
		glPopMatrix();


	}

void initRendering() {
	/*glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50,(float)w/(float)h,5,2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	glEnable(GL_DEPTH_TEST);

	GLfloat global_ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };		
	GLfloat light0pos[4] = { 0.0f, 5.0f, 10.0f, 1.0f };		
	GLfloat light0ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };		
	GLfloat light0diffuse[4] = { 0.3f, 0.3f, 0.3f, 1.0f };		
	GLfloat light0specular[4] = { 0.8f, 0.8f, 0.8f, 1.0f };		

	GLfloat lmodel_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };		
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);		

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);		
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);				
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0ambient);			
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0diffuse);			
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0specular);			

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glEnable(GL_NORMALIZE);

	glShadeModel(GL_SMOOTH);									

	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5);						



	glEnable(GL_COLOR_MATERIAL);


}

void handleResize(int w, int h) {
	/*glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);

	glOrtho(0,640,480,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (float)w / (float)h, 5, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void drawScene() {
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 1.0f, -6.0f);

	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat directedLightPos[] = { -10.0f, 15.0f, 20.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glColor3f(1.0f,0.0f,0.0f);
	drawHelix();

	glFlush();
	glutSwapBuffers();
}

/*void update(int value)
{
	angle += 10.0;
	glutPostRedisplay();
	glutTimerFunc(10,update,1);
}
*/
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);

	glutCreateWindow("DNA");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	//glutTimerFunc(25,update,1);
	glutMainLoop();
	return 0;
}

