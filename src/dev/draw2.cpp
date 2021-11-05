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
#include "../lib/player.h"
using namespace std;

int wScreen = 1200, hScreen = 900;
int angZoom = 45;
GLdouble xCam = 4, yCam = 10, zCam = 30;
GLdouble xFocus = 10, yFocus = 5, zFocus = 2, zoomRad = 20, verAng = 45, horAng = 45, zoomRatio = 0.02;
// point3d player = point3d(10, 2, 10);
Player player(point3d(20, 1, 20));
int mode = 0;
int zoomX = 0, zoomY = 0;
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
    gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (mode == 0)
        gluLookAt(/*rVisao * cos(PI / 2 * aVisao), yCam, rVisao * sin(PI / 2 * aVisao)*/
                  xFocus + zoomRad * cos(DEG_TO_RAD(horAng)) * sin(DEG_TO_RAD(verAng)),
                  yFocus + zoomRad * cos(DEG_TO_RAD(verAng)),
                  zFocus + zoomRad * sin(DEG_TO_RAD(horAng)) * sin(DEG_TO_RAD(verAng)),
                  xFocus, yFocus, zFocus, 0, 1, 0);
    else
    {
        point3d p = player.pos;
        point3d dir(p.x + cos(DEG_TO_RAD(player.angHor)) * sin(DEG_TO_RAD(player.angHeight)),
                    p.y + cos(DEG_TO_RAD(player.angHeight)),
                    p.z + sin(DEG_TO_RAD(player.angHor)) * sin(DEG_TO_RAD(player.angHeight)));
        gluLookAt(/*rVisao * cos(PI / 2 * aVisao), yCam, rVisao * sin(PI / 2 * aVisao)*/
                  p.x,
                  p.y,
                  p.z,
                  dir.x, dir.y, dir.z, 0, 1, 0);
        printf("(%lf,%lf,%lf) looking at (%lf, %lf, %lf)\n", p.x, p.y, p.z, dir.x, dir.y, dir.z);
    }
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
    if (k.keys[pos_key].deltaZ > -0.4)
        k.keys[pos_key].velZ = -0.02; // press down
    else
        k.keys[pos_key].velZ = 0.02;
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{
    switch (toupper(key))
    {
    case 'W':
        press_key(0);
        if (mode)
            player.move_front();
        break;
    case 'A':
        press_key(1);
        if (mode)
            player.move_left();
        break;
    case 'S':
        press_key(2);
        if (mode)
            player.move_back();
        break;
    case 'D':
        press_key(3);
        if (mode)
            player.move_right();
        break;
    case 'P':
        mode = 1 - mode;
        break;
    case ' ':
        press_key(4);
        if (mode)
            player.jump();
        break;
    case '+':
        verAng += 2.0;
        break;
    case '-':
        verAng -= 2.0;
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
        zFocus += 0.1;
    }
    if (key == GLUT_KEY_DOWN)
    {
        zFocus -= 0.1;
    }
    if (key == GLUT_KEY_LEFT)
    {
        // deg = (int)(deg + deltaAng) % 360;
        xFocus -= 0.1;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        // deg = (int)(deg - deltaAng) % 360;
        xFocus += 0.1;
    }
    if (key == GLUT_KEY_F1)
    {
        yFocus -= 0.1;
    }
    if (key == GLUT_KEY_F2)
    {
        yFocus += 0.1;
    }

    cout << "(x,y,z) = (" << xFocus << "," << yFocus << "," << zFocus << ")\n";
    glutPostRedisplay();
}

void zoom_wheel(int button, int state, int x, int y)
{
    cout << "Button " << button << endl;
    if (mode == 0)
        switch (button)
        {
        case 3:
            zoomRad -= zoomRatio * zoomRad;
            break;
        case 4:
            zoomRad += zoomRatio * zoomRad;
            break;
        case 7:
            zoomRatio *= 1.5;
            break;
        case 8:
            zoomRatio /= 1.5;
        default:
            break;
        }
    cout << "zoomRatio = " << zoomRatio << "\n";
}

void adjust_angle(int x, int y)
{
    int deltaX, deltaY;
    GLdouble aid;
    switch (mode)
    {
    case 0:
        deltaX = zoomX - x, deltaY = zoomY - y;
        if (abs(deltaX) < 20 && abs(deltaY) < 20)
        {
            horAng -= deltaX;
            aid = deltaY / 2.0;
            if (verAng + aid > 0 && verAng + aid < 180)
                verAng += aid;
        }
        zoomX = x;
        zoomY = y;
        break;
    }
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
    for (auto &c : k.mouse_wheel)
    {
        c.angX += c.velY;
        c.angY -= c.velX;
        GLdouble drag = 0.02;
        c.velX -= drag * c.velX;
        c.velY -= drag * c.velY;
    }
    if (mode)
        player.move_vert();

    glutPostRedisplay();
    // cout << "Animating...\n";
    glutTimerFunc(16, animate_keyboard, 0);
} // 60 FPS !!!

void mouse_move(int x, int y)
{
    // cout << "Mouse move: " << x << "," << y << endl;
    int deltaX = x - xPos, deltaY = y - yPos;
    xPos = x, yPos = y;
    if (abs(deltaX) < 100 && abs(deltaY) < 100)
    {
        k.mouse_wheel[1].velY -= deltaX * 0.05;
        k.mouse_wheel[0].velX -= deltaY * 0.05;
    }
    cout << "MODE=" << mode << endl;
    if (mode)
    {
        // deltaX = zoomX - x;
        // deltaY = zoomY - y;
        player.angHor += deltaX;
        double final = player.angHeight + deltaY;
        if (final > 0 && final < 180)
        {
            player.angHeight = final;
        }
        // zoomX = x;
        // zoomY = y;
    }
    cout << player.angHeight << " " << player.angHor << endl;
}

//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Teclado Gaming: WASD");

    k = Keyboard();

    // cout << "Point length: " << k.pts.size() << "; colour length: " << k.colours.size() << endl;
    inicializa();
    // cu = Cuboid(point3d(0, 0, 0), 1, 1, 1, GREY);
    // cu.draw();
    // glutSwapBuffers();
    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse_move);
    glutMotionFunc(adjust_angle);
    glutMouseFunc(zoom_wheel);
    glutTimerFunc(16, animate_keyboard, 0);
    glutMainLoop();

    return 0;
}
