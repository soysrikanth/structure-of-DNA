#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

const float CIRCLE = 3.14159/180;
static float d=0, z=1.0, r=0.0, t=0.0;
static int win;
static int menid;
static int submenid;
static int primitive = 0;
static int width = 800;
static int height = 700;
static char text0[30]="atomic structure";
static char text1[30]="DNA Structure";
static char text2[70]="The DNA double helix is stabilized by hydrogen bonds between";
static char text3[70]="the bases attached to the two strands. The four bases found in";
static char text4[70]="DNA are adenine(A), cytosine(C), guanine(G) and thymine (T)";
static char text5[70]="These four bases are attached to the sugar/phosphate to form ";
static char text6[70]="the complete nucleotide.";
static char menu1[30]="key";
static char menu2[30]= "Z/z : Zoom out/in";
static char menu3[30]= "R/r : Y axis Rotate";
static char menu4[30]= "T/t : X axis Rotate";
static char menu5[30]= "c : Restore Default Value";

void createMenu(void);
void menu(int value);
void disp(void);

bool _highShininess = false; //Whether the shininess parameter is high
bool _lowSpecularity = false; //Whether the specularity parameter is high
bool _emission = true; //Whether the emission parameter is turned on

void createMenu(void){
  // Create a submenu, this has to be done first.
  submenid = glutCreateMenu(menu);
  // Add sub menu entry
  glutAddMenuEntry("Normal", 2);
  glutAddMenuEntry("DNA Structure", 3);
  // Create the menu, this menu becomes the current menu
  menid = glutCreateMenu(menu);
  // Create an entry
  glutAddMenuEntry("Clear", 1);
  glutAddSubMenu("Draw", submenid);
  // Create an entry
  glutAddMenuEntry("Quit", 5);
  // Let the menu respond on the right mouse button
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int value){
  if(value == 0){
    glutDestroyWindow(win);
    exit(0);
  }else{
    primitive=value;
  }
  // you would want to redraw now
  glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
        case 'z':  // Zoom
             z = (z + 0.1) ;
             glutPostRedisplay();
             break;
        case 'Z':
             z = (z - 0.1) ;
             glutPostRedisplay();
             break;
        case 'r':  // y axis rotate (Auto)
              r = (r + 2) ;
              glutPostRedisplay();
              break;
         case 'R':
              r = (r - 2) ;
              glutPostRedisplay();
              break;
         case 't':  // x axis rotate                
              t = (t + 2) ;
              glutPostRedisplay();
              break;
         case 'T':
              t = (t - 2) ;
              glutPostRedisplay();
              break;
         case 'c':
              d=0, z=1.0, r=0.0, t=0.0, _emission = true, _lowSpecularity = false, _highShininess = false ;
              glutPostRedisplay();
              break;
	}
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_COLOR_MATERIAL); //Disable color materials, so that glMaterial calls work
}

void handleResize(int w, int h) {
	glViewport(-225, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 200.0);
}

void initLight(float radius) {
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
	GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat lightColor[] = {0.6, 0.6, 0.6, 1.0};
	GLfloat lightPos[] = {1.5 * radius, 3 * radius, 1.5 * radius, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);   	//Diffuse (non-shiny) light component
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);   	//Specular (shiny) light component
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);  
}

void draw_circle(float radius, float r, float g, float b) {
	//Determine the specularity, emissivity, and shininess parameters, based on
	//variables that can be toggled with keystrokes
	float specularity;
	if (_lowSpecularity) {
		specularity = 0.3;
	}
	else {
		specularity = 1.5;
	}	
	float emissivity;
	if (_emission) {
		emissivity = 0.03;
	}
	else {
		emissivity = 0;
	}	
	float shininess;
	if (_highShininess) {
		shininess = 25;
	}
	else {
		shininess = 12;
	}
	GLfloat materialColor[] = {r, g, b, 1.0};	  //The color of the sphere
	GLfloat materialSpecular[] = {specularity, specularity, specularity, 1.0};	  //The specular (shiny) component of the material
	GLfloat materialEmission[] = {emissivity, emissivity, emissivity, 1.0};	   //The color emitted by the material
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess); //The shininess parameter        
    glutSolidSphere(radius, 20, 20);  
}

