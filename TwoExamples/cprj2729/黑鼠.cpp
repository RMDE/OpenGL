/*****************************************************************************
        FILE : submit.c (Assignment 1)
        NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID:   
		Student Name: 
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init(void);
void display(void);
void reshape(int w,int h);
void keyboard(unsigned char key, int x, int y);
void idle(void);

void setLight0(bool flag);
void setLight1(bool flag);

/* Global Variables */
GLfloat light_pos0[] = {0, 25, -10, 1};
GLfloat light_dir0[]   = {0, -1, 0};
GLfloat light_cutoff0 = 45;
GLfloat light_amb0[] = {0.2, 0.2, 0.2, 1.0};
GLfloat light_dif0[] = {0.4, 0.4, 0.4, 1.0};
GLfloat light_spc0[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light_pos1[] = {10, 10, 10, 1};
GLfloat light_dir1[]   = {0, -1, -1};
GLfloat light_cutoff1 = 20;
GLfloat light_amb1[] = {0.1, 0.3, 0.1, 1.0};
GLfloat light_dif1[] = {0.1, 0.7, 0.1, 1.0};
GLfloat light_spc1[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light_pos2[] = {0, 10, -10, 1};
GLfloat light_dir2[]   = {0, -1, 0};
GLfloat light_cutoff2 = 50;
GLfloat light_amb2[] = {0.2, 0.15, 0, 1.0};
GLfloat light_dif2[] = {0.8, 0.75, 0, 1.0};
GLfloat light_spc2[] = {1.0, 1.0, 0, 1.0};

bool aRoomLight = true;

bool aAndroid = false;
int aAndroidAng = 0;
bool aAndroidLight = false;
bool aAndroidJumpUp = true;
float aAndroidJumpDis = 0;

bool aCeilingLight = false;

bool aMice = false;
bool aMiceEyeBigger = true;
float aMiceEyeScale = 1.0;
float aMiceTrans[] = {0,0,0};

void setLight0(bool flag)
{
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_cutoff0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc0);

	if(flag)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}

void setLight1(bool flag)
{
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light_cutoff1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_spc1);
	
	if(flag)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
}

void setLight2(bool flag)
{
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_dir2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, light_cutoff2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_amb2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_dif2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_spc2);
	
	if(flag)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);
}

