/*****************************************************************************
        FILE : submit.c (Assignment 1)
        NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information (非常重要)
		Student ID (学号):161720110
		Student Name(姓名):叶茜
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h> 
#include <GL/glut.h>
#include <math.h>
#define N 2500
const GLfloat PI=4.1415926f;
const GLdouble FRUSTDIM = 100.0f;
GLint option = 0, i = 0;
bool enableLight = 0;
GLfloat donut_x=17.f;
GLfloat donut_z=-70.f;
GLfloat bench_x1=220.f;
GLfloat bench_x2=220.f;
GLfloat bench_x3=220.f;
GLfloat sphere_angle=0;
GLfloat sphere_size=3;
GLint sphere_spin=0;
GLint on=0;


/* 窗口 */
GLint WinWidth, WinHeight;

/* animation */
GLUquadricObj *obj;

/* 镜头漫游*/
struct Eyepoint
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Eye;

//圆弧点
struct Cycle{
    GLfloat x;
	GLfloat y;
	GLfloat z;
};


//星星位置
GLfloat star_size[100]={0.f};
GLfloat star1_x[100]={0.f};
GLfloat star1_y[100]={0.f};
GLfloat star2_x[50]={0.f};
GLfloat star2_y[50]={0.f};

/* Initialize material properties */
GLfloat mat_ambient[] = { 0.931250, 0.231250, 0.231250, 1 };
GLfloat mat_diffuse[] = { 0.277500, 0.277500, 0.277500, 1 };
GLfloat mat_specular[] = {1.0,1.0,1.0, 1 };
GLfloat mat_shininess[] = { 50 };


//LIGHT0
GLfloat color0[]={1,1,1,1.0f};
GLfloat color1[]={1.0,0.55,0.65,1.f};
GLfloat color2[]={0.2,0.6,0.95,1.f};//光源颜色
//GLfloat position0[]={-100.f,-500.f,400.f,1.f};//光源位置
GLfloat position0[]={-100.f,0.f,400.f,1.f};//光源位置
GLfloat diff0[]={0.5,0.5,0.5,0.3};//漫射光成分
GLfloat speculer0[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat direction0[]={0.0,-1.0,0.f}; //光线向量
GLfloat exponent0[]={2.f}; //聚光程度
GLfloat cutoff0[]={15.f}; //光覆盖角度
GLfloat atten0[]={0.5f};
GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };  
GLfloat local_view[] = { 0.0 };

