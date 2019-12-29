//
//  main.cpp
//  HW2
//
//  Created by 劉品萱 on 2019/12/14.
//  Copyright © 2019 劉品萱. All rights reserved.
//

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <GL/glut.h>
#include <GL/glui.h>
#include <ctime>

int SelectActionNum;
int timer = 0;

#define TORSO_HEIGHT 3.5
#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_LEG_RADIUS  0.5
#define LOWER_LEG_RADIUS  0.5
#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 3.0
#define UPPER_LEG_RADIUS  0.5
#define TORSO_RADIUS 0.75
#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.5
#define HEAD_HEIGHT 1.5
#define HEAD_RADIUS 1.0
#define TShirt_RADIUS 1.2

GLfloat Squat = 0.0;

typedef float point[3];

static GLfloat theta[11] = {0.0, 0.0, 0.0, 20.0,-60.0, 20.0, -60.0, 180.0, 0.0, 180.0, 0.0};
GLfloat ActionTheta[11] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
GLfloat ActionPosi[24] = { 0.0,     //右手 軸肢 X 軸 ActionPosi[0]
                           0.0,     //右手 軸肢 Y 軸 ActionPosi[1]
                           0.0,     //右手 軸肢 Z 軸 ActionPosi[2]
                           0.0,     //右手 前肢 X 軸 ActionPosi[3]
                           0.0,     //右手 前肢 Y 軸 ActionPosi[4]
                           0.0,     //右手 前肢 Z 軸 ActionPosi[5]
                           180.0,   //左手 軸肢 X 軸 ActionPosi[6]
                           0.0,     //左手 軸肢 Y 軸 ActionPosi[7]
                           0.0,     //左手 軸肢 Z 軸 ActionPosi[8]
                           0.0,     //左手 前肢 X 軸 ActionPosi[9]
                           0.0,     //左手 前肢 Y 軸 ActionPosi[10]
                           0.0,     //左手 前肢 Z 軸 ActionPosi[11]
                           0.0,     //右腳 軸肢 X 軸 ActionPosi[12]
                           0.0,     //右腳 軸肢 Y 軸 ActionPosi[13]
                           0.0,     //右腳 軸肢 Z 軸 ActionPosi[14]
                           0.0,     //右腳 前肢 X 軸 ActionPosi[15]
                           0.0,     //右腳 前肢 Y 軸 ActionPosi[16]
                           0.0,     //右腳 前肢 Z 軸 ActionPosi[17]
                           0.0,     //左腳 軸肢 X 軸 ActionPosi[18]
                           0.0,     //左腳 軸肢 Y 軸 ActionPosi[19]
                           0.0,     //左腳 軸肢 Z 軸 ActionPosi[20]
                           0.0,     //左腳 前肢 X 軸 ActionPosi[21]
                           0.0,     //左腳 前肢 Y 軸 ActionPosi[22]
                           0.0      //左腳 前肢 Z 軸 ActionPosi[23]
                        };
static GLint angle = 2;

GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul, *quadratic;

double size=1.0;

void torso()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   glColor3f(0.996, 0.655, 0.478);
   gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);
   glColor3f(1.0, 1.0, 1.0);
   glTranslatef(0.0, 0.0,-0.5);
   gluCylinder(t, TShirt_RADIUS, TShirt_RADIUS, TORSO_HEIGHT, 10, 10);
   glPopMatrix();
}

