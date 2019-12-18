//
//  main.cpp
//  penGLMidterm
//
//  Created by 劉品萱 on 2019/9/27.
//  Copyright © 2019 劉品萱. All rights reserved.
//

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <GL/glut.h>
#include <GL/glui.h>
#include <windows.h>

#define PI 3.14159265
#define MS 10.0
#define TN 3.5
#define FRAME 10
#define MAX_CHAR 128

int type = 1;
int timer = 0;
int RainBowFuntion = 0;
int WindowId;

// 光源參數
GLfloat light0_v[4] =  {0.6, 0.6, 0.6, 1};

// 設置控制點座標
GLfloat cpts[2][7][3] = {{{5.0, 8.0, 0.0}, {3.0, 5.0, 0.0}, {2.0, 2, 0.0}, {5.0, 0.0, 0.0}, {7.0, -2.0, 0.0}, {8.0, -5.0, 0.0}, {6.0, -7.0, 0.0}}};
GLubyte image[64][64][3];
GLfloat r1[3][3] = {{static_cast<GLfloat>(cos(PI / 180.0)), 0.0, static_cast<GLfloat>(sin(PI / 180.0))}, {0.0, 1.0, 0.0}, {static_cast<GLfloat>(-sin(PI / 180.0)), 0.0, static_cast<GLfloat>(cos(PI / 180.0))}};
GLfloat r10[3][3] = {{static_cast<GLfloat>(cos(PI / 18.0)), 0.0, static_cast<GLfloat>(sin(PI / 18.0))}, {0.0, 1.0, 0.0}, {static_cast<GLfloat>(-sin(PI / 18.0)), 0.0, static_cast<GLfloat>(cos(PI / 18.0))}};
GLfloat r100[3][3] = {{static_cast<GLfloat>(cos(PI / 180.0)), 0.0, static_cast<GLfloat>(sin(PI / 180.0))}, {0.0, 1.0, 0.0}, {static_cast<GLfloat>(-sin(PI / 180.0)), 0.0, static_cast<GLfloat>(cos(PI / 180.0))}};
GLfloat thta[2] = {0.0, 0.0};
float p[3], mp[3], interw, interh, mrgb[3] = {0.0, 0.4, 0.8};
int pn = 7, ww, hh;

// 繪製字樣
void printString(const char* str)
{
    static int isFirstCall = 1;
    static GLuint lists;
    // 如果是第一次調用，則執行初始化。並且為每一個ASCII字符產生一個顯示列表
    // 为每一个ASCII字符产生一个显示列表
    if( isFirstCall ) {             
         isFirstCall = 0;
         // 申請MAX_CHAR個連續的顯示列表編號
         lists = glGenLists(MAX_CHAR);
         // 把每個字符的繪製命令都裝到對應的顯示列表中
         wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
     }
    // 調用每個字符對應的顯示列表，繪製每個字符
    for(; *str!='\0'; ++str)
         glCallList(lists + *str);
}

