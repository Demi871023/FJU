## �� main
```cpp=
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800); //�]�m�����j�p
    glutCreateWindow("Midterm Homework"); //�]�m�����W��
    //glutReshapeFunc(myReshape);
    glutDisplayFunc(display2); //�ثe�Ҫ��䥲�n�s�b
    glEnable(GL_DEPTH_TEST);
    glClearColorIiEXT(0, 0, 0, 1);
    glutMainLoop();
    
}
```
## Resource
* [�W�ҺK�n](https://hackmd.io/91yUsQj-SBS3cZG6HC08Bg)
* [�@�~��z](https://hackmd.io/tASW9OGSTTi9ANAW1Y9GVA)
