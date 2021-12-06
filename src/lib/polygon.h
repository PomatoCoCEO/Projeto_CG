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
#include "textures/textures.h"
#include <vector>
#include <iostream>
#include <cstdarg>
using namespace std;
struct Polygon
{
    point3d normal;
    vector<point3d> points;
    vector<colour4> colours;
    vector<GeoTransform<GLfloat>> transform;
    Texture *text = NULL;
    void draw()
    {
        for (int i = transform.size() - 1; i >= 0; i--)
            transform[i].apply();
        glNormal3d(normal.x, normal.y, normal.z);
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

    Polygon(vector<point3d> &points, vector<colour4> &colours, point3d normal, Texture *text = nullptr) : points(points), colours(colours), normal(normal), text(text)
    {
        // draw();
    }

    Polygon(vector<point3d> &points, colour4 colour, point3d normal, Texture *text = nullptr) : points(points), colours(points.size(), colour), text(text)
    {
        // draw();
    }

    Polygon(vector<point3d> &points, point3d normal, Texture *text = nullptr) : points(points), colours(points.size(), {1, 1, 1, 1}), text(text)
    {
        // draw();
    }
    Polygon() {}
};

#endif
