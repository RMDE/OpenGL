/*****************************************************************************
FILE : submit.c (Assignment 1)
NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
Student Information
Student ID:********
Student Name:******
*****************************************************************************/

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

const GLdouble FRUSTDIM = 100.0f;
int i;

/* Initialize material properties */
GLfloat mat_ambient[] = { 0.931250, 0.231250, 0.231250, 1 };
GLfloat mat_diffuse[] = { 0.277500, 0.277500, 0.277500, 1 };
GLfloat mat_specular[] = { 0.773911, 0.773911, 0.773911, 1 };
GLfloat mat_shininess[] = { 89.599998 };




/* lighting mat */

//light 0
GLfloat light0_pos[] = { 0.0f, 0.f, 0.f, 1.0f };
GLfloat light0_amb[] = { 0.6, 0.6, 0.6, 1.0f };
GLfloat light0_diff[] = { 0.5, 0.5, 0.5, 0.3 };

//light1
GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_speculer[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_position[] = { 99.9, 70, -90, 1.0 };
GLfloat spot_direction[] = { 1.0, 0, 0 };


/* animation */
GLUquadricObj *obj;

/* 镜头漫游*/
struct Eyepoint
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Eye;


/* 窗口 */
GLint WinWidth, WinHeight;

/* 动画参数 */
GLfloat
FanAngle = 0,
TeapotPos = -96,
PostPos = -100,
HolePos = -100,
StoolPos = 50,
Sphereangle = 0,
SphereScale = 6;

bool Teapot_dire = true, Stool_dir = true;

enum {light_on, light_off} Light;

enum {teapotstop, teapot_translate} Teapot;

enum {postempty,post_up, post_down} Post;

enum {stoolstop, stoolmove} Stool;

enum { sphere_stop, sphere_rotate } Sphere;

enum {sphere_large, sphere_small} Sphere1;

enum {fan_turnoff, fan_turnon} Fan;

enum{ closehole, openhole } Hole;

void init(void) // All Setup For OpenGL Goes Here
{

	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
	//启用灯源
	glEnable(GL_LIGHTING);
	//启用0号光源(0-7)，光源要求用glLight函数完成
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_speculer);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0);

	glEnable(GL_LIGHT1);

	//深度测试，根据坐标远近自动隐藏遮住图形
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GLUT_MULTISAMPLE);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	Eye.x = 0.0f;
	Eye.y = -30.0f;
	Eye.z = 10.0f;

	obj = gluNewQuadric();
}


void DrawWalls()
{
	/*  room space
		x:100 ~ -100
		y:100 ~ -100
		z:0 ~ -200
	*/

	glPushMatrix();

	//back wall 
	glBegin(GL_QUADS);
	glColor3ub(105, 105, 105);
	glVertex3f(-100, -100, -200);
	glVertex3f(100, -100, -200);
	glColor3ub(207, 207, 207);
	glVertex3f(100, 100, -200);
	glVertex3f(-100, 100, -200);
	glEnd();
	//ceiling
	glBegin(GL_QUADS);
	glColor3ub(169, 169, 169);
	glVertex3f(100, 100, -200);
	glVertex3f(-100, 100, -200);
	glVertex3f(-100, 100, 0);
	glVertex3f(100, 100, 0);
	glEnd();
	//left wall
	glColor3ub(79, 79, 79);
	glBegin(GL_QUADS);
	glVertex3f(-100, 100, -200);
	glVertex3f(-100, 100, 0);
	glVertex3f(-100, -100, 0);
	glVertex3f(-100, -100, -200);
	glEnd();
	//right wall
	glBegin(GL_QUADS);
	glVertex3f(100, 100, -200);
	glVertex3f(100, 100, 0);
	glVertex3f(100, -100, 0);
	glVertex3f(100, -100, -200);
	glEnd();
	//floor
	glColor3ub(139, 115, 85);
	glBegin(GL_QUADS);
	glVertex3f(100, -100, -200);
	glVertex3f(-100, -100, -200);
	glVertex3f(-100, -100, 0);
	glVertex3f(100, -100, 0);
	glEnd();

	glPopMatrix();
}