void init(void) // All Setup For OpenGL Goes Here
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void display(void) // Here's Where We Do All The Drawing
{
	// TODO:
	// Place light source here
	setLight0(aRoomLight);
	setLight1(aAndroidLight);
	setLight2(aCeilingLight);

	// TODO:
	// Draw walls and objects here
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	GLfloat matBlack[] = {0, 0, 0, 1};
	GLfloat matWhite[] = {1, 1, 1, 1};
	GLfloat matPink[] = {1, 0.8, 0.2, 1};
	GLfloat matBrown[] = {1, 0.6, 0.3, 1};
	GLfloat matYellowGreen[] = {0.5, 1, 0.5, 1};
	GLfloat matRed[] = {1, 0, 0, 1};
	GLfloat matGreen[] = {0, 1, 0, 1};
	GLfloat matBlue[] = {0, 0, 1, 1};
	GLfloat matYellow[] = {1, 1, 0, 1};
	GLfloat matShininess[] = {50};

	//Room x:10 to -10; y:10 to -10; z:0 to -20
	glColor3f(1.0, 1.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWhite);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);					//back wall
	glVertex3f( 10, 10, -20);
	glVertex3f(-10, 10, -20);
	glVertex3f(-10,-10, -20);
	glVertex3f( 10,-10, -20);
	glEnd();
	
	glColor3f(1, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRed);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRed);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f( 10, 10, -20);
	glVertex3f( 10, 10,   0);
	glVertex3f(-10, 10,   0);
	glVertex3f(-10, 10, -20);
	glEnd();

	glColor3f(0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f(-10, 10, -20);
	glVertex3f(-10, 10,   0);
	glVertex3f(-10,-10,   0);
	glVertex3f(-10,-10, -20);
	glEnd();

	glColor3f(0, 0, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBlue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f(-10,-10, -20);
	glVertex3f(-10,-10,   0);
	glVertex3f( 10,-10,   0);
	glVertex3f( 10,-10, -20);
	glEnd();

	glColor3f(1, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glBegin(GL_QUADS);
	glVertex3f( 10,-10, -20);
	glVertex3f( 10,-10,   0);
	glVertex3f( 10, 10,   0);
	glVertex3f( 10, 10, -20);
	glEnd();
	
	//Bed on the conner
	glColor3f(1, 0.8, 0.2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	glPushMatrix();
	glTranslatef(-6, -6, -19.5);
	glScalef( 8, 8, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, -7, -11.5);
	glScalef( 8, 1, 16);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, -8.5, -4);
	glScalef( 8, 3, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();

	glColor3f(1, 0.8, 0.8);		//pink
	glMaterialfv(GL_FRONT, GL_AMBIENT, matPink);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPink);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	glTranslatef(-6, -6, -11.5);
	glScalef( 8, 2, 16);
	glutSolidCube(1);
	glPopMatrix();

	//Brown closet in the conner
	glColor3f(1, 0.6, 0.3);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	glPushMatrix();
	glTranslatef(6, 0, -18);
	glScalef( 8, 20, 4);
	glutSolidCube(1);
	glPopMatrix();
	
	//Brown desk
	glColor3f(1, 0.6, 0.3);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matBrown);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	glPushMatrix();
	glTranslatef(8, -4.5, -6);
	glScalef( 4, 1, 12);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(9.5, -7, -6);
	glScalef( 1, 6, 12);
	glutSolidCube(1);
	glPopMatrix();
	

	//Android
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);
	
	glPushMatrix();
	glColor3f(0.5, 1, 0.5);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellowGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellowGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glTranslatef(8, -2, -2);
	glTranslatef(0, aAndroidJumpDis, 0);		//Jump animation
	glRotatef(aAndroidAng, 0, 1, 0);	//Rotate animation
		glPushMatrix();
		glRotatef(90, 1, 0, 0);				//Body
		gluCylinder(quadratic, 1, 1, 1.5, 16, 16);
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 1, 0, 0);				//Hand
		glTranslatef(1.2, 0, 0.3);
		gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 1, 0, 0);				//Hand
		glTranslatef(-1.2, 0, 0.3);
		gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 1, 0, 0);				//Foot
		glTranslatef(0.5, 0, 1.5);
		gluCylinder(quadratic, 0.2, 0.2, 0.5, 16, 16);
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 1, 0, 0);				//Foot
		glTranslatef(-0.5, 0, 1.5);
		gluCylinder(quadratic, 0.2, 0.2, 0.5, 16, 16);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.7, 1.2, 0);			//Antenna
		glRotatef(90, 3, -1.5, 0);
		gluCylinder(quadratic, 0.1, 0.1, 0.5, 16, 16);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-0.7, 1.2, 0);			//Antenna
		glRotatef(90, 3, 1.5, 0);
		gluCylinder(quadratic, 0.1, 0.1, 0.5, 16, 16);
		glPopMatrix();
		glPushMatrix();
		glutSolidSphere(1,16,16);			//Head
		glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, -10, -19.99);
		glPushMatrix();				//Mice hole
		glColor3f(0, 0, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, matBlack);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matBlack);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matBlack);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
		glScalef(1, 1.5, 1);
		gluDisk(quadratic, 0, 1, 16, 5);
		glPopMatrix();
		glPushMatrix();				//Mice eye
		glColor3f(1, 1, 0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matYellow);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
		glTranslatef(0.5, 0.5, 0.01);
			glTranslatef(aMiceTrans[0],aMiceTrans[1],aMiceTrans[2]);
		glScalef(aMiceEyeScale, aMiceEyeScale, 1);
		gluDisk(quadratic, 0, 0.1, 8, 1);
		glPopMatrix();
		glPushMatrix();				//Mice eye
		glTranslatef(-0.5, 0.5, 0.01);
			glTranslatef(aMiceTrans[0],aMiceTrans[1],aMiceTrans[2]);
		glScalef(aMiceEyeScale, aMiceEyeScale, 1);
		gluDisk(quadratic, 0, 0.1, 8, 1);
		glPopMatrix();
		if(aMice){
			glPushMatrix();			//Mice Body
			glColor3f(0, 0, 0);
			glMaterialfv(GL_FRONT, GL_AMBIENT, matBlack);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, matBlack);
			glMaterialfv(GL_FRONT, GL_SPECULAR, matBlack);
			glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
			glTranslatef(0,0,-1);
			glTranslatef(aMiceTrans[0],aMiceTrans[1],aMiceTrans[2]);
			glScalef(1,1,1.7);
			glutSolidSphere(0.8,16,16);
			glPopMatrix();
		}
	glPopMatrix();
	
	glPushMatrix();					//Celling Light
	glColor3f(1, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	if(aCeilingLight) glMaterialfv(GL_FRONT, GL_EMISSION, matYellow);
	glTranslatef(0,9.5,-10);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(1,1,16,16);
	glPopMatrix();

	glPushMatrix();				//Teapot
	glColor3f(1,1,1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWhite);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWhite);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);
	glTranslatef(7.5, -3, -10);
	glRotatef(-135, 0, 1, 0);
	glutSolidTeapot(1.5);
	glPopMatrix();

	// TODO:
	// Add animation here
	
	glFlush();
	glutSwapBuffers();
	
}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65,(GLfloat)w/(GLfloat)h,1.0,100.0); 
	gluLookAt( 0.0, 0.0,15.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	   switch (key) 
	   {
	   case'\033'://press 'esc' to quit
		   exit(0);
		   break;

		   // TODO:
		   // Add keyboard control here
		/*case'a':
		   light_pos0[0] -= 1;
		   printf("Press key 'a'.\n");
		   break;
		case'w':
		   light_pos0[1] += 1;
		   printf("Press key 'w'.\n");
		   break;
		case's':
		   light_pos0[1] -= 1;
		   printf("Press key 's'.\n");
		   break;
		case'd':
		   light_pos0[0] += 1;
		   printf("Press key 'd'.\n");
		   break;
		case'q':
		   light_pos0[2] -= 1;
		   printf("Press key 'q'.\n");
		   break;
		case'z':
		   light_pos0[2] += 1;
		   printf("Press key 'z'.\n");
		   break;
		case'f':
		   light_dir0[0] -= 0.1f;
		   printf("Press key 'f'.\n");
		   break;
		case'h':
		   light_dir0[0] += 0.1f;
		   printf("Press key 'h'.\n");
		   break;
		case't':
		   light_dir0[1] += 0.1f;
		   printf("Press key 't'.\n");
		   break;
		case'g':
		   light_dir0[1] -= 0.1f;
		   printf("Press key 'g'.\n");
		   break;
		case'r':
		   light_dir0[2] -= 0.1f;
		   printf("Press key 'r'.\n");
		   break;
		case'v':
		   light_dir0[2] += 0.1f;
		   printf("Press key 'v'.\n");
		   break;
		case'y':
		   light_cutoff0 += 1.0f;
		   printf("Press key 'y'.\n");
		   break;
		case'n':
		   light_cutoff0 -= 1.0f;
		   printf("Press key 'n'.\n");
		   break;*/
		case'1':
			aRoomLight = !aRoomLight;
		   printf("Press key '1'.\n");
		   break;
		case'2':
			aCeilingLight = !aCeilingLight;
		   printf("Press key '2'.\n");
		   break;
		case'3':
			aAndroidLight = !aAndroidLight;
			if(!aAndroidLight) aAndroidJumpDis = 0;
		   printf("Press key '3'.\n");
		   break;
		case'4':
			aAndroid = !aAndroid;
			if(!aAndroid) aAndroidJumpDis = 0;
		   printf("Press key '4'.\n");
		   break;
		case'5':
			if(!aRoomLight && !aCeilingLight && !aAndroidLight)
				aMice = !aMice;
		   printf("Press key '5'.\n");
		   break;
	   }
		
	   if(aRoomLight  || aCeilingLight || aAndroidLight)
		   aMice = false;

		//printf("Pos:%f %f %f %f\n",light_pos0[0], light_pos0[1], light_pos0[2], light_pos0[3]);
		//printf("Dir:%f %f %f\n", light_dir0[0], light_dir0[1], light_dir0[2]);
		//printf("Cutoff:%f\n",light_cutoff0);

		//printf("Amb:%f %f %f\n",light_amb0[0],light_amb0[1],light_amb0[2]);
		//printf("Dif:%f %f %f\n",light_dif0[0],light_dif0[1],light_dif0[2]);
		//printf("Spc:%f %f %f\n\n",light_spc0[0],light_spc0[1],light_spc0[2]);
}