//LIGHT1
GLfloat color[]={0.1,0.1,0.1,1.f};//光源颜色
GLfloat diff[] = {0.3,0.3,0.3,1.f};
//GLfloat position[]={-2000.f,-75.f,-5400.f,1.f};//光源位置
GLfloat position[]={0.f,30.f,50.f,1.f};//光源位置
GLfloat speculer[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat spot_direction[] = {0,0.0,-1.0};


void Draw_Wall()
{
	glPushMatrix();
	//back wall
	glBegin(GL_QUADS);//绘制由四个顶点组成的方形
	glColor3ub(150,160,230);//设定颜色
	glVertex3f(-233,-175,-225);//指定顶点的值
	glVertex3f(233,-175,-225);
	glColor3ub(170,180,255);//距离地板越近颜色越深
	glVertex3f(233,175,-225);
	glVertex3f(-233,175,-225);
	glEnd();
	//ceiling
	glBegin(GL_QUADS);
	glColor3ub(255,225,170);
	glVertex3f(233.0,175,-225);
	glVertex3f(-233.0,175,-225);
	glVertex3f(-233.0,175,0);
	glVertex3f(233,175,0);
	glEnd();
	//left wall
	glColor3ub(150,160,220);
	glBegin(GL_QUADS);
	glVertex3f(-233,175,-225);
	glVertex3f(-233,175,0);
	glColor3ub(130,140,200);
	glVertex3f(-233,-175,0);
	glVertex3f(-233,-175,-225);
	glEnd();
	//right wall
	glColor3ub(150,160,220);
	glBegin(GL_QUADS);
	glVertex3f(233,175,-225);
	glVertex3f(233,175,0);
	glColor3ub(130,140,200);
	glVertex3f(233,-175,0);
	glVertex3f(233,-175,-225);
	glEnd();
	//floor
	glColor3ub(170,180.5,170);
	glBegin(GL_QUADS);
	glVertex3f(233,-175,-225);
	glVertex3f(-233,-175,-225);
	glVertex3f(-233,-175,0);
	glVertex3f(233,-175, 0);
	glEnd();

	glPopMatrix();
}

void Draw_Window()
{

	glPushMatrix();
	//弧形窗
	glColor3ub(0,0,0);
	GLfloat r=120;
	Cycle arc[N];
	GLfloat start_angle=24.7;
	GLfloat end_angle=112;
    GLfloat diff=end_angle-start_angle;
    for(i=0;i<N;i++)
	{
        arc[i].x=r*cos((start_angle+diff/N*i)/360.0*2*PI); 
		arc[i].y=r*sin((start_angle+diff/N*i)/360.0*2*PI);
		arc[i].z=-224.9f;
	}
	glBegin(GL_POLYGON);
    for(int i=0;i<N;i++)
        glVertex3f(arc[i].x, arc[i].y+25, arc[i].z);
    glEnd();

	//方形窗
	glColor3ub(0,0,0);
	glBegin(GL_QUADS);
	glVertex3f(-100,90,-224.9);
	glVertex3f(-100,-50,-224.9);
	glVertex3f(100,-50,-224.9);
	glVertex3f(100,90,-224.9);
	glEnd();

	//方形边框
	glLineWidth(6.0f);
	glColor3ub(190,150,150);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-100,90,-224.8);
	glVertex3f(-100,-50,-224.8);
	glVertex3f(100,-50,-224.8);
	glVertex3f(100,90,-224.8);
	glVertex3f(-100,90,-224.8);
	glEnd();

	//弧形边框
	glLineWidth(6.0f);
	glColor3ub(190,150,150);
	glBegin(GL_LINE_STRIP);
	for(i=0;i<N;i++)
		arc[i].z=-224.8f;
    for(i=0;i<N;i++)
        glVertex3f(arc[i].x, arc[i].y+25, arc[i].z);
    glEnd();

	//竖型边框
	glLineWidth(6.0f);
	glColor3ub(190,150,150);
	glBegin(GL_LINES);
    glVertex3f(0,90,-224.8);
	glVertex3f(0,-50,-224.8);
    glEnd();

	glPopMatrix();
}

void Draw_Star(int red,int green,int blue,GLfloat s=0.3)
{
	glPushMatrix();
	//方形窗内的星星
	int count=100;
	GLfloat x,y,z;
	GLfloat size;
	glEnable(GL_POINT_SMOOTH); //进行点平滑处理
	glHint(GL_POINT_SMOOTH,GL_NICEST);
	glColor3ub(red,green,blue);
	for(i=0;i<count;i++)
	{
		size=star_size[i]+s;
		glPointSize(size); //只能设在glbegin()之前才有效
		x=star1_x[i];
		y=star1_y[i];
		z=-224.7;
		glBegin(GL_POINTS);
		glVertex3f(x,y,z);
		glEnd();
	}
	//弧形窗内的星星
	GLfloat r=120;
	count=50;
    for(int i=0;i<count;i++)
	{
		size=star_size[i]+s;
		glPointSize(size);
		x=star2_x[i];
		y=star2_y[i];
		z=-224.7;
		if((x*x+(y-25)*(y-25))<r*r)
		{
			glBegin(GL_POINTS);
			glVertex3f(x,y,z);
			glEnd();
		}
	}
	glPopMatrix();
}