void Drawbed()
{
	glPushMatrix();

	//床身
	glColor3ub(169, 169, 169);
	glTranslatef(-75, -65, -100);
	glScalef(50, 5, 80);
	glutSolidCube(1);
	glPopMatrix();
	
	//床架
	glPushMatrix();
	glTranslatef(-55, -84, -100);
	glScalef(5, 33, 80);
	glutSolidCube(1);
	glPopMatrix();

	//被子
	glPushMatrix();
	glColor3ub(232, 232, 232);
	glTranslatef(-75, -61, -89);
	glScalef(50, 2, 59);
	glutSolidCube(1);
	glPopMatrix();

	//枕头
	glPushMatrix();
	glColor3ub(238, 232, 170);
	glTranslatef(-75, -61, -130);
	glScalef(30, 4, 10);
	glutSolidCube(1);
	glPopMatrix();

}

void DrawStool()
{
	glPushMatrix();

	glColor3ub(238, 197, 145);
	glTranslatef(StoolPos, -99, -100);

	//凳子腿
	glPushMatrix();
	glTranslatef(-5, 0, -5);
	glRotatef(-90, 1, 0, 0);	
	gluCylinder(obj, 1, 1, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, -5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 1, 1, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0, 5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 1, 1, 13, 31, 31);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, 5);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 1, 1, 13, 31, 31);
	glPopMatrix();


	//凳子面
	glPushMatrix();
	glTranslatef(0, 10, 0);
	glRotatef(-90, 1, 0, 0);
	glColor3ub(205, 170, 125);
	gluCylinder(obj, 8.5, 8.5, 3, 30, 30);
	glPopMatrix();

	glTranslated(0, 13, 0);
	glRotatef(-90, 1, 0, 0);
	gluDisk(obj, 0, 8.6, 20, 20);

	glPopMatrix();
}

void Drawtable()
{
	glPushMatrix();
	
	//木板
	glColor3ub(139, 115, 85);
	glTranslatef(90, -60, -100);
	glScalef(20, 1, 50);
	glutSolidCube(1);
	glPopMatrix();

	//铁链
	glPushMatrix();
	glColor3ub(0, 0, 0);
	glTranslatef(85, -60, -78);
	gluPartialDisk(obj, 2, 3.5, 32, 32, -90, 180);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, -60, -78);
	for (i = 1; i <= 7; i++)
	{
		glTranslatef(2, 2, 0);
		gluDisk(obj, 1, 1.5, 32, 32);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(85, -60, -78);
	glTranslatef(0, 0, -45);
	gluPartialDisk(obj, 2, 3.5, 32, 32, -90, 180);
	
	for (i = 1; i <= 7; i++)
	{
		glTranslatef(2, 2, 0);
		gluDisk(obj, 1, 1.5, 32, 32);
	}	
	glPopMatrix();

	//石柜
	glPushMatrix();
	glColor3ub(139, 139, 122);
	glTranslatef(-90, 50, -100);
	glScalef(20, 1, 60);
	glutSolidCube(1);

	glTranslatef(0, -30, 0);
	glutSolidCube(1);

	glPopMatrix();

}

void DrawCabinet()
{
	glPushMatrix();

	//柜子
	glColor3ub(139, 115, 85);
	glTranslatef(-80, -50, -170);
	glScalef(35, 100, 40);
	glutSolidCube(1);
	glLineWidth(3);
	glColor3ub(139, 126, 102);
	//柜边
	glutWireCube(1.0005);
	glPopMatrix();

	//把手
	glPushMatrix();
	glColor3ub(139, 87, 66);
	glTranslatef(-62, -50, -160);
	glScalef(1, 10, 1);
	glutSolidCube(1);
	glTranslatef(0, 0, -20);
	glutSolidCube(1);

	glPopMatrix();
}

void DrawTeapot()
{
	glPushMatrix();

	//茶壶
	glColor3ub(139, 69, 19);
	glTranslatef(88, -55, TeapotPos);
	glutSolidTeapot(7);
	glPopMatrix();

	//球
	glPushMatrix();
	glColor3ub(28, 28, 28);
	glTranslatef(30, -95, -100);
	glRotatef(Sphereangle, 0, 1, 0);
	glTranslatef(40, 0, 0);
	gluSphere(obj, SphereScale, 32, 32);

	glPopMatrix();
}

