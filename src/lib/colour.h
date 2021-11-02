#ifndef COLOUR_H
#define COLOUR_H
#include <GL/glut.h>

struct colour4
{
    GLfloat r, g, b, a;
    colour4(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : r(r), g(g), b(b), a(a) {}
};

struct colour3 : public colour4
{
    colour3(GLfloat r, GLfloat g, GLfloat b) : colour4(r, g, b, 1.0) {}
};

colour4 light(colour4 c)
{
    GLfloat r = (1.0 - c.r) / 2, g = (1.0 - c.g) / 2, b = (1.0 - c.b) / 2;
    return colour4(r, g, b, c.a);
}

colour4 dark(colour4 c)
{
    GLfloat r = c.r / 2, g = c.g / 2, b = c.b / 2;
    return colour4(r, g, b, c.a);
}

const colour4 RED = colour4(1, 0, 0, 1);
const colour4 GREEN = colour4(0, 1, 0, 1);
const colour4 BLUE = colour4(0, 0, 1, 1);
const colour4 WHITE = colour4(1, 1, 1, 1);
const colour4 BLACK = colour4(0, 0, 0, 1);
const colour4 MAGENTA = colour4(1, 0, 1, 1);
const colour4 CYAN = colour4(0, 1, 1, 1);
const colour4 YELLOW = colour4(1, 1, 0, 1);
const colour4 GREY = colour4(0.5, 0.5, 0.5, 1);

#endif