void draw_circle_object(float radius, float x, float y, float z, char color) {
     glTranslatef(x,y,z);
     if(color=='y')
        draw_circle(radius, 1.0, 1.0, 0.0);
     else if(color=='r')
        draw_circle(radius, 1.0, 0.0, 0.0);
	 else if(color=='g')
        draw_circle(radius, 0.0, 1.0, 0.0);
	 else if(color=='p')
        draw_circle(radius, 0.6, 0.4, 0.7);
     else if(color=='b')
        draw_circle(radius, 0.0, 0.0, 1.0);
	 else if(color=='w')
        draw_circle(radius, 255.0, 255.0, 255.0);
     glTranslatef(-x,-y,-z);
}

void drawModel(int mode) {
	if (mode==0)  {
		glColor3f(0.0,0.0,0.0);
        
		for(double i = -10 ; i < 11 ; i+=4){
			draw_circle_object(0.4, 0 , (i/1.5) , 1  ,'p');
			draw_circle_object(0.4, 0 , (i/1.5) , 2  ,'g');
		}

		for(double i = -10 ; i < 11 ; i+=2){
			draw_circle_object(0.4, 0 , (i/1.5) , 1  ,'r');
			draw_circle_object(0.4, 0 , (i/1.5) , 2  ,'b');
		}

		for(double i = -10 ; i < 11 ; i++){
			draw_circle_object(0.4, 0 , (i/1.5) , 0  ,'y');
			draw_circle_object(0.4, 0 , (i/1.5) , 3  ,'y');
		}
		draw_circle_object(0,  0.2, (6/1.7) , -0.3  ,'w');
	} else if (mode==1) {
        glColor3f(0.0,0.0,0.0);
		draw_circle_object(0.4, -1 , (-10/1.4) , 0  ,'y');
		draw_circle_object(0.4, 1 , (-9/1.5) , 0.5  ,'y');
		draw_circle_object(0.4, -1 , (-8/1.6) , -0.5  ,'y');
		draw_circle_object(0.4, 1 , (-7/1.4) , 0  ,'y');
		draw_circle_object(0.4, -1, (-6/1.5) , 0.5  ,'y');
		draw_circle_object(0.4, 1, (-5/1.6) , -0.5  ,'y');
		draw_circle_object(0.4, -1, (-4/1.4) , 0  ,'y');
		draw_circle_object(0.4, 1, (-3/1.5) , 0.5  ,'y');
		draw_circle_object(0.4,  -1, (-2/1.4) , 0  ,'y');
		draw_circle_object(0.4,  1, (-1/1.5) , 0.5  ,'y');
		draw_circle_object(0.4,  -1 , (0/1.4) , 0  ,'y');
		draw_circle_object(0.4,  1, (1/1.5) , 0.5  ,'y');
		draw_circle_object(0.4,  -1, (2/1.4) , 0  ,'y');
		draw_circle_object(0.4,  -1, (3/1.5) , 0.5  ,'y');
		draw_circle_object(0.4,  1, (4/1.6) , -0.5  ,'y');
		draw_circle_object(0.4,  -1, (5/1.4) , 0  ,'y');
		draw_circle_object(0.4,  1, (6/1.5) , 0.5  ,'y');
		draw_circle_object(0.4,  -1, (7/1.6) , -0.5  ,'y');
		draw_circle_object(0.4,  1, (8/1.4) , 0  ,'y');
		draw_circle_object(0.4,  -1, (9/1.5) , 0.5  ,'y');
		draw_circle_object(0.4, -0.2 , (-10/1.4) , 0  ,'r');
		draw_circle_object(0.4, -0.3 , (-9/1.5) , 0  ,'g');
		draw_circle_object(0.4, -0.4 , (-8/1.6) , -0.5  ,'p');
		draw_circle_object(0.4, -0.3 , (-7/1.4) , 0  ,'b');
		draw_circle_object(0.4, -0.4, (-6/1.5) , 0.5  ,'r');
		draw_circle_object(0.4, -0.5, (-5/1.6) , -0.5  ,'g');
		draw_circle_object(0.4, -0.4, (-4/1.4) , 0  ,'p');
		draw_circle_object(0.4,  -0.3, (-3/1.5) , 0.5  ,'b');
		draw_circle_object(0.4,  -0.2, (-2/1.4) , 0  ,'r');
		draw_circle_object(0.4,  -0.1, (-1/1.5) , 0.5  ,'g');
		draw_circle_object(0.4,  0 , (0/1.4) , 0  ,'p');
		draw_circle_object(0.4,  0.1, (1/1.5) , 0.5  ,'b');
		draw_circle_object(0.4,  0.2, (2/1.4) , 0  ,'r');
		draw_circle_object(0.4,  0.1, (3/1.5) , 0.5  ,'g');
		draw_circle_object(0.4,  0.1, (4/1.6) , -0.5  ,'p');
		draw_circle_object(0.4,  0, (5/1.4) , 0  ,'b');
		draw_circle_object(0.4,  -0.1, (6/1.5) , 0.5  ,'r');
		draw_circle_object(0.4,  -0.2, (7/1.6) , -0.5  ,'g');
		draw_circle_object(0.4,  -0.3, (8/1.4) , 0  ,'p');
		draw_circle_object(0.4,  -0.2, (9/1.5) , -0.1  ,'r');
		draw_circle_object(0.4,  0 , (-10/1.4) , -0.6  ,'g');
		draw_circle_object(0.4, -0.3 , (-9/1.5) , 0.6  ,'p');
		draw_circle_object(0.4, -0.5 , (-8/1.6) , -0.5  ,'b');
		draw_circle_object(0.4, -0.4 , (-7/1.4) , 0  ,'r');
		draw_circle_object(0.4, -0.2, (-6/1.5) , 0.5  ,'g');
		draw_circle_object(0.4, -0.4, (-5/1.6) , -0.5  ,'p');
		draw_circle_object(0.4, -0.1, (-4/1.4) , 0  ,'b');
		draw_circle_object(0.4,  -0.6, (-3/1.5) , 0.5  ,'r');
		draw_circle_object(0.4,  0, (-2/1.4) , 0  ,'g');
		draw_circle_object(0.4,  0.1, (-1/1.5) , 0.5  ,'p');
		draw_circle_object(0.4,  0.5 , (0/1.4) , 0  ,'b');
		draw_circle_object(0.4,  0, (1/1.5) , 0.5  ,'r');
		draw_circle_object(0.4,  -0.6, (2/1.4) , 0  ,'g');
		draw_circle_object(0.4,  0.4, (3/1.5) , 0.5  ,'p');
		draw_circle_object(0.4,  0.2, (4/1.6) , -0.5  ,'b');
		draw_circle_object(0.4,  0.1, (5/1.4) , 0  ,'r');
		draw_circle_object(0.4,  -0.6, (6/1.5) , 0.5  ,'g');
		draw_circle_object(0.4,  0.3, (7/1.6) , -0.5  ,'p');
		draw_circle_object(0.4,  -0.4, (8/1.4) , 0  ,'b');
		draw_circle_object(0.4,  0.4, (9/1.5) , 0.5  ,'r');
		draw_circle_object(0.4,  0 , (-10/1.4) , 0.7  ,'g');
		draw_circle_object(0.4, -0.5 , (-9/1.5) , -0.5  ,'p');
		draw_circle_object(0.4, 0.2 , (-8/1.6) , -0.5  ,'b');
		draw_circle_object(0.4, 0.1 , (-7/1.4) , 0.9  ,'r');
		draw_circle_object(0.4, 0.1, (-6/1.5) , 0.7  ,'g');
		draw_circle_object(0.4, 0.3, (-5/1.6) , -0.6  ,'p');
		draw_circle_object(0.4, 0.2, (-4/1.4) , 0.7  ,'b');
		draw_circle_object(0.4, -0.3, (-3/1.5) , 0.7  ,'r');
		draw_circle_object(0.4,  0, (-2/1.4) , 0.8  ,'g');
		draw_circle_object(0.4,  0.1, (-1/1.5) , 0.7  ,'p');
		draw_circle_object(0.4,  -0.2 , (0/1.4) , 0.5  ,'b');
		draw_circle_object(0.4,  0.2, (1/1.5) , 0.7  ,'r');
		draw_circle_object(0.4,  0.1, (2/1.4) , 0.4  ,'g');
		draw_circle_object(0.4,  -0.2, (3/1.5) , 0.7  ,'p');
		draw_circle_object(0.4,  -0.2, (4/1.6) , -0.3  ,'b');
		draw_circle_object(0.4,  -0.3, (5/1.4) , 0.5  ,'r');
		draw_circle_object(0.4,  0.1, (6/1.5) , 0.7  ,'g');
		draw_circle_object(0.4,  -0.3, (7/1.6) , -0.4  ,'p');
		draw_circle_object(0.4,  0.4, (8/1.4) , 0.5  ,'b');
		draw_circle_object(0.4,  0, (9/1.5) , 0.7  ,'r');
		draw_circle_object(0.4,  0.4 , (-10/1.5) , 0.7  ,'g');
		draw_circle_object(0.4,  0.4 , (-10/1.7) , 0.4  ,'p');
		draw_circle_object(0.4,  0.4 , (-10/1.5) , 0.1  ,'b');
		draw_circle_object(0.4,  0.1 , (-10/1.5) , 0.3  ,'r');
		draw_circle_object(0.4,  -0.4 , (-10/1.5) , 0  ,'g');
		draw_circle_object(0.4,  0.2 , (-10/1.5) , -0.2  ,'p');
		draw_circle_object(0.4,  0 , (-10/1.5) , -0.1  ,'b');
		draw_circle_object(0.4,  0.2 , (-10/1.5) , 0.1  ,'r');
		draw_circle_object(0.4, -0.1 , (-9/1.5) , -0.5  ,'g');
		draw_circle_object(0.4, 0.3 , (-8/1.5) , -0.5  ,'p');
		draw_circle_object(0.4, 0.3 , (-7/1.5) , 0.9  ,'b');
		draw_circle_object(0.4, 0.1, (-6/1.5) , 0.7  ,'r');
		draw_circle_object(0.4, 0.5, (-5/1.5) , -0.6  ,'g');
		draw_circle_object(0.4, 0.6, (-4/1.5) , 0.7  ,'p');
		draw_circle_object(0.4, -0.4, (-3/1.5) , 0.7  ,'b');
		draw_circle_object(0.4,  0.4, (-2/1.5) , 0.8  ,'r');
		draw_circle_object(0.4,  0.5, (-1/1.5) , 0.7  ,'g');
		draw_circle_object(0.4,  0 , (0/1.5) , 0.5  ,'p');
		draw_circle_object(0.4,  0, (1/1.5) , 0.7  ,'b');
		draw_circle_object(0.4,  0, (2/1.5) , 0.4  ,'r');
		draw_circle_object(0.4,  0.2, (3/1.5) , 0.7  ,'g');
		draw_circle_object(0.4,  0.2, (4/1.5) , -0.3  ,'p');
		draw_circle_object(0.4,  0.3, (5/1.5) , 0.5  ,'b');
		draw_circle_object(0.4,  -0.1, (6/1.5) , 0.7  ,'r');
		draw_circle_object(0.4,  0.3, (7/1.5) , -0.4  ,'g');
		draw_circle_object(0.4,  -0.4, (8/1.5) , 0.5  ,'p');
		draw_circle_object(0.4,  -0.3, (9/1.5) , 0.7  ,'r');
		draw_circle_object(0.4,  -0.3, (-10/1.5) , 0.7  ,'g');
		draw_circle_object(0.4,  -0.3, (-10/1.5) , 0.5  ,'p');
		draw_circle_object(0.4,  -0.3, (-10/1.5) , -0.7  ,'r');
		draw_circle_object(0.4,  -0.3, (-8/1.5) , 0.5  ,'g');
		draw_circle_object(0.4,  -0.3, (-8/1.5) , -0.7  ,'p');
		draw_circle_object(0.4,  -0.3, (-7/1.5) , 0.2  ,'b');
		draw_circle_object(0.4,  -0.3, (-8/1.5) , -0.4  ,'r');
		draw_circle_object(0.4,  -0.3, (-8/1.5) , 0.1  ,'g');
		draw_circle_object(0.4,  -0.3, (-8/1.5) , -0.3  ,'p');
		draw_circle_object(0.4,  0.5, (-8/1.5) , 0.1  ,'b');
		draw_circle_object(0.4,  0.1, (-8/1.3) , -0.3  ,'r');
		draw_circle_object(0.4,  0.4, (-8/1.2) , 0.2  ,'g');
		draw_circle_object(0.4,  0.2, (-8/1.1) , -0.5  ,'p');
		draw_circle_object(0.4,  0.3, (-8/1.6) , 0.5  ,'b');
		draw_circle_object(0.4,  -0.5, (-2/1.9) , 0.1  ,'r');
		draw_circle_object(0.4,  0.2, (-3/1.7) , -0.3  ,'g');
		draw_circle_object(0.4,  0.4, (-5/1.8) , 0.2  ,'p');
		draw_circle_object(0.4,  -0.1, (-6/1.6) , -0.5  ,'b');
		draw_circle_object(0.4,  0.1, (-1/1.5) , 0.5  ,'r');
		draw_circle_object(0.4,  0, (-4/2) , 0.1  ,'g');
		draw_circle_object(0.4,  -0.3, (-6/2.2) , -0.3  ,'p');
		draw_circle_object(0.4,  -0.2, (-5/2) , 0  ,'b');
		draw_circle_object(0.4,  0.1, (-4/1.3) , -0.1  ,'r');
		draw_circle_object(0.4,  0.4, (-7/1.4) , -0.2  ,'g');
		draw_circle_object(0.4,  0.3, (-5/1.5) , 0.3  ,'p');
		draw_circle_object(0.4,  -0.1, (-6/1.7) , -0.3  ,'b');
		draw_circle_object(0.4,  -0.4, (-2/1.2) , 0.1  ,'r');
		draw_circle_object(0.4,  -0.2, (-4/1.3) , -0.2  ,'g');
		draw_circle_object(0.4,  -0.3, (-5/1.6) , -0.5  ,'p');
		draw_circle_object(0.4,  -0.5, (-6/1.6) , -0.2  ,'b');
		draw_circle_object(0.4,  0.3, (-6/1.6) , 0.3  ,'r');
		draw_circle_object(0.4,  -0.3, (-6/1.6) , -0.5  ,'g');
		draw_circle_object(0.4,  -0.5, (-7/1.6) , -0.2  ,'p');
		draw_circle_object(0.4,  0.3, (-7/1.6) , 0.3  ,'b');
		draw_circle_object(0.4,  -0.3, (-7/1.6) , -0.5  ,'r');
		draw_circle_object(0.4,  -0.5, (-8/1.6) , -0.2  ,'g');
		draw_circle_object(0.4,  0.3, (-8/1.6) , 0.3  ,'p');
		draw_circle_object(0.4,  -0.3, (-8/1.6) , -0.5  ,'b');
		draw_circle_object(0.4,  -0.5, (-4/1.6) , -0.2  ,'r');
		draw_circle_object(0.4,  0.3, (-4/1.6) , 0.3  ,'g');
		draw_circle_object(0.4,  -0.3, (-4/1.6) , -0.5  ,'p');
		draw_circle_object(0.4,  -0.5, (-4/1.6) , -0.2  ,'b');
		draw_circle_object(0.4,  0.3, (-4/1.6) , 0.3  ,'r');
		draw_circle_object(0.4,  -0.3, (-4/1.6) , -0.5  ,'g');
		draw_circle_object(0.4,  -0.5, (-5/1.6) , -0.2  ,'p');
		draw_circle_object(0.4,  0.3, (-5/1.6) , 0.3  ,'b');
		draw_circle_object(0.4,  -0.3, (-5/1.6) , -0.5  ,'r');
		for(int i = -3 ; i < 10 ; i++){
			draw_circle_object(0.4,  -0.5, (-i/1.6) , -0.2  ,'r');
			draw_circle_object(0.4,  0.3, (-i/1.4) , 0.3  ,'g');
			draw_circle_object(0.4,  -0.3, (-i/1.5) , -0.5  ,'p');
		}
		draw_circle_object(0.4,  -0.3, (5/1.6) , 0  ,'r');
		draw_circle_object(0.4,  0.1, (5/1.6) , 0.1  ,'g');
		draw_circle_object(0.4,  0, (5/1.6) , -0.2  ,'p');
		draw_circle_object(0.4,  -0.5, (4/1.6) , -0.2  ,'b');
		draw_circle_object(0.4,  0.3, (4/1.6) , 0.3  ,'r');
		draw_circle_object(0.4,  -0.3, (4/1.6) , -0.5  ,'g');
		draw_circle_object(0.4,  -0.5, (8/1.6) , -0.2  ,'p');
		draw_circle_object(0.4,  0.3, (8/1.6) , 0.3  ,'b');
		draw_circle_object(0.4,  -0.3, (8/1.6) , -0.5  ,'r');
		draw_circle_object(0.4,  -0.2, (8/1.4) , -0.2  ,'g');
		draw_circle_object(0.4,  0.4, (8/1.2) , 0.3  ,'p');
		draw_circle_object(0.4,  -0.5, (8/1.5) , -0.5  ,'b');
		draw_circle_object(0.4,  -0.5, (8/1.5) , -0.3  ,'r');
		draw_circle_object(0.4,  0.3, (8/1.6) , 0.4  ,'g');
		draw_circle_object(0.4,  -0.3, (8/1.4) , 0  ,'p');
		draw_circle_object(0.4,  -0.5, (8/1.4) , -0.1  ,'b');
		draw_circle_object(0.4,  0.3, (8/1.3) , 0.5  ,'r');
		draw_circle_object(0.4,  -0.3, (8/1.5) , -0.4  ,'g');
		draw_circle_object(0.4,  -0.5, (8/1.7) , 0.3  ,'p');
		draw_circle_object(0.4,  0.3, (8/1.6) , -0.3  ,'b');
		draw_circle_object(0.4,  -0.3, (8/1.4) , 0  ,'r');
		draw_circle_object(0.4,  -0.5, (6/1.9) , -0.2  ,'g');
		draw_circle_object(0.4,  0.3, (6/1.8) , 0.3  ,'p');
		draw_circle_object(0.4,  -0.3, (6/1.7) , -0.5  ,'r');
		draw_circle_object(0.4,  -0.2, (6/1.9) , 0.2  ,'g');
		draw_circle_object(0.4,  0.4, (6/1.8) , 0.1  ,'p');
		draw_circle_object(0.4,  0.2, (6/1.7) , -0.3  ,'b');
		draw_circle_object(0,  0.2, (6/1.7) , -0.3  ,'w');
	}
}

