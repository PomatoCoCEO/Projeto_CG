/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    ................................................ JHenriques / APerrotta
    Trabalho 3 - Visualizacao
======================================================================================= */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <ctype.h>
#include <iostream>
#include <bits/stdc++.h>
#include "../lib/keyboard/keyboard.h"
using namespace std;
int wScreen = 800, hScreen = 600;
int angZoom = 45;
GLdouble xCam = 4, yCam = 10, zCam = 30;
Keyboard k;
Cuboid cu;
//================================================================================
//=========================================================================== INIT
/*
vector<GLdouble> cuVertices = {
    0, 0, 0};*/
vector<GLdouble> cuVertices, cuColours;
vector<GLuint> vec = {0, 1, 3, 2};
int xPos, yPos;

void inicializa(void)
{
    glClearColor(0, 0, 0, 1); //������������������������������Apagar
    glEnable(GL_DEPTH_TEST);  //������������������������������Profundidade
    glShadeModel(GL_SMOOTH);  //������������������������������Interpolacao de cores

    glEnableClientState(GL_VERTEX_ARRAY);
    // glVertexPointer(3, GL_FLOAT, 0, &(k.pts[0])); //���������������VertexArrays: vertices + normais + cores
    // glNormalPointer(GL_FLOAT, 0, normais);
    // glEnableClientState(GL_NORMAL_ARRAY);
    //++++++++++++++++++++++++ cores ??
    glEnableClientState(GL_COLOR_ARRAY);
    // startCuboid();
    // drawCuboid();
    // glColorPointer(3, GL_FLOAT, 0, &(k.colours[0]));
}

void drawEixos()
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
    glColor4f(1, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(10, 0, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
    glColor4f(0, 1, 0, 1);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 10, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
    glColor4f(0, 0, 1, 1);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 10);
    glEnd();
}

void drawScene()
{
    k.draw();
}

void display(void)
{

    //================================================================= APaga ecran e lida com profundidade (3D)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //================================================================= N�o modificar !!!!!!!!!!!!
    glViewport(0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(/*rVisao * cos(PI / 2 * aVisao), yCam, rVisao * sin(PI / 2 * aVisao)*/ xCam, yCam, zCam, 10, 5, 2, 0, 1, 0);
    //================================================================= N�o modificar !!!!!!!!!!!!

    //����������������������������������������������������������Objectos
    drawEixos();
    drawScene();

    //. . . . . . . . . . . . . . . . . . . . .  Actualizacao
    glutSwapBuffers();
}

void press_key(int pos_key)
{
    cout << "Key pressed: " << pos_key << endl;
    k.keys[pos_key].velZ = -0.02; // press down
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{
    switch (toupper(key))
    {
    case 'W':
        press_key(0);
        break;
    case 'A':
        press_key(1);
        break;
    case 'S':
        press_key(2);
        break;
    case 'D':
        press_key(3);
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void teclasNotAscii(int key, int x, int y)
{
    //.. observador pode andar � volda da cena  (setas esquerda / direita)
    //.. observador pode andar para cima e para baixo (setas cima / baixo )

    if (key == GLUT_KEY_UP)
    {
        zCam += 0.1;
    }
    if (key == GLUT_KEY_DOWN)
    {
        zCam -= 0.1;
    }
    if (key == GLUT_KEY_LEFT)
    {
        // deg = (int)(deg + deltaAng) % 360;
        xCam -= 0.1;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        // deg = (int)(deg - deltaAng) % 360;
        xCam += 0.1;
    }
    if (key == GLUT_KEY_F1)
    {
        yCam -= 0.1;
    }
    if (key == GLUT_KEY_F2)
    {
        yCam += 0.1;
    }
    cout << "(x,y,z) = (" << xCam << "," << yCam << "," << zCam << ")\n";
    glutPostRedisplay();
}

void animate_keyboard(int time)
{
    // handle key pressing
    for (int i = 0; i < k.keys.size(); i++)
    {
        k.keys[i].deltaZ += k.keys[i].velZ;
        if (k.keys[i].deltaZ < -0.4 && k.keys[i].velZ < 0)
            k.keys[i].velZ = -k.keys[i].velZ;
        if (k.keys[i].deltaZ > 0 && k.keys[i].velZ > 0)
            k.keys[i].deltaZ = k.keys[i].velZ = 0;
    }
    k.mouse_wheel.velX -= 0.005 * k.mouse_wheel.velX;
    k.mouse_wheel.velY -= 0.005 * k.mouse_wheel.velY;
    glutPostRedisplay();
    cout << "Animating...\n";
    glutTimerFunc(16, animate_keyboard, 0);
}

//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("{jh,avperrotta@dei.uc.pt|    |Mover/rodar Cima:'r'|   |FaceVisivel:'f'|      |Observador:'SETAS'|        |Andar-'a/s'|        |Rodar -'e/d'| ");

    k = Keyboard();

    // cout << "Point length: " << k.pts.size() << "; colour length: " << k.colours.size() << endl;
    inicializa();
    // cu = Cuboid(point3d(0, 0, 0), 1, 1, 1, GREY);
    // cu.draw();
    // glutSwapBuffers();
    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, animate_keyboard, 0);
    glutMainLoop();

    return 0;
}