void Draw_Sofa()
{
	//沙发架
	glPushMatrix();
	glColor3ub(105,105,105);
	glTranslatef(-90,-150,-111);//平移变换
	glScalef(50,15,106);//缩放变换,相当于长方体的长宽高设置
	glutSolidCube(1);//长方体
	glPopMatrix();

	//沙发靠背
	glPushMatrix();
	glColor3ub(125,125,125);
	glTranslatef(-94,-132,-157.5);
	glScalef(57,25,8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(115,115,115);
	glTranslatef(-118.5,-132.5,-111);
	glScalef(8,50,106);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(125,125,125);
	glTranslatef(-94,-132,-61.7);
	glScalef(57,25,8);
	glutSolidCube(1);
	glPopMatrix();

	//沙发坐垫
	glPushMatrix();
	glColor3ub(160,160,80);
	glTranslatef(-90,-140,-111);
	glScalef(50,4,90);
	glutSolidCube(1);
	glPopMatrix();
	
}

void Draw_Desk()
{
	//桌面
	glPushMatrix();
	glColor3ub(50,50,80);
	glTranslatef(10.f, -140.f, -105.f);
	glRotatef(90, 1.f, 0.f, 0.f);
	glScalef(1,1.5,0.5);//将圆盘变为椭圆盘
	gluDisk(obj, 0.f, 35.f, 100.f, 100.f);//绘制圆盘
	glPopMatrix();

	//桌脚
	glPushMatrix();
	glColor3ub(200,200,200);
	glTranslatef(10.f, -150.f, -112.5f);
	glRotatef(90,1,0,0);
	gluCylinder(obj,4,10,10,32,32);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(200,200,200);
	glTranslatef(10.f, -140.f, -112.5f);
	glRotatef(90,1,0,0);
	gluCylinder(obj,10,4,10,32,32);
	glPopMatrix();

	//茶壶
	glPushMatrix();
	glColor3ub(139,69,19);
	glTranslatef(0,-135,-120);
	glutSolidTeapot(8);
	glPopMatrix();

	//茶杯
	glPushMatrix();
	glColor3ub(139,69,19);
	glTranslatef(10.f,-132.5f,-100.f);
	glRotatef(90,1,0,0);
	gluCylinder(obj,4,2.5,4,32,32);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(139,69,19);
	glTranslatef(10.f,-134.9f,-100.f);
	glRotatef(90, 1.f, 0.f, 0.f);
	glScalef(1,1,0.5);
	gluDisk(obj,0.f,3.f,10.f,10.f);//绘制茶杯底座
	glPopMatrix();

	//钥匙
	glPushMatrix();
	glColor3ub(255,215,0);
	glLineWidth(1.5);
	glBegin(GL_LINES);//钥匙杆
	glVertex3f(17,-134.9,-71);
	glVertex3f(17,-134.9,-77);
	glEnd();
	glLineWidth(2);
	glBegin(GL_LINES);//钥匙杠
	glVertex3f(17,-134.9,-76);
	glVertex3f(19,-134.9,-76);
	glEnd();
	glBegin(GL_LINES);//钥匙杠
	glVertex3f(17,-134.9,-74);
	glVertex3f(19,-134.9,-74);
	glEnd();
	glColor3ub(255,215,0);
	glTranslatef(17.f,-134.9f,-70.5f);//钥匙环
	glRotatef(90, 1.f, 0.f, 0.f);
	glScalef(1,1,0.01);
	gluDisk(obj,0.f,1.5f,10.f,10.f);
	glPopMatrix();

}

void Draw_Donut(GLfloat donut_x,GLfloat donut_z)
{
	//垫子
	glPushMatrix();
	glColor3ub(255,231,186);
	glBegin(GL_QUADS);
	glVertex3f(donut_x-8,-135,donut_z);
	glVertex3f(donut_x,-135,donut_z-8);
	glVertex3f(donut_x+8,-135,donut_z);
	glVertex3f(donut_x,-135,donut_z+8);
	glEnd();
	glPopMatrix();

	//甜甜圈
	glPushMatrix();
	glColor3ub(160,50,50);
	glTranslatef(donut_x,-134,donut_z);
	glRotatef(-90.f, 1.f, 0.f, 0.f);	
	glutSolidTorus(1.7,2.5,110.f,110.f); //绘制立体圆环
	glPopMatrix();
}

void Draw_Light(GLfloat color[])
{
	glPushMatrix();
	//电灯线
	glColor3ub(0,0,0);
	glLineWidth(1.5);
	glBegin(GL_LINES);
	glVertex3f(0,100,-80);
	glVertex3f(0,87,-80);
	glEnd();

	//电灯炳
	glColor3ub(0,0,0);
	glLineWidth(4.5);
	glBegin(GL_LINES);
	glVertex3f(0,87,-80);
	glVertex3f(0,84,-80);
	glEnd();
	glPopMatrix();

	//电灯罩顶
	glPushMatrix();
	glColor3ub(141,182,205);
	glTranslatef(0.f,75,-80);
	glRotatef(90, 1.f, 0.f, 0.f);
	glScalef(1,1,0.2);
	gluDisk(obj,0.f,19.9f,50.f,50.f);
	glPopMatrix();

	//电灯罩面
	glPushMatrix();
	glColor3ub(225,196,160);
	glTranslatef(0.f,75.f,-80);
	glRotatef(90,1,0,0);
	gluCylinder(obj,20,20,4,32,32);
	glPopMatrix();

	//电灯泡
	glPushMatrix();
	glColor4f(color[0]*1.1,color[1]*1.1,color[2]*1.1,0.5);
	glTranslatef(0.f,70.f,-80);
	glutSolidSphere(5,5,5);
	glPopMatrix();
}

void Draw_Show()
{
	glPushMatrix();
	glColor3f(0.9,0.9,0);	
	glLineWidth(1.5);
	glBegin(GL_LINE_LOOP);
	GLfloat R=12;
	GLfloat xA=R*cos(90*2*PI/360);   	
	GLfloat yA=R*sin(90*2*PI/360); 	
	GLfloat xB=R*cos(306*2*PI/360);	
	GLfloat yB=R*sin(306*2*PI/360); 	
	GLfloat xC=R*cos(162*2*PI/360);	
	GLfloat yC=R*sin(162*2*PI/360); 	
	GLfloat xD=R*cos(18*2*PI/360);	
	GLfloat yD=R*sin(18*2*PI/360); 	
	GLfloat xE=R*cos(234*2*PI/360);	
	GLfloat yE=R*sin(234*2*PI/360); 	
	glVertex3f(227,xA-80,yA-100);	
	glVertex3f(227,xB-80,yB-100);	
	glVertex3f(227,xC-80,yC-100);	
	glVertex3f(227,xD-80,yD-100);	
	glVertex3f(227,xE-80,yE-100);	
	glEnd();

	glPopMatrix();
}

void Draw_Television(GLint on)
{
	//外框上沿
	glPushMatrix();
	glColor3ub(50,50,50);
	glTranslatef(230,-58,-100);
	glScalef(6,4,63);
	glutSolidCube(1);
	glPopMatrix();
	//外框下沿
	glPushMatrix();
	glTranslatef(230,-102,-100);
	glScalef(6,8,63);
	glutSolidCube(1);
	glPopMatrix();
	//外框左沿
	glPushMatrix();
	glTranslatef(230,-80,-130);
	glScalef(6,43,3);
	glutSolidCube(1);
	glPopMatrix();
	//外框右沿
	glPushMatrix();
	glTranslatef(230,-80,-70);
	glScalef(6,43,3);
	glutSolidCube(1);
	glPopMatrix();

	//内屏
	glPushMatrix();
	glColor4f(0,0,0,0.7);
	glTranslatef(230,-80,-100);
	glScalef(5,43,57);
	glutSolidCube(1);
	glPopMatrix();

	//指示灯
	glPushMatrix();
	if(on==0)
		glColor3ub(255,0,0);
	else if(on==1)
		glColor3ub(0,255,0);
	glPointSize(2.5f);
	glBegin(GL_POINTS);
	glVertex3f(224,-102,-125);
	glEnd();
	glPopMatrix();

	if(on==1)
		Draw_Show(); 
}

void Draw_TVbench(GLfloat bench_x1,GLfloat bench_x2,GLfloat bench_x3)
{
	//柜顶
	glPushMatrix();
	glColor3ub(255,187,255);
	glTranslatef(220,-152,-110);
	glScalef(40,2,120);
	glutSolidCube(1);
	glPopMatrix();

	//抽屉1
	glPushMatrix();
	glColor3ub(139,71,137);
	glTranslatef(bench_x1,-165,-150);
	glScalef(40,25,40);
	glutSolidCube(1);
	glPopMatrix();
	//把手
	glPushMatrix();
	glColor3ub(0,0,0);
	glPointSize(2.5f);
	glBegin(GL_POINTS);
	glVertex3f(bench_x1-20.1,-165,-150);
	glEnd();
	glPopMatrix();

	//抽屉2
	glPushMatrix();
	glColor3ub(205,150,205);
	glTranslatef(bench_x2,-165,-110);
	glScalef(40,25,40);
	glutSolidCube(1);
	glPopMatrix();
	//把手
	glPushMatrix();
	glColor3ub(0,0,0);
	glPointSize(2.5f);
	glBegin(GL_POINTS);
	glVertex3f(bench_x2-20.1,-165,-110);
	glEnd();
	glPopMatrix();

	//抽屉3
	glPushMatrix();
	glColor3ub(122,55,139);
	glTranslatef(bench_x3,-165,-70);
	glScalef(40,25,40);
	glutSolidCube(1);
	glPopMatrix();
	//把手
	glPushMatrix();
	glColor3ub(0,0,0);
	glPointSize(2.5f);
	glBegin(GL_POINTS);
	glVertex3f(bench_x3-20.1,-165,-70);
	glEnd();
	glPopMatrix();
}

void Draw_Sphere()
{
	//运动轨道
	glPushMatrix();
	glColor3ub(93,71,139);
	glTranslatef(180,50,-220);
	gluCylinder(obj,4,4.5,4,60,60);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(93,71,139);
	glTranslatef(180,50,-220);
	gluCylinder(obj,15,15.5,4,60,60);
	glPopMatrix();

	//球
	glPushMatrix();
	glColor3ub(107,142,35);
	glTranslatef(180,50,-220);
	glRotatef(sphere_angle, 0, 0, 1);
	glTranslatef(10, 0, 0);
	gluSphere(obj,sphere_size,32,32);
	glPopMatrix();
}

void Draw_Shelf()
{
	glPushMatrix();
	glColor4f(0.1,0.2,0.2,0.6);
	glTranslatef(-220,0,-110);
	glScalef(40,2,120);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.1,0.2,0.2,0.6);
	glTranslatef(-220,-30,-110);
	glScalef(40,2,120);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.1,0.2,0.2,0.6);
	glTranslatef(-220,-60,-110);
	glScalef(40,2,120);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.1,0.2,0.2,0.6);
	glTranslatef(-220,-90,-110);
	glScalef(40,2,120);
	glutSolidCube(1);
	glPopMatrix();
}