void renderBitmapString(float x, float y, float z, void *font, char *string) {  
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glColor3f(0.0,1.0,1.0);
		glutBitmapCharacter(font, *c);
	}
}

void drawScene() {      	
	// Draw the sphere
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutFullScreen();
	initLight(20);  	// Setting Light Environment
	int mode=0;   
    if(primitive == 1){
       glutPostRedisplay();
    }
    else if(primitive == 2){
       mode=0;
    }
    else if(primitive == 3){
       mode=1;
    }
    else if(primitive == 5) {
       exit(0);
    }
    //Show Menu 
    //renderBitmapString(-11, -7, 0, GLUT_BITMAP_8_BY_13, menu1);
    renderBitmapString(-11, -8, 0, GLUT_BITMAP_8_BY_13, menu2);
    renderBitmapString(-11, -9, 0, GLUT_BITMAP_8_BY_13, menu3);
    renderBitmapString(-11, -10, 0, GLUT_BITMAP_8_BY_13, menu4);
    renderBitmapString(-11, -11, 0, GLUT_BITMAP_8_BY_13, menu5);
    //Show Text	
    renderBitmapString(14, 5, 0, GLUT_BITMAP_HELVETICA_18, text1);   
	renderBitmapString(9, 3, 0, GLUT_BITMAP_8_BY_13, text2); 
    renderBitmapString(9, 2, 0, GLUT_BITMAP_8_BY_13, text3); 
    renderBitmapString(9, 1, 0, GLUT_BITMAP_8_BY_13, text4); 
	renderBitmapString(9, 0, 0, GLUT_BITMAP_8_BY_13, text5); 
	renderBitmapString(9, -1, 0, GLUT_BITMAP_8_BY_13, text6);
    renderBitmapString(18, -11, 0, GLUT_BITMAP_9_BY_15, text0);
    // All Scene Rotate 
    glRotatef(r,0.0,1.0,0.0);
    glRotatef(t,1.0,0.0,0.0);
    //All Scene Scale        
    glPushMatrix();
    glScalef(z,z,z);   
	drawModel(mode);
    glPopMatrix();
	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
	d += 0.1; r+=0.5;
	if (r > 360)
		r -= 360;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);	
	glutCreateWindow("DNA Structure");	
	createMenu();
	initRendering();	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);	
	glutMainLoop();
	return 0;
}
