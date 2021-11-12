/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Meta 1 do Projeto
    Autor: Paulo Cortesão, 2019216517
======================================================================================= */
#ifndef POLYGON_H
#define POLYGON_H
#include "point.h"
#include "colour.h"
#include "geoTransform.h"
#include <vector>
#include <iostream>
#include <cstdarg>
using namespace std;
struct Polygon
{
    vector<point3d> points;
    vector<colour4> colours;
    vector<GeoTransform<GLfloat>> transform;
    void draw()
    {
        for (int i = transform.size() - 1; i >= 0; i--)
            transform[i].apply();
        glBegin(GL_POLYGON);
        for (int i = 0; i < points.size(); i++)
        {
            auto c = colours[i];
            auto p = points[i];
            // cout << "r=" << c.r << ";g=" << c.g << ";b=" << c.b << ";a=" << c.a << endl;
            glColor4f(c.r, c.g, c.b, c.a);
            glVertex3d(p.x, p.y, p.z);
        }
        auto c = colours[0];
        glColor4f(c.r, c.g, c.b, c.a); // colour loop
        glEnd();
    }

    void addFunction(func_code code, vector<GLfloat> args)
    {
        GeoTransform<GLfloat> g(code, args);
        transform.push_back(g);
    }

    Polygon(vector<point3d> &points, vector<colour4> &colours) : points(points), colours(colours)
    {
        // draw();
    }

    Polygon(vector<point3d> &points, colour4 colour) : points(points), colours(points.size(), colour)
    {
        // draw();
    }

    Polygon(vector<point3d> &points) : points(points), colours(points.size(), {1, 1, 1, 1})
    {
        // draw();
    }
    Polygon() {}
};

#endif