void init(void) // All Setup For OpenGL Goes Here
{
	//LIGHT0
	glLightfv(GL_LIGHT0,GL_AMBIENT,color0);
	glLightfv(GL_LIGHT0,GL_POSITION,position0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,diff0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,direction0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,speculer0);
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, 180.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0);
	
	// glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT,exponent0);
	// glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF,cutoff0);
	// glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION,atten0);
	// glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,atten0);
	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);  
    // glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view); 

	//Light1
	glLightfv(GL_LIGHT1,GL_AMBIENT,color);
	glLightfv(GL_LIGHT1,GL_POSITION,position);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,diff);
	glLightfv(GL_LIGHT1,GL_SPECULAR,speculer);
	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, 180.0);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0);
 
	glEnable(GL_LIGHTING);//使用0号灯
	enableLight=1;
	glEnable(GL_LIGHT0);//开灯
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GLUT_MULTISAMPLE);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Eye.x = 0.0f;
	Eye.y = -30.f;
	Eye.z =55.f;

	for(i=0;i<100;i++)
	{
		star_size[i]=(rand()%10)/10;
		star1_x[i]=rand()%200-100;
		star1_y[i]=rand()%140-50;
	}
	for(i=0;i<50;i++)
	{
		star2_x[i]=rand()%200-100;
		star2_y[i]=rand()%60+90;
	}


	obj = gluNewQuadric();
}