void DrawPost()
{
	glPushMatrix();

	glTranslatef(-100, 80, -195);
	glRotatef(90, 0, 1, 0);
	gluCylinder(obj, 1.5, 1.5, 200, 30, 30);
	glPopMatrix();

	//海报
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-60, 80, -195);
	glVertex3f(100, 80, -195);
	glVertex3f(100, PostPos, -195);
	glVertex3f(-60, PostPos, -195);
	glEnd();

	//洞
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(70, HolePos, -199.9);
	glVertex3f(95, HolePos, -199.9);
	glVertex3f(95, -100, -199.9);
	glVertex3f(70, -100, -199.9);
	glEnd();

	glPopMatrix();

}

void DrawWindow()
{
	glPushMatrix();

	//窗户
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(99.9, 60, -110);
	glVertex3f(99.9, 60, -80);
	glVertex3f(99.9, 40, -80);
	glVertex3f(99.9, 40, -110);
	glEnd();

	//栏杆
	glLineWidth(5);
	glColor3f(0.0f, 0.0f, 0.0f);

	for ( i = 0; i <= 6; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(99.9f, 60, -110+i*5);
		glVertex3f(99.9f, 40, -110+i*5);
		glEnd();
	}

	glPopMatrix();

	glPushMatrix();
	for ( i = 0; i < 29; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(-100 + i * 7, 100, 0);
		glVertex3f(-100 + i * 7, -100, 0);
		glEnd();
	}
	glPopMatrix();
	glLineWidth(1);

}

void DrawFan()
{
	glPushMatrix();

	glTranslatef(0, 75, -100);
	glRotatef(FanAngle, 0, 1, 0);

	//风扇支架
	glPushMatrix();
	glColor3ub(255, 228, 225);
	glTranslatef(0, 10, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(obj, 2, 2, 15, 30, 30);
	glPopMatrix();

	//风扇圆
	glPushMatrix();
	glTranslatef(0, 7, 0);
	glRotatef(-90, 1, 0, 0);
	glColor3ub(139, 139, 131);
	gluCylinder(obj, 6, 6, 3, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 7, 0);
	glRotatef(-90, 1, 0, 0);
	glColor3ub(240, 255, 240);
	gluDisk(obj, 0, 6, 30, 30);

	glTranslatef(0, 0, 3);
	glColor3ub(205, 205, 193);
	gluDisk(obj, 0, 6, 30, 30);
	glPopMatrix();

	//扇叶
	glPushMatrix();
	glColor3ub(240, 255, 255);
	glTranslatef(0, 8, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(40, 0, -5);
	glVertex3f(40, 0, 5);

	glVertex3f(0, 0, 0);
	glVertex3f(-40, 0, -5);
	glVertex3f(-40, 0, 5);

	glVertex3f(0, 0, 0);
	glVertex3f(-5, 0, -40);
	glVertex3f(5, 0, -40);

	glVertex3f(0, 0, 0);
	glVertex3f(-5, 0, 40);
	glVertex3f(5, 0, 40);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}


void display(void) // Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*--------------------------------------*/

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	DrawWalls();

	Drawbed();

	DrawWindow();

	DrawStool();
	
	Drawtable();

	DrawPost();

	DrawTeapot();
	
	DrawCabinet();

	DrawFan();


	/*----------------------------------------*/
	glutSwapBuffers();
	glFlush();

}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	//以防除数为0
	if (h == 0) h = 1;

	WinWidth = w;
	WinHeight = h;

	//将视口大小变成窗口大小
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	//单位化投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 320., 800.);
    //上面这个不好用

	GLfloat faspect;
	faspect = (GLfloat)w / (GLfloat)h;

	gluPerspective(100.0, faspect, 0.1, 1000.0);
	gluLookAt(Eye.x, Eye.y, Eye.z,
		0.0, -30.0, 0.0,
		0.0, 1.0, 0.0);
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key)
	{
	case '\033'://press 'esc' to quit
		exit(0);
		break;

		// TODO:
		// Add keyboard control here

	case '1':	//放下海报
		Post = post_up;
		break;

	case '2':	//收起海报
		Post = post_down;
		break;

	case '3':	//风扇旋转/停下
		if (Fan == fan_turnoff)
		Fan = fan_turnon;
		else Fan = fan_turnoff;
		break;

	case '4':	//茶壶移动/停止
		if (Teapot == teapotstop)
		Teapot = teapot_translate;
		else Teapot = teapotstop;
		break;

	case '5':	//开/关灯
		if (Light == light_on)
		{
			Light = light_off;
			glDisable(GL_LIGHT0);
		}
		else
		{
			Light = light_on;
			glEnable(GL_LIGHT0);
		}
		break;

	case '6':	//凳子移动
		Stool = stoolmove;
		break;

	case '7':	//球体旋转
		if (Sphere == sphere_stop)
		{
			Sphere = sphere_rotate;
		}
		else Sphere = sphere_stop;
		break;

	case '8':
		if (Sphere1 == sphere_large)
		{
			Sphere1 = sphere_small;
		}
		else Sphere1 = sphere_large;
		break;
	case '9':	//洞口显示
		if (Hole == closehole)
		{
			Hole = openhole;
		}
		else Hole = closehole;
		break;


	default:break;

	}
}

