/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Meta 1 do Projeto
    Autor: Paulo Cortesão, 2019216517
======================================================================================= */
#ifndef KEY_H
#define KEY_H
#include "../cg-lib.h"
class Key : public Cuboid
{
public:
    GLdouble velZ = 0, deltaZ = 0;
    char letter;
    bool pressed = false;
    Key() {}
    Key(point3d base, GLdouble x, GLdouble y, GLdouble z, colour4 colour, char letter, material *m, Texture *tex = nullptr, int xDivs = 1, int yDivs = 1) : Cuboid(base, x, y, z, colour, m, tex, xDivs, yDivs), letter(letter)
    {
    }
    void drawLetter()
    {
        glColor4f(0, 0, 0, 1);
        point3d aid = faces[0].points[0], aid2 = faces[2].points[3];
        glRasterPos3d(aid.x + 0.5, aid.y + 0.5, aid2.z + 0.01);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
};
#endif