void display(void) // Here's Where We Do All The Drawing
{
	//glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// TODO:
	Draw_Wall();
	Draw_Window();
	Draw_Star(255,255,255);
	Draw_Sofa();
	Draw_Desk();
	Draw_Donut(donut_x,donut_z);
	Draw_Light(color0);
	Draw_Television(on);
	Draw_TVbench(bench_x1,bench_x2,bench_x3);
	Draw_Sphere();
	Draw_Shelf();
	// TODO:
	// Add animation here

	
	glutSwapBuffers();
	glFlush();
	
}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	WinWidth = w;
	WinHeight = h;

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, (GLfloat)w / (GLfloat)h,100,500);
	//glMatrixMode(GL_MODELVIEW);
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
	    case'\033'://press 'esc' to quit
		   exit(0);
		   break;
		   // TODO:
		   // Add keyboard control here
		case 'w': //change the color of light to white
			glDisable(GL_LIGHT1);
			glLightfv(GL_LIGHT0,GL_AMBIENT,color0);
			glEnable(GL_LIGHT0);
			enableLight=1;
			Draw_Light(color0);
			printf("Press the key \'w\'\n");
			break;
		case 'r': //change the color of light to red
			glDisable(GL_LIGHT1);
			glLightfv(GL_LIGHT0,GL_AMBIENT,color1);
			glEnable(GL_LIGHT0);
			enableLight=1;
			Draw_Light(color1);
			printf("Press the key \'r\'\n");
			break;
		case 'b'://change the color of light to blue
			glDisable(GL_LIGHT1);
			glLightfv(GL_LIGHT0,GL_AMBIENT,color2);
			glEnable(GL_LIGHT0);
			enableLight=1;
			Draw_Light(color2);
			printf("Press the key \'b\'\n");
			break;
		case 'd': /*decrease light*/
			if (enableLight){
				for (i=0; i<=3 ; i++)
				{
					color0[i] -= 0.1;
					if(color0[i]<0)
						color0[i]=0;
					diff0[i] -= 0.1;
					if(diff0[i]<0)
						diff0[i]=0;
				}
				glLightfv(GL_LIGHT0, GL_AMBIENT, color0);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
				glEnable(GL_LIGHT0);
				printf("Press the key \'d\'\n");
			}
			break;

		case 'i': /*increase light*/
			if (enableLight){
				for (i=0; i<=3 ; i++)
				{
					color0[i] += 0.1;
					if(color0[i]>1)
						color0[i]=1;
					diff0[i] += 0.1;
					if(diff0[i]>1)
						diff0[i]=1;
				}
				glLightfv(GL_LIGHT0, GL_AMBIENT, color0);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
				glEnable(GL_LIGHT0);
				printf("Press the key \'i\'\n");
			}
			break;
		case 'f':
			if(enableLight){
				enableLight=0;
				glDisable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				Draw_Star(255,255,255,1.5);
				GLfloat color[]={80,80,80};
				Draw_Light(color);
				printf("Press the key \'f\'\n");
			}
			break;
		case 'o':
			if(!enableLight){
				enableLight=1;
				glEnable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				Draw_Light(color0);
				printf("Press the key \'o\'\n");
			}
			break;
		case 'm': //move the donut
			if(donut_x==17.f)
				option=1;
			else if(donut_x==3.f)
				option=2;
			printf("Press the key \'m\'\n");
			break;
		case 't': //turn on/off the TV
			if(on==0)
				on=1;
			else
				on=0;
			Draw_Television(on);
			printf("Press the key \'t\'\n");
			break;
		case '1': //move the TV bench's drawer1
			if(bench_x1==220.f)
				option=3;
			else if(bench_x1==190.f)
				option=4;
			printf("Press the key \'1\'\n");
			break;
		case '2': //move the TV bench's drawer2
			if(bench_x2==220.f)
				option=5;
			else if(bench_x2==190.f)
				option=6;
			printf("Press the key \'2\'\n");
			break;
		case '3': //move the TV bench's drawer3
			if(bench_x3==220.f)
				option=7;
			else if(bench_x3==190.f)
				option=8;
			printf("Press the key \'3\'\n");
			break;
		case 's': //spin / stop the sphere
			if(sphere_spin==0)
				sphere_spin=1;
			else
				sphere_spin=0;
			printf("Press the key \'s\'\n");
			break;
		case 'c': //change the size of the sphere
			if(sphere_size==3)
				sphere_size=5;
			else
				sphere_size=3;
			printf("Press the key \'c\'\n");
			break;
	   }
	   glutPostRedisplay();
}