// 計算旋轉角度使用，搭配 display
void vmult(float m[3][3], float v[3], float r[3])
{
    int i, j;
    for(i = 0; i < 3; ++i){
        for(j = 0, r[i] = 0.0; j < 3; ++j){
            r[i] += m[i][j] * v[j];
        }
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 初始化 Martix
    glLoadIdentity();

    glPushMatrix();
    glTranslated(TN * (float)ww / (float)hh, 0.0, 0.0);
    
    /****************產生貝式曲線 ****************/   
    glColor3f(0.2, 0.8, 0.3);
    
    // 為曲線建立對應, u 的數值由 0 到 1
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &cpts[0][0][0]);
    /*  glMap1f(控制點代表頂點座標, u值起頭, u值結尾, 每個儲存塊之間單精度或雙精度浮點數的數量, 控制點數量, 指向第一個控制點的第一個座標)*/
    glMapGrid1f(30, 0.0, 1.0);
    /*  glMapGrid1f(網格中間的階段, u值起頭, u值結尾)*/
    glEvalMesh1(GL_LINE, 0, 30);
    /*  glEvalMesh1(mode,i1,i2)
     對所有已經啟用的求值器應用定義一維網格。
     mode參數可以是GL_POINT、GL_LINE。
     这个函数相當於從i1到i2的每一步都調用glMapGrid1d函数，其中0<i1,i2<n*/
    
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &cpts[0][3][0]);
    glMapGrid1f(30, 0.0, 1.0);
    glEvalMesh1(GL_LINE, 0, 30);
    
    // 設置控制點大小
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    glVertex3fv(cpts[0][0]);
    glVertex3fv(cpts[0][1]);
    glVertex3fv(cpts[0][2]);
    glVertex3fv(cpts[0][3]);
    glVertex3fv(cpts[0][4]);
    glVertex3fv(cpts[0][5]);
    glVertex3fv(cpts[0][6]);
    glEnd();
    
    // 將每個控制點連線
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    {
        for(int i = 0 ; i < 7 ; i++)
            glVertex3fv(cpts[0][i]);
    }
    glEnd();

    // 繪製字
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-8.5f, 9.0f);
    printString("Midterm Homework - 406262216");
    glRasterPos2f(-13.0f, -8.5f);
    printString("You can move the curve control points to change the shape of the 3D model.");
    glRasterPos2f(-13.0f, -9.0f);
    printString("And you can click left mouse button and move view then 3D model will rotate.");
    glRasterPos2f(-13.0f, -9.5f);
    printString("In addition, click middle mouse button can open menu.");

    // 模型顏色
    glColor3f(1, 1, 1);
    glBegin(GL_LINE);
    glVertex3fv(cpts[0][0]);
    glVertex3fv(cpts[0][1]);
    glEnd();

    glPopMatrix();
    glTranslated(-TN * (float)ww / (float)hh, 0.0, 0.0);

    // 讓模型能夠旋轉
    glRotatef(thta[1], 1.0, 0.0, 0.0);
    glRotatef(thta[2], 0.0, 1.0, 0.0);
    glRotatef(thta[0], 0.0, 0.0, 1.0);
    
    int i;

    // type 對應主選單點選的選項，並依照設定好的角度讓運算控制點後將數值存起來
    switch(type){
        case 1:
            for(i = 0; i < 7; ++i)
                vmult(r10, cpts[0][i], cpts[1][i]);
            break;
        case 2:
            for(i = 0; i < 7; ++i)
                vmult(r1, cpts[0][i], cpts[1][i]);
            break;
        case 3:
            for(i = 0; i < 7; ++i)
                vmult(r100, cpts[0][i], cpts[1][i]);
            break;
    }
    
    // type 對應主選單點選的選項，決定呈現的方式：Line、Fill、Point
    switch(type){
        case 1:
            // Line
            for(i = 0; i < 36; ++i){
                glRotatef(10.0, 0.0, 1.0, 0.0);
                
                glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 21, 2, &cpts[0][0][0]);
                //glMapGrid2f() 從 a 到 b 的範圍對映一個包含 n 個點的網格 
                glMapGrid2f(30,     // 產生網格數
                            0.0,    // u值下界
                            1.0,    // u值上界
                            10, 
                            0.0, 
                            1.0);
                // 計算網格
                glEvalMesh2(GL_LINE, 0, 30, 0, 10);
                
                glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 21, 2, &cpts[0][3][0]);
                glMapGrid2f(30, 0.0, 1.0, 10, 0.0, 1.0);
                glEvalMesh2(GL_LINE, 0, 30, 0, 10);
            }
            break;
        case 2:
            // Fill
            for(i = 0; i < 360; ++i){
                glRotatef(1.0, 0.0, 1.0, 0.0);
                
                glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 21, 2, &cpts[0][0][0]);
                glMapGrid2f(30, 0.0, 1.0, 10, 0.0, 1.0);
                glEvalMesh2(GL_FILL, 0, 30, 0, 10);
                
                glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 21, 2, &cpts[0][3][0]);
                glMapGrid2f(30, 0.0, 1.0, 10, 0.0, 1.0);
                glEvalMesh2(GL_FILL, 0, 30, 0, 10);
            }
            break;
        case 3:
            // Point
            for(i = 0; i < 360; ++i){
                glEnable(GL_POINT_SIZE);
                glEnable(GL_TEXTURE_2D);
                glPointSize(0.5f);
                glRotatef(1.0, 0.0, 1.0, 0.0);
                
                glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 21, 2, &cpts[0][0][0]);
                glMapGrid2f(30, 0.0, 1.0, 10, 0.0, 1.0);
                glEvalMesh2(GL_POINT, 0, 30, 0, 10);
                
                glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 21, 2, &cpts[0][3][0]);
                glMapGrid2f(30, 0.0, 1.0, 10, 0.0, 1.0);
                glEvalMesh2(GL_POINT, 0, 30, 0, 10);
            }
            break;
    }
    glFlush();
    glutSwapBuffers();
}

