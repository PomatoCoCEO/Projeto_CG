/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Meta 1 do Projeto
    Autor: Paulo Cortesão, 2019216517
    FICHEIRO PRINCIPAL
    Execução: no presente diretório, escrever o seguinte comando no terminal:
    ./glut++.sh keyboard.cpp remote && ./remote
    O código foi elaborado no sistema operativo Linux
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
GLdouble key_speed = -0.02;
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

void drawPlayer()
{
    glPushMatrix();
    glTranslatef(player.pos.x, player.pos.y, player.pos.z);
    glColor3f(1, 1, 0);
    glutWireSphere(1, 10, 10);
    glPopMatrix();
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
        // cout << p.x << " " << p.y << " " << p.z << endl;
        point3d dir(p.x + cos(DEG_TO_RAD(player.angHorView)) * sin(DEG_TO_RAD(player.angHeightView)),
                    p.y + cos(DEG_TO_RAD(player.angHeightView)),
                    p.z + sin(DEG_TO_RAD(player.angHorView)) * sin(DEG_TO_RAD(player.angHeightView)));
        gluLookAt(/*rVisao * cos(PI / 2 * aVisao), yCam, rVisao * sin(PI / 2 * aVisao)*/
                  p.x,
                  p.y,
                  p.z,
                  dir.x, dir.y, dir.z, 0, 1, 0);
        // printf("(%lf,%lf,%lf) looking at (%lf, %lf, %lf)\n", p.x, p.y, p.z, dir.x, dir.y, dir.z);
    }
    //================================================================= N�o modificar !!!!!!!!!!!!

    //����������������������������������������������������������Objectos
    drawEixos();
    drawScene();
    drawPlayer();

    //. . . . . . . . . . . . . . . . . . . . .  Actualizacao
    glutSwapBuffers();
}

void press_key(int pos_key)
{
    // cout << "Key pressed: " << pos_key << endl;
    k.keys[pos_key].pressed = true;
    if (k.keys[pos_key].deltaZ > -0.4)
        k.keys[pos_key].velZ = key_speed; // press down
    // else
    //    k.keys[pos_key].velZ = 0.02;
}

void keyboardUp(unsigned char key, int x, int y)
{
    switch (toupper(key))
    {
    case 'W':
        k.keys[0].pressed = false;
        // if (mode)
        player.mov -= point3d(1, 0, 0); // move_front();
        break;
    case 'A':
        k.keys[1].pressed = false;
        // if (mode)
        player.mov -= point3d(0, 0, -1);
        break;
    case 'S':
        k.keys[2].pressed = false;
        // if (mode)
        player.mov -= point3d(-1, 0, 0);
        break;
    case 'D':
        k.keys[3].pressed = false;
        // if (mode)
        player.mov -= point3d(0, 0, 1);
        break;
    case ' ':
        k.keys[4].pressed = false;
    default:
        break;
    }
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{
    switch (toupper(key))
    {
    case 'W':
        press_key(0);
        // if (mode)
        player.mov += point3d(1, 0, 0); // move_front();
        break;
    case 'A':
        press_key(1);
        // if (mode)
        player.mov += point3d(0, 0, -1);
        break;
    case 'S':
        press_key(2);
        // if (mode)
        player.mov += point3d(-1, 0, 0);
        break;
    case 'D':
        press_key(3);
        // if (mode)
        player.mov += point3d(0, 0, 1);
        break;
    case 'P':
        mode = 1 - mode;
        break;
    case ' ':
        press_key(4);
        // if (mode)
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

    // cout << "(x,y,z) = (" << xFocus << "," << yFocus << "," << zFocus << ")\n";
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
        // cout << "VelZ: " << k.keys[i].velZ << "; DeltaZ:" << k.keys[i].deltaZ << endl;
        /*if (k.keys[i].deltaZ < -0.4 && k.keys[i].velZ < 0)
            k.keys[i].velZ = -k.keys[i].velZ;*/
        if (k.keys[i].pressed)
        {
            if (k.keys[i].deltaZ < -0.4)
                k.keys[i].velZ = 0;
            if (k.keys[i].letter == ' ')
                player.jump();
        }
        else
        {
            // cout << "Key" << k.keys[i].letter << "not pressed" << endl;
            if (k.keys[i].deltaZ <= -0.399)
                k.keys[i].velZ = -key_speed;
            else
            {
                if (k.keys[i].deltaZ > 0.001)
                    k.keys[i].deltaZ = k.keys[i].velZ = 0;
            }
        }
    }
    for (auto &c : k.mouse_wheel)
    {
        c.angX += c.velY;
        c.angY -= c.velX;
        GLdouble drag = 0.02;
        c.velX -= drag * c.velX;
        c.velY -= drag * c.velY;
    }
    // if (mode)
    player.move();

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
    // cout << "MODE=" << mode << endl;
    if (mode)
    {
        // deltaX = zoomX - x;
        // deltaY = zoomY - y;
        player.angHorView += deltaX / 5.0;
        double final = player.angHeightView + deltaY / 5.0;
        if (final > 0 && final < 180)
        {
            player.angHeightView = final;
        }
        // zoomX = x;
        // zoomY = y;
    }
    cout << player.angHeightView << " " << player.angHorView << endl;
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

    inicializa();
    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouse_move);
    glutMotionFunc(adjust_angle);
    glutMouseFunc(zoom_wheel);
    glutTimerFunc(16, animate_keyboard, 0);
    glutMainLoop();

    return 0;
}
