#ifndef CUBOID_H
#define CUBOID_H
#include <GL/glut.h>
#include <iostream>
#include "polygon.h"
#include "geoTransform.h"
#include <bits/stdc++.h>
#define LSOne(s) ((s) & (-(s)))
using namespace std;

// point3d, color3

class Solid
{
public:
    vector<Polygon> faces;
};

class Cuboid : public Solid
{

public:
    vector<GLdouble> points;
    vector<GLdouble> colors;
    Cuboid() {}
    Cuboid(point3d base, GLdouble x, GLdouble y, GLdouble z, colour4 colour)
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
        faces.emplace_back(pol, light(colour));
        pol = {pts[0], pts[2], pts[6], pts[4]};
        faces.emplace_back(pol, dark(colour));
        pol = {pts[1], pts[3], pts[7], pts[5]};
        faces.emplace_back(pol, dark(colour));
        pol = {pts[4], pts[5], pts[7], pts[6]};
        faces.emplace_back(pol, light(colour));
        pol = {pts[0], pts[1], pts[5], pts[4]};
        faces.emplace_back(pol, colour);
        pol = {pts[2], pts[3], pts[7], pts[6]};
        faces.emplace_back(pol, colour);
        for (auto f : faces)
        {
            for (auto p : f.points)
                points.push_back(p.x), points.push_back(p.y), points.push_back(p.z);
            for (auto c : f.colours)
                colors.push_back(c.r), colors.push_back(c.g), colors.push_back(c.b), colors.push_back(c.a);
        }
        glVertexPointer(3, GL_DOUBLE, 0, &points[0]);
        glColorPointer(4, GL_DOUBLE, 0, &colors[0]);

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
        for (GLuint i = 0; i < 24; i += 4) // base
        {
            vector<GLuint> vec = {i, i + 1, i + 2, i + 3};
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
        }
    }
};

#endif