// 設置滑鼠按鍵回調函式，取得滑鼠拖動時的位置
void myMotion(int x, int y){
    y = hh - y;
    float tmp[3] = {static_cast<float>(2.0 * interw * (float)x / (float)ww - interw), static_cast<float>(2.0 * interh * (float)y / (float)hh - interh), 0.0};
    int i;
    if(pn == 7){
        for(i = 0; i < 2; ++i){
            if(mp[i] < tmp[i])
                --thta[i];
            else if(mp[i] > tmp[i])
                ++thta[i];
            if(thta[i] >= 360.0 || thta[i] <= -360.0)
                thta[i] = 0.0;
        }
    }
    else{
        for(i = 0; i < 3; ++i)
            cpts[0][pn][i] = tmp[i];
        cpts[0][pn][0] -= TN * (float)ww / (float)hh;
    }
    mp[0] = tmp[0];
    mp[1] = tmp[1];
    glutPostRedisplay();
}

// myMouse 使用
float dis2p(float a[3], float b[3]){
    return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));
}

// 用來換算滑鼠位置，搭配 dis2p 使用
void myMouse(int btn, int state, int x, int y){
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        y = hh - y;
        p[0] = mp[0] = 2.0 * interw * (float)x / (float)ww - interw - TN * (float)ww / (float)hh;
        p[1] = mp[1] = 2.0 * interh * (float)y / (float)hh - interh;
        int i;
        
        for(i = 0; i < 7; ++i){
            if(dis2p(cpts[0][i], p) <= 1.0){
                pn = i;
                break;
            }
        }
    }
    else
        pn = 7;
}

// 當應用程式視窗大小調動時調用的函式
void myReshape(int w, int h)
{
    // w 代表 window 寬度，h 代表 window 高度
    // 檢視設定，即告訴 openGL 渲染之後的圖形會繪製在哪
    glViewport(0,   // 視見區域的左下角在視窗中的 x 位置
               0,   // 視見區域的左下角在視窗中的 y 位置
               w,   // 視見區域的寬度
               h);  // 視見區域的高度

    // 聲明接下來要做什麼
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (w <= h){
        // glOrtho(left, right, bottom, top, near, far)
        glOrtho(-FRAME,     // 視景體左面座標（left）
                FRAME,      // 視景體右面座標（right）
                -FRAME * ((GLfloat) h / (GLfloat) w),   // （buttom）
                FRAME * ((GLfloat) h / (GLfloat) w),    // （top）
                -FRAME,     // (near）
                FRAME);     //（far）
        interw = FRAME;
        interh = FRAME * (GLfloat) h / (GLfloat) w;
    }
    else{
        glOrtho(-FRAME * (GLfloat) w / (GLfloat) h, FRAME * (GLfloat) w / (GLfloat) h, -FRAME, FRAME, -FRAME, FRAME);
        interw = FRAME * (GLfloat) w / (GLfloat) h;
        interh = FRAME;
    }
    
    // 聲明接下來要做什麼
    glMatrixMode(GL_MODELVIEW);
    ww = w;
    hh = h;
}

// 七彩變換選單，改變 RainBowFunction 數值來開關效果
void RainbowShowMenu(int index)
{
    if(index == 1)
        RainBowFuntion = 1;
    if(index == 2)
        RainBowFuntion = 0;
}

// 顏色選單，直接改變light0_v array 的數值
void ColorMenu(int index){
    RainBowFuntion = 0;
    switch(index){
        case 1:     //White
            light0_v[0] = 1.000000;
            light0_v[1] = 1.000000;
            light0_v[2] = 1.000000;
            light0_v[3] = 1.000000;
            break;
        case 2:     //Red
            light0_v[0] = 1.000000;
            light0_v[1] = 0.000000;
            light0_v[2] = 0.000000;
            light0_v[3] = 0.000000;
            break;
        case 3:     //Orange
            light0_v[0] = 1.000000;
            light0_v[1] = 0.560976;
            light0_v[2] = 0.000000;
            light0_v[3] = 1.000000;
            break;
        case 4:     //Yellow
            light0_v[0] = 1.000000;
            light0_v[1] = 1.000000;
            light0_v[2] = 0.000000;
            light0_v[3] = 0.000000;
            break;
        case 5:     //Green
            light0_v[0] = 0.000000;
            light0_v[1] = 1.000000;
            light0_v[2] = 0.000000;
            light0_v[3] = 0.000000;
            break;
        case 6:     //Blue
            light0_v[0] = 0.000000;
            light0_v[1] = 0.560976;
            light0_v[2] = 1.000000;
            light0_v[3] = 1.000000;
            break;
        case 7:     //DarkBlue
            light0_v[0] = 0.000000;
            light0_v[1] = 0.000000;
            light0_v[2] = 1.000000;
            light0_v[3] = 1.000000;
            break;
        case 8:     //Purple
            light0_v[0] = 0.414634;
            light0_v[1] = 0.000000;
            light0_v[2] = 1.000000;
            light0_v[3] = 1.000000;
            break;
    }
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_v);
    glutPostRedisplay();
}

