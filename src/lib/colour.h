/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Meta 1 do Projeto
    Autor: Paulo Cortesão, 2019216517
======================================================================================= */
#ifndef COLOUR_H
#define COLOUR_H
#include <GL/glut.h>
// #define min(a, b) ((a) < (b) ? (a) : (b))
#include <bits/stdc++.h>
using namespace std;
struct colour4
{
    GLdouble r, g, b, a;
    colour4(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : r(r), g(g), b(b), a(a) {}
};

struct colour3 : public colour4
{
    colour3(GLfloat r, GLfloat g, GLfloat b) : colour4(r, g, b, 1.0) {}
};

colour4 light(colour4 c)
{
    GLdouble r = min(1.5 * c.r, 1.0), g = min(1.5 * c.g, 1.0), b = min(1.5 * c.b, 1.0);
    return colour4(r, g, b, c.a);
}

colour4 dark(colour4 c)
{
    GLdouble r = c.r / 2, g = c.g / 2, b = c.b / 2;
    return colour4(r, g, b, c.a);
}

const colour4 RED = colour4(1, 0, 0, 1);
const colour4 GREEN = colour4(0, 1, 0, 1);
const colour4 BLUE = colour4(0, 0, 1, 1);
const colour4 WHITE = colour4(1, 1, 1, 1);
const colour4 BLACK = colour4(0, 0, 0, 1);
const colour4 MAGENTA = colour4(1, 0, 1, 1);
const colour4 CYAN = colour4(0, 1, 1, 1);
const colour4 YELLOW = colour4(1, 1, 0, 1);
const colour4 GREY = colour4(0.5, 0.5, 0.5, 1);
const colour4 ORANGE = colour4(1, 0.5, 0, 1);
#endif