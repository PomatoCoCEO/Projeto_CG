/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Meta 1 do Projeto
    Autor: Paulo Cortesão, 2019216517
======================================================================================= */
#ifndef MOUSE_CUBE_H
#define MOUSE_CUBE_H
#include "../cg-lib.h"

class MouseCube : public Cuboid
{

public:
    GLdouble angX = 0,
             angY = 0, velX = 0, velY = 0;
    MouseCube() {}
    MouseCube(point3d base, GLdouble x, GLdouble y, GLdouble z, colour4 colour) : Cuboid(base, x, y, z, colour)
    {
    }
};
#endif