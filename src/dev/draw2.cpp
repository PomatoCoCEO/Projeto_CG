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
#include "../lib/keyboard.h"
using namespace std;
#define reveal(a) cout << #a "=" << a << endl;

//--------------------------------- Definir cores
#define BLUE 0.0, 0.0, 1.0, 1.0
#define RED 1.0, 0.0, 0.0, 1.0
#define YELLOW 1.0, 1.0, 0.0, 1.0
#define GREEN 0.0, 1.0, 0.0, 1.0
#define WHITE 1.0, 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0, 1.0
#define PI 3.14159

//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam = 0.5;
GLdouble xTable = 0.0, yTable = 0.0, xCam = 4, yCam = 10, zCam = 30;
GLboolean up = false;
int deg = 0;
GLdouble deltaAng = 5.0;
/*static*/ vector<GLfloat> vertices = {
    //�������������������������������������� x=tam (Esquerda)
    -tam, -tam, tam,  // 0
    -tam, tam, tam,   // 1
    -tam, tam, -tam,  // 2
    -tam, -tam, -tam, // 3
                      //�������������������� Direita
    tam, -tam, tam,   // 4
    tam, tam, tam,    // 5
    tam, tam, -tam,   // 6
    tam, -tam, -tam,  // 7
                      //��������������������� (Cima
    -tam, tam, tam,   // 8
    -tam, tam, -tam,  // 9
    tam, tam, -tam,   // 10
    tam, tam, tam,    // 11
};
/*
static GLfloat normais[] = {
    //�������������������������������������� x=tam (Esquerda)
    -1.0,
    0.0,
    0.0,
    -1.0,
    0.0,
    0.0,
    -1.0,
    0.0,
    0.0,
    -1.0,
    0.0,
    0.0,
    //�������������������������������������� x=tam (Direita)
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    //�������������������������������������� y=tam (Cima)
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
};*/
//------------------------------------------------------------ Cores
static GLfloat cor[] = {
    0.5, 0.0, 1.0, 0.5, 0.0, 1.0,
    0, 1, 1, 0, 1, 1,
    0, 1, 0, 0, 1, 0,
    0, 1, 1, 0, 1, 1,
    1, 0, 0, 1, 0, 0,
    1, 1, 0, 1, 1, 0};
// nao est� feito !!
// falta fazer

//=========================================================== FACES DA MESA
GLint frenteVisivel = 1;
vector<GLuint> cima = {8, 11, 10, 9};    // regra da mao direita
static GLuint direita[] = {4, 5, 6, 7};  //++++++++++++ falta a esquerda
static GLuint esquerda[] = {0, 1, 2, 3}; //++++++++++++ falta a direita

//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint wScreen = 800, hScreen = 600;      //.. janela (pixeis)
GLfloat xC = 10.0, yC = 10.0, zC = 10.0; //.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador
GLfloat rVisao = 10, aVisao = 90, incVisao = 0.05;
GLfloat obsP[] = {rVisao * cos(aVisao), 3.0, rVisao *sin(aVisao)};
GLfloat angZoom = 45;
GLfloat incZoom = 3;

//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
    glClearColor(BLACK);     //������������������������������Apagar
    glEnable(GL_DEPTH_TEST); //������������������������������Profundidade
    glShadeModel(GL_SMOOTH); //������������������������������Interpolacao de cores

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]); //���������������VertexArrays: vertices + normais + cores
    glEnableClientState(GL_VERTEX_ARRAY);
    // glNormalPointer(GL_FLOAT, 0, normais);
    // glEnableClientState(GL_NORMAL_ARRAY);
    //++++++++++++++++++++++++ cores ??
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cor);
}

void drawEixos()
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
    glColor4f(RED);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(10, 0, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 10, 0);
    glEnd();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
    glColor4f(BLUE);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 10);
    glEnd();
}

void drawScene()
{

    //=================================================== Qual o lado visivel ???
    /*switch (frenteVisivel)
    {
     case 0:
         glDisable(GL_CULL_FACE);
         break;
     case 1:
         glEnable(GL_CULL_FACE);
         glCullFace(GL_BACK);
         break;
     default:
         glEnable(GL_CULL_FACE);
         glCullFace(GL_FRONT);
     }*/
    //++++++++++++++++++++   falta fazer

    //==================================== MESA
    //++++++++++++++++++   ?? escala, rotacao, translacao ??
    Keyboard k = Keyboard();
    // glPushMatrix();
    // glScalef(-1, 1, 1);
    k.draw();
    //  glPopMatrix();
    /*glTranslatef(xTable, yTable, 0);
    glRotatef(deg, 0, 1, 0);
    glPushMatrix();
    glScalef(2, 2, 2);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &cima[0]); // desenhar uma das faces da mesa
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);  //+++++++++++++++++ face esquerda
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda); //+++++++++++++++++ face direita
    glPopMatrix();

    //==================================== Chaleira Amarela
    glColor4f(YELLOW);
    glPushMatrix();
    //+++++++++++++++++++++ escala, rotacao, translacao ??
    glutWireTeapot(1);
    glPopMatrix();*/
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
    gluLookAt(/*rVisao * cos(PI / 2 * aVisao), yCam, rVisao * sin(PI / 2 * aVisao)*/ xCam, yCam, zCam, 5, 2, 10, 0, 1, 0);
    //================================================================= N�o modificar !!!!!!!!!!!!

    //����������������������������������������������������������Objectos
    drawEixos();
    drawScene();

    //. . . . . . . . . . . . . . . . . . . . .  Actualizacao
    glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{

    switch (toupper(key))
    {
    //++++++++++++++++++++++++++++  TECLAS
    //  F		lado da frente ou de tras visivel
    case 'F':
        frenteVisivel = (frenteVisivel + 1) % 3;
        reveal(frenteVisivel) break;
    case 'A':
        xTable += 0.1;
        reveal(xTable) break;
    case 'S':
        xTable -= 0.1;
        reveal(xTable) break;
        //  A/S		movimeto eixo x
        //	E/D		rodar esquerda/direita
        //	R		rar continuamente
        //++++++++++++++++++++++++++++  TECLAS
    case 'R':
        deg = (deg + 5) % 360;
        if (up)
        {
            yTable += 0.1;
        }
        else
        {
            yTable -= 0.1;
        }
        if (yTable >= 10.0)
            up = false;
        if (yTable <= 0)
            up = true;
        break;
        //++++++++++++++++++++++++++++
        // E possivel inventar outra coisa qualquer !!!

        //--------------------------- Escape
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
    cout << "(x,y,z) = (" << xCam << "," << yCam << "," << zCam << ")\n";
    glutPostRedisplay();
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

    inicializa();

    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