void specialkey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Eye.x -= 2.0;
		break;

	case GLUT_KEY_RIGHT:
		Eye.x += 2.0;
		break;

	case GLUT_KEY_UP:
		Eye.y += 2.0;
		break;

	case GLUT_KEY_DOWN:
		Eye.y -= 2.0;
		break;

	case GLUT_KEY_PAGE_UP:
		Eye.z += 2.0;
		break;
	
	case GLUT_KEY_PAGE_DOWN:
		Eye.z -= 2.0;
		break;

	default:
		break;
	}

	reshape(WinWidth, WinHeight);
	glutPostRedisplay();
}


void idle()
{
	if (Post == post_up)
	{

		PostPos = PostPos + 0.05;
		if (PostPos >= 80)
		{
			PostPos = 80;
			Post = postempty;
		}
	}
	
	if (Post == post_down)
	{
		PostPos = PostPos - 0.05;
		if (PostPos <= -100)
		{
			PostPos = -100;
			Post = postempty;
		}
	}

	if (Fan == fan_turnon)
	{
		if (FanAngle <= -360)
		{
			FanAngle = 0;
		}
		FanAngle--;
	}

	if (Hole == openhole)
	{
		if (HolePos >= -60)
		{
			HolePos = -60;
			
		}
		HolePos += 2;
	}

	if (Hole == closehole)
	{
			HolePos = -100;
	}

	if (Teapot == teapot_translate)
	{
		if (Teapot_dire == true)
		{
			TeapotPos -= 0.1;
			if (TeapotPos < -110)
			{
				Teapot_dire = false;
			}
		}
		else
		{
			TeapotPos += 0.1;
			if (TeapotPos > -96)
			{
				Teapot_dire = true;
			}
		}
	}

	if (Stool == stoolmove)
	{
		if (Stool_dir)
		{
			StoolPos -= 1;
			if (StoolPos <= -40)
			{
				Stool = stoolstop;
				Stool_dir = false;
			}
		}
		else
		{
			StoolPos += 1;
			if (StoolPos >= 50)
			{
				Stool = stoolstop;
				Stool_dir = true;
			}

		}
	}

	if (Sphere == sphere_rotate)
	{
		if (Sphereangle >= 360)
			Sphereangle = 0;
		Sphereangle += 1;
	}

	if (Sphere1 == sphere_small)
	{
		SphereScale -= 0.1;
		if (SphereScale <= 2)
		{
			SphereScale = 2;
		}
	}
	else
	{
		SphereScale += 0.1;
		if (SphereScale >= 5)
		{
			SphereScale = 5;
		}
	}

	glutPostRedisplay();
}


void main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	//双缓冲+RGBA+深度模式
	glutInitDisplayMode(GLUT_RGBA | 
		GLUT_DOUBLE | GLUT_DEPTH | 
		GLUT_MULTISAMPLE);

	/*Create a window with title specified */
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("Assignment 1");

	init();	/*not GLUT call, initialize several parameters */

	/*Register different CALLBACK function for GLUT to response
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */

	//改变窗口大小时防止变形
	glutReshapeFunc(reshape);
	//显示ʾ
	glutDisplayFunc(display);
	//键盘按键
	glutKeyboardFunc(keyboard);
	//特殊按键
	glutSpecialFunc(specialkey);
	//空闲时渲染
	glutIdleFunc(idle);

	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

}