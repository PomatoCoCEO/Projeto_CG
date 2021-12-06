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
#define XDIVS 10
#define YDIVS 10

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
        int cb = 0;
        for (auto &c : base)
        {
            cubes.push_back(c);
            c.vertex_array_pos = 24 * cb++;
        }
        for (auto &c : keys)
        {
            cubes.push_back(c);
            c.vertex_array_pos = 24 * cb++;
        }
        for (auto &w : mouse_wheel)
        {
            cubes.push_back(w);
            w.vertex_array_pos = 24 * cb++;
        }
        cout << "Cube length: " << cubes.size() << endl;

        for (auto &c : cubes)
        {
            c.vertex_array_pos = pts.size();
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
        cout << "Boo\n";
        base.push_back(Cuboid(point3d(0.0, 0.0, 0.0), 28.0, 15.0, 2.0, dark(GREY), &materials[0], &textures[0], XDIVS, YDIVS));
        base.emplace_back(point3d(15.5, 8.5, 1), 1, 1, 4, GREY, &materials[5], nullptr, XDIVS, YDIVS);
        base.emplace_back(point3d(25.5, 8.5, 1), 1, 1, 4, GREY, &materials[7], nullptr, XDIVS, YDIVS);
        base.emplace_back(point3d(21.5, 8.5, 5), 5, 1, 1, GREY, &materials[15], nullptr, 2 * XDIVS, 2 * YDIVS);
        base.emplace_back(point3d(-3, 0, 0), 3.0, 15.0, 2.0, GREY, &materials[26], nullptr, 2 * XDIVS, 2 * YDIVS);

        keys.emplace_back(point3d(2, 11, 1.5), 3, 3, 1, dark(YELLOW), 'W', &materials[2], nullptr, XDIVS, YDIVS);        // W
        keys.emplace_back(point3d(1, 7, 1.5), 3, 3, 1, dark(RED), 'A', &materials[1], nullptr, XDIVS, YDIVS);            // A
        keys.emplace_back(point3d(5, 7, 1.5), 3, 3, 1, dark(GREEN), 'S', &materials[11], nullptr, XDIVS, YDIVS);         // S
        keys.emplace_back(point3d(9, 7, 1.5), 3, 3, 1, dark(BLUE), 'D', &materials[4], nullptr, XDIVS, YDIVS);           // D
        keys.emplace_back(point3d(2, 2, 1.5), 11, 3, 1, dark(ORANGE), ' ', &materials[5 /*25*/], nullptr, XDIVS, YDIVS); // <SPACE>
        mouse_wheel.push_back(MouseCube(point3d(20, 7, 2 * sqrt(3.0f)), 4.0, 4.0, 4.0, dark(CYAN), &materials[0], &textures[2], XDIVS, YDIVS));
        mouse_wheel.push_back(MouseCube(point3d(14, 7, 2 * sqrt(3.0f)), 4.0, 4.0, 4.0, dark(MAGENTA), &materials[0], &textures[3], XDIVS, YDIVS));
        cout << "Boo2\n";
        // setup_draw();
    }

    void draw()
    {
        // base[0].m.apply();
        for (GLuint i = 0; i < base.size(); i++)
        {
            // base[i].m->apply();
            base[i].draw();
        }

        for (GLuint i = 0; i < keys.size(); i++)
        {
            // applyMaterial(keys[i].m);
            // keys[i].m.apply();
            glPushMatrix();
            glTranslatef(0, 0, keys[i].deltaZ);
            keys[i].draw();
            keys[i].drawLetter();
            glPopMatrix();
        }
        // cout << "Boo1\n";
        for (GLuint m = 0; m < mouse_wheel.size(); m++)
        {
            auto &c = mouse_wheel[m];
            // applyMaterial(c.m);
            c.m->apply();
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
            c.draw();
            glPopMatrix();
        }
    }
};

#endif