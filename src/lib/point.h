#ifndef POINT_H
#define POINT_H
#include <GL/glut.h>

struct point3d
{
    GLdouble x, y, z;
    point3d(GLdouble x, GLdouble y, GLdouble z) : x(x), y(y), z(z) {}
    point3d() {}
    point3d operator+(const point3d &a)
    {
        return point3d(x + a.x, y + a.y, z + a.z);
    }
    point3d operator+=(const point3d &a)
    {
        x += a.x, y += a.y, z += a.z;
        return *this; // point2d(x + a.x, y + a.y);
    }
};

struct point2d : point3d
{
    GLdouble x, y;
    point2d(GLdouble x, GLdouble y) : point3d(x, y, 0) {}
    point2d() {}
};

#endif