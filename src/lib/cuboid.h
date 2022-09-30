/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Meta 1 do Projeto
    Autor: Paulo Cortesão, 2019216517
======================================================================================= */
#ifndef CUBOID_H
#define CUBOID_H
#include <GL/glut.h>
#include <iostream>
#include "rectangle.h"
#include "geoTransform.h"
#include "material/material.h"
#include <vector>
#define LSOne(s) ((s) & (-(s)))
using namespace std;

// point3d, color3

class Solid
{
public:
    vector<Rectangle> faces;
    int vertex_array_pos = 0;
};

class Cuboid : public Solid
{

public:
    vector<GLdouble> points;
    vector<GLdouble> colors;
    int xDivs = 1, yDivs = 1;
    material *m;
    Texture *tex = nullptr;
    Cuboid() {}
    Cuboid(point3d base, GLdouble x, GLdouble y, GLdouble z, colour4 colour, material *m, Texture *tex = nullptr, int xDivs = 1, int yDivs = 1) : m(m), tex(tex), xDivs(xDivs), yDivs(yDivs)
    {
        vector<GLdouble> vec1 = {x, y, z}; // vec2 = {base.x, base.y, base.z};
        // points
        vector<point3d> pts = {};
        for (int i = 0; i < (1 << 3); i++)
        {
            vector<GLdouble> pt = {0, 0, 0};
            int j = i;
            while (j > 0)
            {
                int f = LSOne(j);
                int pos = __builtin_ctz(f);
                pt[pos] += vec1[pos];
                j -= f;
            }
            point3d add = base + point3d(pt[0], pt[1], pt[2]);
            pts.push_back(add);
        }
        // faces
        vector<point3d> pol = {pts[0], pts[1], pts[3], pts[2]};
        faces.emplace_back(pol, light(colour), point3d(0, 0, -1), tex, xDivs, yDivs);
        pol = {pts[0], pts[2], pts[6], pts[4]};
        faces.emplace_back(pol, dark(colour), point3d(-1, 0, 0), tex, xDivs, yDivs);
        pol = {pts[1], pts[3], pts[7], pts[5]};
        faces.emplace_back(pol, dark(colour), point3d(1, 0, 0), tex, xDivs, yDivs);
        pol = {pts[4], pts[5], pts[7], pts[6]};
        faces.emplace_back(pol, light(colour), point3d(0, 0, 1), tex, xDivs, yDivs);
        pol = {pts[0], pts[1], pts[5], pts[4]};
        faces.emplace_back(pol, colour, point3d(0, -1, 0), tex, xDivs, yDivs);
        pol = {pts[2], pts[3], pts[7], pts[6]};
        faces.emplace_back(pol, colour, point3d(0, 1, 0), tex, xDivs, yDivs);
        cout << "First face data: " << faces[0].xDivs << "," << faces[0].yDivs << endl;
        for (auto f : faces)
        {
            for (auto p : f.points)
                points.push_back(p.x), points.push_back(p.y), points.push_back(p.z);
            for (auto c : f.colours)
                colors.push_back(c.r), colors.push_back(c.g), colors.push_back(c.b), colors.push_back(c.a);
        }
        // glVertexPointer(3, GL_DOUBLE, 0, &points[0]);
        // glColorPointer(4, GL_DOUBLE, 0, &colors[0]);

        cout << "Point length: " << points.size() << "; colour length: " << colors.size() << endl;
    }

    void addFunction(func_code code, vector<GLfloat> args)
    {
        /*GeoTransform<GLfloat> g(code, args);
        transform.push_back(g);*/
        for (auto &f : faces)
            f.addFunction(code, args);
    }

    void draw()
    {

        // applyMaterial(m);
        m->apply();
        // cout << "first component: " << m->amb[0] << " " << m->amb[1] << " " << m->amb[2] << " " << m->amb[3] << " " << m->diff[0] << " " << m->diff[1] << " " << m->diff[2] << " "
        //    << m->spec[0] << " " << m->spec[1] << " " << m->spec[2] << " " << m->spec[3] << " " << endl;
        for (int i = 0; i < faces.size(); i++)
        {
            faces[i].draw();
        }
    }
    /*
    void draw()
    {
        for (GLuint i = 0; i < 24; i += 4) // base
        {
            vector<GLuint> vec = {i, i + 1, i + 2, i + 3};
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
        }
    }*/
};

#endif