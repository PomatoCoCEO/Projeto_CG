#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "cg-lib.h"

class Keyboard
{
public:
    Cuboid base;
    vector<Cuboid> keys;
    Cuboid mouse_wheel;
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

        /* for(auto& f: base.faces) {
            for(auto& p: f.points) {
                pts.push_back(p);
            }
        } */
    }

    Keyboard()
    {
        base = Cuboid(point3d(0.0, 0.0, 0.0), 20.0, 10.0, 2.0, GREY);
        keys.emplace_back(point3d(2, 6, 1.5), 3, 3, 1, YELLOW);
        keys.emplace_back(point3d(1, 2, 1.5), 3, 3, 1, RED);
        keys.emplace_back(point3d(5, 2, 1.5), 3, 3, 1, GREEN);
        keys.emplace_back(point3d(9, 2, 1.5), 3, 3, 1, BLUE);
        mouse_wheel = Cuboid(point3d(16, 2, 2 * sqrt(3.0f)), 4, 4, 4, MAGENTA);
        setup_draw();
    }

    void drawLetters()
    {
        glRasterPos3d(2, 5.5, 2);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
    }

    void draw()
    {
        for (int i = 0; i < pts.size(); i += 4)
        {
            vector<GLint> vec = {i, i + 1, i + 2, i + 3};
            glDrawElements(GL_POLYGON, 4, GL_INT, &vec[0]);
        }
    }
};

#endif