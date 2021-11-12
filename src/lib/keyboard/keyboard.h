/* ===================================================================================
    Departamento Eng. Informatica - FCTUC
    Computacao Grafica - 2021/22
    Meta 1 do Projeto
    Autor: Paulo Cortesão, 2019216517
======================================================================================= */
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../cg-lib.h"
#include "key.h"
#include "mouse_cube.h"

class Keyboard
{
public:
    vector<Cuboid> base;
    vector<Key> keys;
    vector<MouseCube> mouse_wheel;
    vector<GLdouble> pts;
    vector<GLdouble> colours;
    void setup_draw()
    {
        pts.clear();
        vector<Cuboid> cubes;
        for (auto c : base)
            cubes.push_back(c);
        for (auto c : keys)
            cubes.push_back(c);
        for (auto &w : mouse_wheel)
            cubes.push_back(w);
        cout << "Cube length: " << cubes.size() << endl;

        for (auto &c : cubes)
        {
            for (auto &f : c.faces)
            {
                for (size_t i = 0; i < f.points.size(); i++)
                {
                    auto p = f.points[i];
                    pts.push_back(p.x);
                    pts.push_back(p.y);
                    pts.push_back(p.z);
                    auto c = f.colours[i];
                    colours.push_back(c.r);
                    colours.push_back(c.g);
                    colours.push_back(c.b);
                    colours.push_back(c.a);
                    // colors.push_back(f.colours[i].)
                }
            }
        }
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, &pts[0]);
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_DOUBLE, 0, &colours[0]);
        /* for(auto& f: base.faces) {
            for(auto& p: f.points) {
                pts.push_back(p);
            }
        } */
    }

    Keyboard()
    {
        base.push_back(Cuboid(point3d(0.0, 0.0, 0.0), 28.0, 15.0, 2.0, dark(GREY)));
        base.emplace_back(point3d(15.5, 8.5, 1), 1, 1, 4, GREY);
        base.emplace_back(point3d(25.5, 8.5, 1), 1, 1, 4, GREY);
        base.emplace_back(point3d(21.5, 8.5, 5), 5, 1, 1, GREY);

        keys.emplace_back(point3d(2, 11, 1.5), 3, 3, 1, dark(YELLOW), 'W'); // W
        keys.emplace_back(point3d(1, 7, 1.5), 3, 3, 1, dark(RED), 'A');     // A
        keys.emplace_back(point3d(5, 7, 1.5), 3, 3, 1, dark(GREEN), 'S');   // S
        keys.emplace_back(point3d(9, 7, 1.5), 3, 3, 1, dark(BLUE), 'D');    // D
        keys.emplace_back(point3d(2, 2, 1.5), 11, 3, 1, dark(ORANGE), ' ');
        mouse_wheel.push_back(MouseCube(point3d(20, 7, 2 * sqrt(3.0f)), 4.0, 4.0, 4.0, dark(CYAN)));
        mouse_wheel.push_back(MouseCube(point3d(14, 7, 2 * sqrt(3.0f)), 4.0, 4.0, 4.0, dark(MAGENTA)));

        setup_draw();
    }

    void draw()
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, &pts[0]);
        for (GLuint i = 0; i < base.size(); i++)
        {

            for (GLuint j = 0; j < 24; j += 4) // base
            {
                GLuint k = 24 * i + j;
                vector<GLuint> vec = {k, k + 1, k + 2, k + 3};
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
            }
        }
        for (GLuint i = 0; i < keys.size(); i++)
        {
            glPushMatrix();
            glTranslatef(0, 0, keys[i].deltaZ);
            for (GLuint j = 0; j < 24; j += 4)
            {
                GLuint k = 24 * (i + base.size()) + j;
                vector<GLuint> vec = {k, k + 1, k + 2, k + 3};
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
            }
            keys[i].drawLetter();
            glPopMatrix();
        }
        // cout << "Boo1\n";
        for (GLuint m = 0; m < mouse_wheel.size(); m++)
        {
            auto &c = mouse_wheel[m];
            // cout << "Boo2\n";
            auto p1 = c.faces[0].points[0], p2 = c.faces[2].points[2];
            glPushMatrix();

            glTranslatef((p1.x + p2.x) / 2, (p1.y + p2.y) / 2, (p1.z + p2.z) / 2);
            double angX = c.angX, angY = c.angY;
            double totAng = sqrt(angX * angX + angY * angY);
            glRotatef(totAng, angY, 0, angX);
            // glRotatef(mouse_wheel.angX, 1, 0, 0);
            // glRotatef(mouse_wheel.angY, 0, 1, 0);
            // glRotatef()
            glTranslatef(-(p1.x + p2.x) / 2, -(p1.y + p2.y) / 2, -(p1.z + p2.z) / 2);
            for (GLuint i = 24 * (base.size() + keys.size() + m) /*pts.size() - 24*/; i < 24 * (m + 1 + base.size() + keys.size()); i += 4)
            {
                vector<GLuint> vec = {i, i + 1, i + 2, i + 3};
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
            }
            glPopMatrix();
        }
    }
};

#endif