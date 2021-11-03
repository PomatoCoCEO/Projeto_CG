#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <ctype.h>
#include <iostream>
#include <bits/stdc++.h>
#include "../lib/keyboard/keyboard.h"
GLdouble inc = 0.5;
int wScreen = 800, hScreen = 600;
GLdouble xCam = 10, yCam = 5, zCam = 10;
Keyboard k;
void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Comando de Jogo");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    // gluLookAt(-100, 30, -100, 0, 0, 0, 0, 1, 0);

    k = Keyboard();
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, &(k.pts[0]));
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_DOUBLE, 0, &(k.colours[0]));
}

void drawEixos()
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
    glColor4f(1, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(100, 0, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
    glColor4f(0, 1, 0, 1);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 100, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
    glColor4f(0, 0, 1, 1);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 100);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, wScreen, hScreen);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluPerspective(45, (float)wScreen / hScreen, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Keyboard k = Keyboard();
    // Keyboard k = Keyboard();
    gluLookAt(xCam, yCam, zCam, 0, 0, 0, 0, 0, 1);
    drawEixos();
    cout << "BOO\n----------------\n";
    // k.draw();
    glutSwapBuffers();
}

void teclasNotAscii(int key, int x, int y)
{
    //.. observador pode andar � volda da cena  (setas esquerda / direita)
    //.. observador pode andar para cima e para baixo (setas cima / baixo )

    if (key == GLUT_KEY_UP)
    {
        yCam += inc;
    }
    if (key == GLUT_KEY_DOWN)
    {
        yCam -= inc;
    }

    if (key == GLUT_KEY_RIGHT)
    {
        xCam += inc;
    }
    if (key == GLUT_KEY_LEFT)
    {
        xCam -= inc;
    }

    if (key == GLUT_KEY_F1)
    {
        zCam -= inc;
    }
    if (key == GLUT_KEY_F2)
    {
        zCam += inc;
    }
    cout << "(x,y,z)=(" << xCam << "," << yCam << "," << zCam << ")\n";

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    init(argc, argv);
    // k = Keyboard();

    display();
    // cout << "Boo\n";
    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutMainLoop();
}