void head()
{
   // 畫頭
   glPushMatrix();
	glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
	glColor3f(0.996, 0.655, 0.478);
	gluSphere(h, 1.3, 15, 15);
                                 /*void gluSphere( GLUquadricObj *qobj, // 繪圖對象
　　                                               GLdouble radius,     // 球體半徑
　　                                               GLint slices,        // Z軸方向片數，經度方向
　　                                               GLint stacks)        // Z軸方向片數，維度方向*/
	glPopMatrix();

	// 眼睛
	glPushMatrix();
	glTranslatef(0.5, 0.85 * HEAD_RADIUS, HEAD_RADIUS * 0.8);
	glColor3f(0.0, 0.0, 0.0);
   // 右眼
	gluSphere(h, 0.4, 20, 20);
	glTranslatef(-1.0, 0.0, 0.0);
   // 左眼
	gluSphere(h, 0.4, 20, 20);
	glPopMatrix();
   
   GLdouble CutUp[4] = { 0.0, -1.0, 0.0, 0.0 };
   glPushMatrix();
   glTranslatef(0.0, -0.3*HEAD_RADIUS+0.7, 0.5*HEAD_RADIUS+0.3);
   glColor3f(1.0, 0.0, 0.0);
   glClipPlane(GL_CLIP_PLANE0, CutUp);
   glEnable(GL_CLIP_PLANE0);
   gluSphere(h, 0.5, 20, 20);
   glDisable(GL_CLIP_PLANE0);
   glPopMatrix();


	// 帽子
	glPushMatrix();
	glTranslatef(0.0, 1.15 * HEAD_RADIUS, 0.0);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	glColor3f(0.396, 0.18, 0);
	gluCylinder(quadratic, 1.0f ,0.95f ,0.5f ,30.0f ,30.0f);

	glTranslatef(0.0, 0.0,0.5);
	glColor3f(0.396, 0.18, 0);
	gluCylinder(quadratic, 0.95f ,0.9f ,0.5f ,30.0f ,30.0f);

	glTranslatef(0.0, 0.0,0.5);
	glColor3f(0.396, 0.18, 0);
	gluCylinder(quadratic, 0.9f ,0.85f ,0.5f ,30.0f ,30.0f);

	glTranslatef(0.0, 0.0,0.2);
	glColor3f(0.396, 0.18, 0);
   gluSphere(quadratic,0.85f,10,10);
	gluCylinder(quadratic, 0.85f ,0.8f ,0.5f ,30.0f ,30.0f);

	glTranslatef(0.0, 0.0,-1);
	gluCylinder(quadratic, 1.5f ,1.5f ,0.3f ,30.0f ,30.0f);
   glTranslatef(0.0, 0.0, 0.1);
	gluCylinder(quadratic, 1.7f ,1.7f ,0.3f ,30.0f ,30.0f);
	glPopMatrix();
}

// 我視角的左手 軸肢
void left_upper_arm()
{
   glPushMatrix();
	glColor3f(1, 1, 1);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluSphere(lua, UPPER_ARM_RADIUS, 10, 10);
	gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
	glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);
	gluSphere(lua,UPPER_ARM_RADIUS,10,10);
	glPopMatrix();
}

// 我視角的左手 前肢
void left_lower_arm()
{
   glPushMatrix();
   glColor3f(0.996, 0.655, 0.478);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
   glTranslatef(0.0, 0.0, LOWER_ARM_HEIGHT);
   gluSphere(lla,LOWER_ARM_RADIUS,10,10);

   if(SelectActionNum == 2)
   {
      // 拳擊手套
      glColor3f(1, 0, 0);
      gluCylinder(rla, 0.6, 0.6, 0.7, 10, 10);
      glTranslatef(0.0, 0.0, 1);
      gluSphere(lua,0.8,10,10);
      glTranslatef(0.0, 0.0, -1.2);
      glColor3f(1, 1, 1);
      gluCylinder(rla, 0.6, 0.6, 0.2, 10, 10);
   }
   if(SelectActionNum == 3)
   {
      // 手舉啞鈴
      glRotatef(70.0, 0.0, 1.0, 0.0);
      glTranslatef(0.0, 0.0, -1.5);
      glColor3f(0.514, 0.514, 0.514);
      gluCylinder(lla, 0.23, 0.23, 3, 10, 10);
      glColor3f(0, 0, 0);
      gluCylinder(lla, 0.35, 0.35, 0.75, 10, 10);
      glTranslatef(0.0, 0.0, 2.5);
      glColor3f(0, 0, 0);
      gluCylinder(lua, 0.35, 0.35, 0.75, 10, 10);
   }
   glPopMatrix();
}

// 我的右手 軸肢
void right_upper_arm()
{
   glPushMatrix();
   glColor3f(1, 1, 1);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluSphere(lua, UPPER_ARM_RADIUS, 10, 10);
   gluCylinder(rua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
   glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);
	gluSphere(lua,UPPER_ARM_RADIUS,10,10);
   glPopMatrix();
}

