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
#include <vector>
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
int playerScore = 0;
Keyboard k;
Sphere sphere;
Cuboid cu;
Santa santa;
GLdouble key_speed = -0.02;
Light l2 = Light(GL_LIGHT1, point3d(-1, -1, -1), 1, WHITE, WHITE, WHITE, 0.01, 0.0001, 0);

//================================================================================
//=========================================================================== INIT
/*
vector<GLdouble> cuVertices = {
    0, 0, 0};*/
vector<GLdouble> cuVertices, cuColours;
vector<Skull> skulls;
vector<GLuint> vec = {0, 1, 3, 2};
int xPos, yPos;

void generateMosaic(int no_skulls, double radius_field);
void inicializa(void)
{
    glClearColor(0, 0, 0, 1); //������������������������������Apagar
    glEnable(GL_DEPTH_TEST);  //������������������������������Profundidade
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH); //������������������������������Interpolacao de cores
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    // cout << "Before textures\n";
    initTextures();
    generateMosaic(30, 30);
    // cout << "After textures\n";
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
    sphere.draw();
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

void drawMosaics()
{
    materials[26].apply();
    for (int i = 0; i < skulls.size(); i++)
    {
        // cout << i << endl;
        skulls[i].draw();
    }
    santa.draw();
}

void generateMosaic(int no_skulls, double radius_field)
{
    GLdouble minZ = -radius_field, maxZ = 20 + radius_field, minX = -2 - radius_field, maxX = radius_field;
    int noDivs = 100000;
    for (int i = 0; i <= no_skulls; i++)
    {
        int ra = rand() % noDivs;
        double p = (ra + 0.0) / (100000.0);
        GLdouble posX = minZ + p * (maxZ - minZ);
        ra = rand() % noDivs;
        p = (ra + 0.0) / (100000.0);
        GLdouble posZ = minZ + p * (maxZ - minZ);
        if (i < no_skulls)
            skulls.emplace_back(point3d(posX, 0, posZ), 1.0);
        else
            santa = Santa(point3d(posX, 0, posZ), 1);
    }
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, wScreen, hScreen); // VIEWPORT
    glMatrixMode(GL_PROJECTION);        // PROJECTION
    glLoadIdentity();
    gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // VISUALIZATION
    if (mode == 0)
    {
        auto posObs = point3d(
            xFocus + zoomRad * cos(DEG_TO_RAD(horAng)) * sin(DEG_TO_RAD(verAng)),
            yFocus + zoomRad * cos(DEG_TO_RAD(verAng)),
            zFocus + zoomRad * sin(DEG_TO_RAD(horAng)) * sin(DEG_TO_RAD(verAng)));
        point3d vecDir(-cos(DEG_TO_RAD(horAng)) * sin(DEG_TO_RAD(verAng)),
                       -cos(DEG_TO_RAD(verAng)),
                       -sin(DEG_TO_RAD(horAng)) * sin(DEG_TO_RAD(verAng)));
        gluLookAt(/*rVisao * cos(PI / 2 * aVisao), yCam, rVisao * sin(PI / 2 * aVisao)*/
                  posObs.x,
                  posObs.y,
                  posObs.z,
                  xFocus, yFocus, zFocus, 0, 1, 0);
        // lights
        Light l1 = Light(GL_LIGHT0, posObs, 1.0f, WHITE, WHITE, WHITE, 0.01, 0.006, 0.00, vecDir, 0.2, 45);
    }
    else
    {
        point3d p = player.pos;
        point3d vecDir(cos(DEG_TO_RAD(player.angHorView)) * sin(DEG_TO_RAD(player.angHeightView)),
                       cos(DEG_TO_RAD(player.angHeightView)),
                       sin(DEG_TO_RAD(player.angHorView)) * sin(DEG_TO_RAD(player.angHeightView)));
        // cout << p.x << " " << p.y << " " << p.z << endl;
        point3d dir = p + vecDir;
        gluLookAt(/*rVisao * cos(PI / 2 * aVisao), yCam, rVisao * sin(PI / 2 * aVisao)*/
                  p.x,
                  p.y,
                  p.z,
                  dir.x, dir.y, dir.z, 0, 1, 0);
        // LIGHTS
        Light l1 = Light(GL_LIGHT0, p, 1.0f, WHITE, WHITE, WHITE, 0.01, 0.1, 0, vecDir, 0, 10);
    }
    if (l2.on)
    {
        auto s = l2.mult;
        l2 = Light(GL_LIGHT1, point3d(-10, -10, -10), 1, WHITE, WHITE, WHITE, 0.5, 0.0001, 0);
        l2.mult = s;
        l2.apply();
    }
    // Light l3(GL_LIGHT2, point3d(5, 5, 5), 1, WHITE, WHITE, WHITE, 0.1, 0, 0.03, point3d(-1, -1, 1), 0, 30);
    // cout << "Before drawing" << endl;
    drawEixos();
    drawScene();
    drawMosaics();
    drawPlayer();
    // cout << "Before drawing mosaics" << endl;

    // cout << "After drawing" << endl;
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
    case 'F':
        // cout << "F pressed \n";
        for (int i = 0; i < k.walls.size(); i++)
        {
            k.walls[i].fall();
        }
        break;
    case 'O':
        l2.toggle();
        break;
    case 'R':
        l2.turn_red();
        break;
    case 'G':
        cout << "toggling l2\n";
        l2.turn_green();
        break;
    case 'B':
        cout << "toggling l2\n";
        l2.turn_blue();
        break;
    case 'H':
        cout << "toggling l2\n";
        l2.turn_white();
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
    case '<':
        // cout << "Before: " << materials[0].shininess << endl;
        materials[0].alterShininess();
        // cout << "After: " << materials[0].shininess << endl;
        break;
    case 27:
        cout << "SCORE: " << playerScore << endl;
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
    // cout << "zoomRatio = " << zoomRatio << "\n";
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

