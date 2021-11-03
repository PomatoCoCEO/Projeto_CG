#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../cg-lib.h"
#include "key.h"
#include "mouse_cube.h"

class Keyboard
{
public:
    Cuboid base;
    vector<Key> keys;
    MouseCube mouse_wheel;
    vector<GLdouble> pts;
    vector<GLdouble> colours;
    void setup_draw()
    {
        pts.clear();
        vector<Cuboid> cubes;
        cubes.push_back(base);
        for (auto c : keys)
            cubes.push_back(c);
        cubes.push_back(mouse_wheel);
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
        base = Cuboid(point3d(0.0, 0.0, 0.0), 20.0, 10.0, 2.0, GREY);
        keys.emplace_back(point3d(2, 6, 1.5), 3, 3, 1, YELLOW); // W
        keys.emplace_back(point3d(1, 2, 1.5), 3, 3, 1, RED);    // A
        keys.emplace_back(point3d(5, 2, 1.5), 3, 3, 1, GREEN);  // S
        keys.emplace_back(point3d(9, 2, 1.5), 3, 3, 1, BLUE);   // D
        mouse_wheel = MouseCube(point3d(14, 2, 2 * sqrt(3.0f)), 4.0, 4.0, 4.0, MAGENTA);
        setup_draw();
    }

    void drawLetters()
    {
        glRasterPos3d(2, 5.5, 2);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
    }

    void draw()
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, &pts[0]);
        for (GLuint i = 0; i < 24; i += 4) // base
        {
            vector<GLuint> vec = {i, i + 1, i + 2, i + 3};
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
        }
        for (GLuint i = 0; i < keys.size(); i++)
        {
            glPushMatrix();
            glTranslatef(0, 0, keys[i].deltaZ);
            for (GLuint j = 0; j < 24; j += 4)
            {
                GLuint k = 24 * (i + 1) + j;
                vector<GLuint> vec = {k, k + 1, k + 2, k + 3};
                glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
            }
            glPopMatrix();
        }
        // cout << "Boo1\n";
        auto &c = mouse_wheel;
        // cout << "Boo2\n";
        auto p1 = c.faces[0].points[0], p2 = c.faces[2].points[2];
        glPushMatrix();
        glTranslatef((p1.x + p2.x) / 2, (p1.y + p2.y) / 2, (p1.z + p2.z) / 2);
        glRotatef(mouse_wheel.angX, 1, 0, 0);
        glRotatef(mouse_wheel.angY, 0, 1, 0);
        glTranslatef(-(p1.x + p2.x) / 2, -(p1.y + p2.y) / 2, -(p1.z + p2.z) / 2);
        for (GLuint i = 24 * (1 + keys.size()) /*pts.size() - 24*/; i < pts.size(); i += 4)
        {
            vector<GLuint> vec = {i, i + 1, i + 2, i + 3};
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, &vec[0]);
        }
        glPopMatrix();
    }
};

#endif