void idle(void)
{
	if(aAndroid){
		if(!aAndroidLight)
			aAndroidAng = ++aAndroidAng % 360;
		else{
			if(aAndroidJumpUp){
				aAndroidJumpDis += 0.1;
				if(aAndroidJumpDis >= 1) aAndroidJumpUp = false;
			}else{
				aAndroidJumpDis -= 0.1;
				if(aAndroidJumpDis <= 0) aAndroidJumpUp = true;
			}
		}
	}
	if(!aMice){
		if(aMiceEyeBigger){
			aMiceEyeScale += 0.2;
			if(aMiceEyeScale >= 3) aMiceEyeBigger = false;
		}else{
			aMiceEyeScale -= 0.2;
			if(aMiceEyeScale <= 0) aMiceEyeBigger = true;
		}
		aMiceTrans[0] = aMiceTrans[1] = aMiceTrans[2] = 0;
	}else{
		aMiceEyeScale = 1;
		aMiceTrans[2] += 0.5;
		if(aMiceTrans[2] < 10)
			aMiceTrans[0] += 0.2;
		else
			aMiceTrans[0] -= 0.2;
		if(aMiceTrans[2] > 25)
			aMiceTrans[0] = aMiceTrans[1] = aMiceTrans[2] = 0;
	}
	Sleep(10);
	glutPostRedisplay();
}

void main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	/*Create a window with title specified */
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 1");

	init();	/*not GLUT call, initialize several parameters */

	/*Register different CALLBACK function for GLUT to response 
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	
	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();
	
}