void writeStringOnScreen(string string)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1, 1, 1);
    glRasterPos2d(0.10 * wScreen, 0.80 * hScreen);
    for (int i = 0; i < string.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
    glutSwapBuffers();
}

void animate_keyboard(int time)
{
    // handle key pressing
    if (player.pos.y <= 1 && player.velVert <= 0)
    {
        auto &ps = player.pos;
        for (int i = 0; i < skulls.size(); i++)
        {
            auto &s = skulls[i].center;
            if (__hypot3(ps.x - s.x, ps.y - s.y, ps.z - s.z) <= sqrt(2.0))
            {
                auto aid = player.mov;
                // writeStringOnScreen("GAME OVER! You touched a Skull\n");
                cout << "You touched a SKULL! Score -1!\n";
                playerScore--;
                player = Player(point3d(20, 1, 20));
                player.mov = aid;
                for (int i = 0; i < k.walls.size(); i++)
                {
                    k.walls[i].reset();
                }
                generateMosaic(30, 30);

                // getchar();
                // exit(1);
            }
        }
        auto &ss = santa.center;
        if (__hypot3(ps.x - ss.x, ps.y - ss.y, ps.z - ss.z) <= sqrt(2.0))
        {
            cout << "Congrats! You discovered Santa!\n";
            auto aid = player.mov;
            playerScore += 10;
            player = Player(point3d(20, 1, 20));
            player.mov = aid;
            for (int i = 0; i < k.walls.size(); i++)
            {
                k.walls[i].reset();
            }
            generateMosaic(30, 30);
            // getchar();
            // exit(0);
        }
    }
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
        player.angHorView += deltaX / ((wScreen + 0.0) / 360.0);
        double final = player.angHeightView + deltaY / ((hScreen + 0.0) / 270.0);
        if (final > 0 && final < 180)
        {
            player.angHeightView = final;
        }
        // zoomX = x;
        // zoomY = y;
    }
}

//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char **argv)
{
    cout << "Main1\n";
    glutInit(&argc, argv);
    cout << "Main2\n";
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    cout << "Main3\n";
    glutInitWindowSize(wScreen, hScreen);
    cout << "Main4\n";
    glutInitWindowPosition(300, 100);
    cout << "Main5\n";

    glutCreateWindow("Teclado Gaming: WASD");
    cout << "Main6\n";

    inicializa();
    cout << "Main7\n";

    k = Keyboard();
    sphere = Sphere(100, 100, 100, &textures[7]);
    cout << "After Constructor\n";
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