void specialkey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Eye.x -= 1;
		break;

	case GLUT_KEY_RIGHT:
		Eye.x += 1;
		break;

	case GLUT_KEY_UP:
		Eye.y +=1;
		break;

	case GLUT_KEY_DOWN:
		Eye.y -=1;
		break;

	case GLUT_KEY_PAGE_UP:
		Eye.z +=1;
		break;
	
	case GLUT_KEY_PAGE_DOWN:
		Eye.z -=1;
		break;

	default:
		break;
	}
	reshape(WinWidth, WinHeight);
	glutPostRedisplay();
}

void idle()
{
	if(option==1)
	{
		if(donut_x==3.f);
		else
		{
			donut_x-=0.5;
			donut_z-=0.5;
		}
	}
	if(option==2)
	{
		if(donut_x==17.f);
		else
		{
			donut_x+=0.5;
			donut_z+=0.5;
		}
	}
	if(option==3)
	{
		if(bench_x1==190.f);
		else
			bench_x1-=0.5;
	}
	if(option==4)
	{
		if(bench_x1==220.f);
		else
			bench_x1+=0.5;
	}
	if(option==5)
	{
		if(bench_x2==190.f);
		else
			bench_x2-=0.5;
	}
	if(option==6)
	{
		if(bench_x2==220.f);
		else
			bench_x2+=0.5;
	}
	if(option==7)
	{
		if(bench_x3==190.f);
		else
			bench_x3-=0.5;
	}
	if(option==8)
	{
		if(bench_x3==220.f);
		else
			bench_x3+=0.5;
	}
	if(sphere_spin==1)
	{
		if(sphere_angle>=360)
			sphere_angle=0;
		sphere_angle+=1;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitDisplayMode(GLUT_RGBA | 
		GLUT_DOUBLE | GLUT_DEPTH | 
		GLUT_MULTISAMPLE);

	/*Create a window with title specified */
	glutInitWindowSize(800,600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Cat\'s House");
	init();	/*not GLUT call, initialize several parameters */

	/*Register different CALLBACK function for GLUT to response 
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);
	glutIdleFunc(idle);
	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();
	
}