// 我的右手 前肢
void right_lower_arm()
{
   glPushMatrix();
   glColor3f(0.996, 0.655, 0.478);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
   // 讓手前肢末看起來不會是空心
   glTranslatef(0.0, 0.0, LOWER_ARM_HEIGHT);
	gluSphere(rla,LOWER_ARM_RADIUS,10,10);
   if(SelectActionNum == 2)
   {
      // 拳擊手套
      glColor3f(1, 0, 0);
      gluCylinder(rla, 0.6, 0.6, 0.7, 10, 10);
      glTranslatef(0.0, 0.0, 1);
      gluSphere(lua,0.8,10,10);
      glTranslatef(0.0, 0.0, -1.2);
      glColor3f(1, 1, 1);
      gluCylinder(rla, 0.6, 0.6, 0.2, 10, 10);
   }
   if(SelectActionNum == 3)
   {
      // 手舉啞鈴
      glRotatef(70.0, 0.0, 1.0, 0.0);
      glTranslatef(0.0, 0.0, -1.5);
      glColor3f(0.514, 0.514, 0.514);
      gluCylinder(rla, 0.23, 0.23, 3, 10, 10);
      glColor3f(0, 0, 0);
      gluCylinder(rla, 0.35, 0.35, 0.75, 10, 10);
      glTranslatef(0.0, 0.0, 2.5);
      glColor3f(0, 0, 0);
      gluCylinder(rla, 0.35, 0.35, 0.75, 10, 10);
   }
   glPopMatrix();
}
// 我的左腳 軸肢
void left_upper_leg()
{
   glPushMatrix();
   glColor3f(0.157, 0.451, 0.71);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluSphere(rla,LOWER_LEG_RADIUS,10,10);
   gluCylinder(lul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
   glPopMatrix();
}
// 我的左腳 前肢
void left_lower_leg()
{
   glPushMatrix();
   glColor3f(0.157, 0.451, 0.71);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluSphere(rla,LOWER_LEG_RADIUS,10,10);
   gluCylinder(lll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
   glTranslatef(0.0, 0.0, LOWER_LEG_HEIGHT);
   glColor3f(0, 0, 0);
	gluSphere(rla,LOWER_LEG_RADIUS,10,10);
   glPopMatrix();
}
// 我的右腳 軸肢
void right_upper_leg()
{
   glPushMatrix();
   glColor3f(0.157, 0.451, 0.71);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluSphere(rla,LOWER_LEG_RADIUS,10,10);
   gluCylinder(rul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
   glPopMatrix();
}
// 我的右腳 前肢
void right_lower_leg()
{
   glPushMatrix();
   glColor3f(0.157, 0.451, 0.71);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluSphere(rla,LOWER_LEG_RADIUS,10,10);
   gluCylinder(rll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
   glTranslatef(0.0, 0.0, LOWER_LEG_HEIGHT);
   glColor3f(0, 0, 0);
	gluSphere(rla,LOWER_LEG_RADIUS,10,10);
   glPopMatrix();
}

void ActionChange(int value)
{
   if(SelectActionNum == 1) // Sit down and cross leg 坐下翹腳
   {
      Squat = 0;
      for(int i = 0; i < 11 ; i++)
         ActionTheta[i] = 0.0;
      for (int i = 0; i < 24; i++)
      {
         ActionPosi[i] = 0.0;
         if(i == 6)
            ActionPosi[i] = 180.0;
      }
      timer = timer + 1;
      if(timer % 25 == 0 || timer % 25 == 1 || timer % 25 == 2 || 
         timer % 25 == 3 || timer % 25 == 4 || timer % 25 == 5)
      {
         Squat = -1.0;
         ActionPosi[12] = 0;
         ActionPosi[15] = 0.0;
         ActionPosi[18] = -20.0;
         ActionPosi[19] = -10.0;
         ActionPosi[20] = 20.0;
         ActionPosi[21] = 20.0;
         ActionPosi[22] = -30.0;
         ActionPosi[23] = 10.0;
      }
      if(timer % 25 == 6 || timer % 25 == 7 || timer % 25 == 8 || 
         timer % 25 == 9 || timer % 25 == 10 || timer % 25 == 11)
      {
         Squat = -2.0;
         ActionPosi[12] = -40.0;
         ActionPosi[15] = 90.0;
         ActionPosi[18] = -50.0;
         ActionPosi[19] = -90.0;
         ActionPosi[20] = 20.0;
         ActionPosi[21] = 50.0;
         ActionPosi[22] = -30.0;
         ActionPosi[23] = 10.0;
      }
      
      if(timer % 25 == 12 || timer % 25 == 13 || timer % 25 == 14 || 
         timer % 25 == 15 || timer % 25 == 16 || timer % 25 == 17 || 
         timer % 25 == 18 || timer % 25 == 19 || timer % 25 == 20 || 
         timer % 25 == 21 || timer % 25 == 22 || timer % 25 == 23 || 
         timer % 25 == 24)
      {
         Squat = -3.0;
         ActionPosi[12] = -80.0;
         ActionPosi[15] = 90.0;
         ActionPosi[18] = -70.0;
         ActionPosi[19] = -90.0;
         ActionPosi[20] = 20.0;
         ActionPosi[21] = 90.0;
         ActionPosi[22] = -30.0;
         ActionPosi[23] = 10.0;
      }
   }
   if(SelectActionNum == 2)   // Boxing 拳擊
   {
      Squat = -0.8;
      for(int i = 0; i < 11 ; i++)
         ActionTheta[i] = 0.0;
      for (int i = 0; i < 24; i++)
      {
         ActionPosi[i] = 0.0;
         if(i == 6)
            ActionPosi[i] = 180.0;
      }
      timer = timer + 1;
      if(timer % 25 == 0 || timer % 25 == 1 || timer % 25 == 2 || 
         timer % 25 == 3 || timer % 25 == 4 || timer % 25 == 5 )
      {
         ActionPosi[0] = -50.0;
         ActionPosi[1] = -60.0;
         ActionPosi[2] = -5.0;
         ActionPosi[3] = -60.0;
         ActionPosi[4] = -30.0;
         ActionPosi[5] = 20.0;
         ActionPosi[6] = 100.0;
         ActionPosi[7] = -60.0;
         ActionPosi[8] = -5.0;
         ActionPosi[9] = -60.0;
         ActionPosi[10] = -30.0;
         ActionPosi[11] = 80.0;
         ActionPosi[12] = 0.0;
         ActionPosi[13] = -60.0;
         ActionPosi[14] = 10.0;
         ActionPosi[15] = 0.0;
         ActionPosi[16] = -30.0;
         ActionPosi[17] = -30.0;
         ActionPosi[18] = -20.0;
         ActionPosi[19] = -60.0;
         ActionPosi[20] = 0.0;
         ActionPosi[21] = 0.0;
         ActionPosi[22] = -30.0;
         ActionPosi[23] = -30.0;
      }
      if(timer % 25 == 6 || timer % 25 == 7 || timer % 25 == 8 || 
         timer % 25 == 9 || timer % 25 == 10 || timer % 25 == 11 )
      {
         ActionPosi[0] = -70.0;
         ActionPosi[1] = -60.0;
         ActionPosi[2] = 10.0;
         ActionPosi[3] = -10.0;
         ActionPosi[4] = 60.0;
         ActionPosi[5] = 0.0;
         ActionPosi[6] = 100.0;
         ActionPosi[7] = -60.0;
         ActionPosi[8] = -5.0;
         ActionPosi[9] = -60.0;
         ActionPosi[10] = -30.0;
         ActionPosi[11] = 80.0;
         ActionPosi[12] = 0.0;
         ActionPosi[13] = -60.0;
         ActionPosi[14] = 10.0;
         ActionPosi[15] = 0.0;
         ActionPosi[16] = -30.0;
         ActionPosi[17] = -30.0;
         ActionPosi[18] = -20.0;
         ActionPosi[19] = -60.0;
         ActionPosi[20] = 0.0;
         ActionPosi[21] = 0.0;
         ActionPosi[22] = -30.0;
         ActionPosi[23] = -30.0;
      }
      if(timer % 25 == 12 || timer % 25 == 13 || timer % 25 == 14 || 
         timer % 25 == 15 || timer % 25 == 16 || timer % 25 == 17 || 
         timer % 25 == 18 || timer % 25 == 19 || timer % 25 == 20 || 
         timer % 25 == 21 || timer % 25 == 22 || timer % 25 == 23 || 
         timer % 25 == 24)
      {
         ActionPosi[0] = -90.0;
         ActionPosi[1] = -60.0;
         ActionPosi[2] = 0.0;
         ActionPosi[3] = 60.0;
         ActionPosi[4] = 0.0;
         ActionPosi[5] = 0.0;
         ActionPosi[6] = 100.0;
         ActionPosi[7] = -60.0;
         ActionPosi[8] = -5.0;
         ActionPosi[9] = -60.0;
         ActionPosi[10] = -30.0;
         ActionPosi[11] = 80.0;
         ActionPosi[12] = 0.0;
         ActionPosi[13] = -60.0;
         ActionPosi[14] = 10.0;
         ActionPosi[15] = 0.0;
         ActionPosi[16] = -30.0;
         ActionPosi[17] = -30.0;
         ActionPosi[18] = -20.0;
         ActionPosi[19] = -60.0;
         ActionPosi[20] = 0.0;
         ActionPosi[21] = 0.0;
         ActionPosi[22] = -30.0;
         ActionPosi[23] = -30.0;
      }
   }
   if(SelectActionNum == 3) // Lifting dumbbells 舉重
   {
      Squat = 0;
      for(int i = 0; i < 11 ; i++)
         ActionTheta[i] = 0.0;
      for (int i = 0; i < 24; i++)
      {
         ActionPosi[i] = 0.0;
         if(i == 6)
            ActionPosi[i] = 180.0;
      }
      ActionPosi[0] = 0.0;
      ActionPosi[6] = 120.0;
      ActionPosi[12] = 0.0;
      ActionPosi[13] = 0.0;
      ActionPosi[14] = 0.0;
      ActionPosi[18] = 0.0;
      ActionPosi[19] = 0.0;
      ActionPosi[20] = 0.0;
      ActionPosi[21] = 0.0;
      ActionPosi[22] = 0.0;
      timer = timer + 1;
      if(timer % 24 == 0)
         ActionTheta[6] = -60.0;
      if(timer % 24 == 1)
         ActionTheta[6] = -50.0;
      if(timer % 24 == 2)
         ActionTheta[6] = -40.0;
      if(timer % 24 == 3)
         ActionTheta[6] = -30.0;
      if(timer % 24 == 4)
         ActionTheta[6] = -20.0;
      if(timer % 24 == 5)
         ActionTheta[6] = -10.0;
      if(timer % 24 == 6)
         ActionTheta[6] = 0.0;
      if(timer % 24 == 7)
         ActionTheta[6] = 10.0;
      if(timer % 24 == 8)
         ActionTheta[6] = 20.0;
      if(timer % 24 == 9)
         ActionTheta[6] = 30.0;
      if(timer % 24 == 10)
         ActionTheta[6] = 40.0;
      if(timer % 24 == 11)
         ActionTheta[6] = 50.0; 
      if(timer % 24 == 12)
         ActionTheta[6] = 60.0;
      if(timer % 24 == 13)
         ActionTheta[6] = 50.0;
      if(timer % 24 == 14)
         ActionTheta[6] = 40.0;
      if(timer % 24 == 15)
         ActionTheta[6] = 30.0;
      if(timer % 24 == 16)
         ActionTheta[6] = 20.0;
      if(timer % 24 == 17)
         ActionTheta[6] = 10.0;
      if(timer % 24 == 18)
         ActionTheta[6] = 0.0;
      if(timer % 24 == 19)
         ActionTheta[6] = -10.0;
      if(timer % 24 == 20)
         ActionTheta[6] = -20.0;
      if(timer % 24 == 21)
         ActionTheta[6] = -30.0;
      if(timer % 24 == 22)
         ActionTheta[6] = -40.0;
      if(timer % 24 == 23)
         ActionTheta[6] = -50.0;
   }
   if(SelectActionNum == 4)   // Open and close jump 開合跳
   {
      for(int i = 0; i < 11 ; i++)
         ActionTheta[i] = 0.0;
      for (int i = 0; i < 24; i++)
      {
         ActionPosi[i] = 0.0;
         if(i == 6)
            ActionPosi[i] = 180.0;
      }
      timer = timer + 1;
      if(timer % 25 == 0 || timer % 25 == 1 || timer % 25 == 2 || 
         timer % 25 == 3 || timer % 25 == 4 || timer % 25 == 5 )
      {
         Squat = 1;
         ActionPosi[0] = 0.0;
         ActionPosi[1] = 0.0;
         ActionPosi[2] = 140.0;
         ActionPosi[3] = -30.0;
         ActionPosi[4] = 90.0;
         ActionPosi[5] = 90.0;
         ActionPosi[6] = -180.0;
         ActionPosi[7] = -180.0;
         ActionPosi[8] = 140.0;
         ActionPosi[9] = -30.0;
         ActionPosi[10] = 90.0;
         ActionPosi[11] = 90.0;
         ActionPosi[12] = 0.0;
         ActionPosi[13] = 0;
         ActionPosi[14] = 10;
         ActionPosi[15] = 0.0;
         ActionPosi[16] = 0;
         ActionPosi[17] = 0;
         ActionPosi[18] = 0;
         ActionPosi[19] = 0;
         ActionPosi[20] = -10.0;
         ActionPosi[21] = 0.0;
         ActionPosi[22] = 0;
         ActionPosi[23] = 0;
      }
      if(timer % 25 == 6 || timer % 25 == 7 || timer % 25 == 8 || 
         timer % 25 == 9 || timer % 25 == 10 || timer % 25 == 11 )
      {
         Squat = 0;
         ActionPosi[0] = 0.0;
         ActionPosi[1] = 0.0;
         ActionPosi[2] = 190.0;
         ActionPosi[3] = -30.0;
         ActionPosi[4] = 90.0;
         ActionPosi[5] = 90.0;
         ActionPosi[6] = -180.0;
         ActionPosi[7] = -180.0;
         ActionPosi[8] = 190.0;
         ActionPosi[9] = -30.0;
         ActionPosi[10] = 90.0;
         ActionPosi[11] = 90.0;
         ActionPosi[12] = 0.0;
         ActionPosi[13] = 0;
         ActionPosi[14] = 30;
         ActionPosi[15] = 0.0;
         ActionPosi[16] = 0;
         ActionPosi[17] = 0;
         ActionPosi[18] = 0;
         ActionPosi[19] = 0;
         ActionPosi[20] = -30.0;
         ActionPosi[21] = 0.0;
         ActionPosi[22] = 0;
         ActionPosi[23] = 0;
      }
      if(timer % 25 == 12 || timer % 25 == 13 || timer % 25 == 14 || 
         timer % 25 == 15 || timer % 25 == 16 || timer % 25 == 17 )
      {
         Squat = 1;
         ActionPosi[0] = 0.0;
         ActionPosi[1] = 0.0;
         ActionPosi[2] = 140.0;
         ActionPosi[3] = -30.0;
         ActionPosi[4] = 90.0;
         ActionPosi[5] = 90.0;

         ActionPosi[6] = -180.0;
         ActionPosi[7] = -180.0;
         ActionPosi[8] = 140.0;

         ActionPosi[9] = -30.0;
         ActionPosi[10] = 90.0;
         ActionPosi[11] = 90.0;

         ActionPosi[12] = 0.0;
         ActionPosi[13] = 0;
         ActionPosi[14] = 10;

         ActionPosi[15] = 0.0;
         ActionPosi[16] = 0;
         ActionPosi[17] = 0;

         ActionPosi[18] = 0;
         ActionPosi[19] = 0;
         ActionPosi[20] = -10.0;

         ActionPosi[21] = 0.0;
         ActionPosi[22] = 0;
         ActionPosi[23] = 0;
      }
      if(timer % 25 == 18 || timer % 25 == 19 || timer % 25 == 20 || 
         timer % 25 == 21 || timer % 25 == 22 || timer % 25 == 23 || timer % 25 == 24)
      {
         Squat = 0;
         ActionPosi[0] = 0.0;    // 我視角的右手 軸肢
         ActionPosi[1] = 0.0;
         ActionPosi[2] = 0.0; 
         ActionPosi[3] = -30.0;  // 我視角的右手 前肢
         ActionPosi[4] = 90.0;
         ActionPosi[5] = 90.0;
         ActionPosi[6] = -180.0; // 我視角的左手 軸肢
         ActionPosi[7] = -180.0;
         ActionPosi[8] = 0.0;
         ActionPosi[9] = -30.0;  // 我視角的左手 前肢
         ActionPosi[10] = 90.0;
         ActionPosi[11] = 90.0;
         ActionPosi[12] = 0.0;   // 我視角的右腳 軸肢
         ActionPosi[13] = 0;
         ActionPosi[14] = 0;
         ActionPosi[15] = 0.0;   // 我視角的右腳 前肢
         ActionPosi[16] = 0;
         ActionPosi[17] = 0;
         ActionPosi[18] = 0;     // 我視角的左腳 軸肢
         ActionPosi[19] = 0;
         ActionPosi[20] = 0.0;
         ActionPosi[21] = 0.0;   // 我視角的左腳 前肢
         ActionPosi[22] = 0;
         ActionPosi[23] = 0;
      }
   }
   if(SelectActionNum == 5)   // Restart 初始動作
   {
      Squat = 0;
      for(int i = 0; i < 11 ; i++)
         ActionTheta[i] = 0.0;
      for (int i = 0; i < 24; i++)
      {
         ActionPosi[i] = 0.0;
         if(i == 6)
            ActionPosi[i] = 180.0;
      }
   }
   glutPostRedisplay();
	glutTimerFunc(60,ActionChange,1);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   glColor3f(1.0, 0.0, 0.0);

   /* ********************************  身體  ************************************/
   glRotatef(theta[0], 0.0, 1.0, 0.0);
   glTranslatef(0.0, Squat, 0.0);
   torso();

   /* *********************************  頭  ************************************/
   glPushMatrix();
   glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
   glRotatef(theta[1], 1.0, 0.0, 0.0);
   glRotatef(theta[2], 0.0, 1.0, 0.0);
   glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
   head();
   glPopMatrix();

   /* ****************************  我視角的左手  *******************************/
   glPushMatrix();
   glTranslatef(TORSO_HEIGHT * -0.47, 0.7 * TORSO_HEIGHT, 0.0);
   glRotatef(180, 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[0], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[1], 0.0, 1.0, 0.0);
   glRotatef(ActionPosi[2], 0.0, 0.0, 1.0);
   // 軸肢
   left_upper_arm();
   glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
   glRotatef(theta[4], 1.0, 0.0, 0.0);
   glRotatef(ActionTheta[5], 1.0, 0.0, 0.0);
   // 前肢
   glRotatef(ActionPosi[3], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[4], 0.0, 1.0, 0.0);
   glRotatef(ActionPosi[5], 0.0, 0.0, 1.0);
   left_lower_arm();
   glPopMatrix();

   /* ****************************  我視角的右手  *******************************/
   glPushMatrix();
   glTranslatef(TORSO_HEIGHT * 0.47, 0.7 * TORSO_HEIGHT, 0.0);
   glRotatef(theta[5], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[6], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[7], 0.0, 1.0, 0.0);
   glRotatef(ActionPosi[8], 0.0, 0.0, 1.0);
   // 軸肢
   right_upper_arm();
   glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
   glRotatef(theta[6], 1.0, 0.0, 0.0);
   glRotatef(ActionTheta[6], 1.0, 0.0, 0.0);
   // 前肢
   glRotatef(ActionPosi[9], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[10], 0.0, 1.0, 0.0);
   glRotatef(ActionPosi[11], 0.0, 0.0, 1.0);
   right_lower_arm();
   glPopMatrix();

   /* ****************************  我視角的左腳  *******************************/
   glPushMatrix();
   glTranslatef(-(TORSO_RADIUS+UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
   glTranslatef(0.5555, -0.5, 0.0);
   glRotatef(theta[7], 1.0, 0.0, 0.0);
   // 軸肢
   glRotatef(ActionPosi[12], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[13], 0.0, 1.0, 0.0);
   glRotatef(ActionPosi[14], 0.0, 0.0, 1.0);
   left_upper_leg();
   glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
   glRotatef(theta[8], 1.0, 0.0, 0.0);
   // 前肢
   glRotatef(ActionPosi[15], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[16], 0.0, 1.0, 0.0);
   glRotatef(ActionPosi[17], 0.0, 0.0, 1.0);
   left_lower_leg();
   glPopMatrix();

   /* ****************************  我視角的右腳  *******************************/
   glPushMatrix();
   glTranslatef(TORSO_RADIUS+UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
   glTranslatef(-0.5555, -0.5, 0.0);
   glRotatef(theta[9], 1.0, 0.0, 0.0);
   // 軸肢
   glRotatef(ActionPosi[18], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[19], 0.0, 1.0, 0.0);
   glRotatef(ActionPosi[20], 0.0, 0.0, 1.0);
   right_upper_leg();
   glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
   glRotatef(theta[10], 1.0, 0.0, 0.0);
   // 前肢
   glRotatef(ActionPosi[21], 1.0, 0.0, 0.0);
   glRotatef(ActionPosi[22], 0.0, 1.0, 0.0);
   glRotatef(ActionPosi[23], 0.0, 0.0, 1.0);
   right_lower_leg();
   glPopMatrix();

   glFlush();
   glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
   {
      theta[angle] += 5.0;
      if( theta[angle] > 360.0 ) theta[angle] -= 360.0;
   }
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
   {
      theta[angle] -= 5.0;
      if( theta[angle] < 360.0 ) theta[angle] += 360.0;
   }
   display();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w, 10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h, 10.0 * (GLfloat) w / (GLfloat) h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myinit()
{
   GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess={100.0};
	GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
	GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[]={10.0, 10.0, 10.0, 0.0};

   // 設置光源 glLightfv(光源編號, 光源特性, 參數數據)
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

   // 設置材質 決定打光出來的效果
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

   // 控制繪製指定兩點間其他點顏色的過度模式
	glShadeModel(GL_SMOOTH);
   glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_COLOR_MATERIAL);
    
   // 設置視窗背景顏色
   glClearColor(0.796, 0.553, 0.553, 1.0);

   h=gluNewQuadric();
   gluQuadricDrawStyle(h, GLU_FILL);
   t=gluNewQuadric();
   gluQuadricDrawStyle(t, GLU_FILL);
   lua=gluNewQuadric();
   gluQuadricDrawStyle(lua, GLU_FILL);
   lla=gluNewQuadric();
   gluQuadricDrawStyle(lla, GLU_FILL);
   rua=gluNewQuadric();
   gluQuadricDrawStyle(rua, GLU_FILL);
   rla=gluNewQuadric();
   gluQuadricDrawStyle(rla, GLU_FILL);
   lul=gluNewQuadric();
   gluQuadricDrawStyle(lul, GLU_FILL);
   lll=gluNewQuadric();
   gluQuadricDrawStyle(lll, GLU_FILL);
   rul=gluNewQuadric();
   gluQuadricDrawStyle(rul, GLU_FILL);
   rll=gluNewQuadric();
   gluQuadricDrawStyle(rll, GLU_FILL);
   quadratic = gluNewQuadric();
   gluQuadricDrawStyle(quadratic, GLU_FILL);
}

void BasicMenu(int id)
{
   if(id < 11) 
      angle = id;
   glutPostRedisplay();
}

void ActionMenu(int id)
{
   if(id == 11) // Sit down and cross leg 坐下翹腳
      SelectActionNum = 1;
   if(id == 12) // Boxing 拳擊
      SelectActionNum = 2;
   if(id == 13) // Lifting dumbbells 舉重
      SelectActionNum = 3;
   if(id == 14)
      SelectActionNum = 4;
   if(id == 15) // Restart
      SelectActionNum = 5;
   glutPostRedisplay();
}

void MainMenu(int id)
{
   if(id == 16)
      exit(0);
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutCreateWindow("HW3 Robot - 406262216");
   myinit();
   glutReshapeFunc(myReshape);
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   // 計時器
   glutTimerFunc(33,ActionChange,1);

   // 創建基本的動作選單
   int Basic_Menu = glutCreateMenu(BasicMenu);
   glutAddMenuEntry("torso", 0);
   glutAddMenuEntry("right_upper_arm", 3);
   glutAddMenuEntry("right_lower_arm", 4);
   glutAddMenuEntry("left_upper_arm", 5);
   glutAddMenuEntry("left_lower_arm", 6);
   glutAddMenuEntry("right_upper_leg", 7);
   glutAddMenuEntry("right_lower_leg", 8);
   glutAddMenuEntry("left_upper_leg", 9);
   glutAddMenuEntry("left_lower_leg", 10);

   // 創建設計的動作選單
   int Action_Menu = glutCreateMenu(ActionMenu);
   glutAddMenuEntry("Sit down and cross leg", 11);
   glutAddMenuEntry("Boxing", 12);
   glutAddMenuEntry("Lifting dumbbells", 13);
   glutAddMenuEntry("Open and close jump", 14);
   glutAddMenuEntry("Restart", 15);

   // 創建主選單，並將 Basic 和 Action Menu 將上主選單
   glutCreateMenu(MainMenu);
   glutAddSubMenu("Basic", Basic_Menu);
   glutAddSubMenu("Action", Action_Menu);
   glutAddMenuEntry("exit", 16);
   glutAttachMenu(GLUT_MIDDLE_BUTTON);

   glutMainLoop();
}
