## 基本 main
```cpp=
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800); //設置視窗大小
    glutCreateWindow("Midterm Homework"); //設置視窗名稱
    //glutReshapeFunc(myReshape);
    glutDisplayFunc(display2); //目前所知其必要存在
    glEnable(GL_DEPTH_TEST);
    glClearColorIiEXT(0, 0, 0, 1);
    glutMainLoop();
    
}
```
## Resource

* [作業整理](https://hackmd.io/tASW9OGSTTi9ANAW1Y9GVA)