// 主選單
void MainMenu(int index){
    if(index == 4)
        exit(0);
    type = index;
    glutPostRedisplay();
}

// 當 RainBowFuntion == 1 時，七彩變化效果開啟，隨時間改變light0_v array 的值
void RainbowShow(int value)
{
    if(RainBowFuntion == 1)
    {
        timer = timer + 1;
        // 紅
        if(timer % 7 == 0)
        {
            light0_v[0] = 1.000000;
            light0_v[1] = 0.000000;
            light0_v[2] = 0.000000;
            light0_v[3] = 0.000000;
        }
        // 橙
        if(timer % 7 == 1)
        {
            light0_v[0] = 1.000000;
            light0_v[1] = 0.560976;
            light0_v[2] = 0.000000;
            light0_v[3] = 1.000000;
        }
        if(timer % 7 == 2)
        {
            light0_v[0] = 1.000000;
            light0_v[1] = 1.000000;
            light0_v[2] = 0.000000;
            light0_v[3] = 0.000000;
        }
        if(timer % 7 == 3)
        {
            light0_v[0] = 0.000000;
            light0_v[1] = 1.000000;
            light0_v[2] = 0.000000;
            light0_v[3] = 0.000000;
        }
        if(timer % 7 == 4)
        {
            light0_v[0] = 0.000000;
            light0_v[1] = 0.560976;
            light0_v[2] = 1.000000;
            light0_v[3] = 1.000000;
        }
        if(timer % 7 == 5)
        {
            light0_v[0] = 0.000000;
            light0_v[1] = 0.000000;
            light0_v[2] = 1.000000;
            light0_v[3] = 1.000000;
        }
        if(timer % 7 == 6)
        {
            light0_v[0] = 0.414634;
            light0_v[1] = 0.000000;
            light0_v[2] = 1.000000;
            light0_v[3] = 1.000000;
        }
    }
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_v);
    glutPostRedisplay();
    glutTimerFunc(60,RainbowShow,1);
}

// 光源、材質、背景顏色等的初始化函式
void myinit()
{
    GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[]={0.8, 0.8, 0.8, 1.0};
    GLfloat mat_shininess={50.0};
    
    GLfloat light_specular[]={0.6, 0.6, 0.6, 1.0};
    GLfloat light_diffuse[]={0.6, 0.6, 0.6, 1.0};
    GLfloat light_ambient[]={0.1, 0.1, 0.1, 1.0};
    
    // 設置光源 glLightfv(光源編號, 光源特性, 參數數據)
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);    // GL_AMBIENT 設置環境光屬性
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);    // GL_DIFFUSE 設置散射光屬性
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);  // GL_SPECULAR 設置鏡面反射光屬性
    
    // 設置材質 決定打光出來的效果、對應選單的color
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    
    // 控制繪製指定兩點間其他點顏色的過度模式
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    // 將視窗背景顏色設置為黑色
    glClearColor(0, 0, 0, 0);
    glColor3f(0.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    //glTexImage2D(GL_TEXTURE_2D,0,3,64,64,0,GL_RGB,GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    WindowId = glutCreateWindow("Midterm Homework - 406262216 ");
    myinit();

    // 創建 Color 子選單
    int Color_Menu;
    Color_Menu = glutCreateMenu(ColorMenu);

    glutAddMenuEntry("White", 1);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Orange", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Green", 5);
    glutAddMenuEntry("Blue", 6);
    glutAddMenuEntry("Indigo", 7);
    glutAddMenuEntry("Purple", 8);

    int RainbowShow_Menu;
    RainbowShow_Menu = glutCreateMenu(RainbowShowMenu);
    glutAddMenuEntry("Open", 1);
    glutAddMenuEntry("Close", 2);

    // 創建主選單
    glutCreateMenu(MainMenu);
    glutAddMenuEntry("Line", 1);
    glutAddMenuEntry("Fill", 2);
    glutAddMenuEntry("Point", 3);
    glutAddSubMenu("Colors", Color_Menu);
    glutAddSubMenu("Rainbow Show", RainbowShow_Menu);
    glutAddMenuEntry("exit", 4);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    // 設置當 Window 視窗大小改變時，作業系統也察覺到了，作業系統會呼叫myReshape Function
    glutReshapeFunc(myReshape);
    // OpenGL的繪圖動作都寫在其所指定的自定函式 display
    glutDisplayFunc(display);
    glutMouseFunc (myMouse);
    glutMotionFunc(myMotion);
    glutTimerFunc(33,RainbowShow,1);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MAP1_VERTEX_3);
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_MAP2_TEXTURE_COORD_2);

    glutMainLoop();
    
    return 0;
}
