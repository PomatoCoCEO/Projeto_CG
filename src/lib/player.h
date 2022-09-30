/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Meta 1 do Projeto
    Autor: Paulo Cortesão, 2019216517
======================================================================================= */
#include "cg-lib.h"
#define fac 0.2
#define g 0.1
class Player
{
public:
    point3d pos, mov;
    double velVert = 0, velHor = 0;
    double angHeightView = 90, angHorView = -90;

    Player(point3d pos) : pos(pos)
    {
    }

    void move_vert()
    {
        if (pos.y < 1)
        {
            pos.y = 1;
            velVert = 0;
        }
        if (pos.y > 1)
        {
            point3d aid(0, velVert, 0);
            pos += aid;
            velVert -= g;
        }
    }

    void move()
    {
        // cout << "mov=" << mov << endl;
        if (mov.norm() != 0)
        {
            auto m = mov.normalized();
            double ang = DEG_TO_RAD(angHorView);
            point3d aid(fac * (m.x * cos(ang) - m.z * sin(ang)), 0, fac * (m.x * sin(ang) + m.z * cos(ang)));
            pos += aid;
        }
        move_vert();
    }

    void move_front()
    {
        point3d aid(fac * cos(DEG_TO_RAD(angHorView)), 0, fac * sin(DEG_TO_RAD(angHorView)));
        pos += aid;
        move_vert();
    }
    void move_back()
    {
        point3d aid(-fac * cos(DEG_TO_RAD(angHorView)), 0, -fac * sin(DEG_TO_RAD(angHorView)));
        pos += aid;
        move_vert();
    }
    void move_left()
    {
        point3d aid(fac * sin(DEG_TO_RAD(angHorView)), 0, -fac * cos(DEG_TO_RAD(angHorView)));
        pos += aid;
        move_vert();
    }
    void move_right()
    {
        point3d aid(-fac * sin(DEG_TO_RAD(angHorView)), 0, fac * cos(DEG_TO_RAD(angHorView)));
        pos += aid;
        move_vert();
    }
    void jump()
    {
        if (pos.y <= 1)
        {
            pos.y = 1.0001;
            velVert = 1.5;
        }
    }
};