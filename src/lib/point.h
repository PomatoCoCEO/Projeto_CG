#ifndef POINT_H
#define POINT_H
#define DEG_TO_RAD(d) ((d)*M_PI / 180.0)
#include <GL/glut.h>
#include <iostream>
using namespace std;

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
    point3d operator/(double a)
    {
        if (a == 0)
            throw "Division by zero";
        point3d n(x / a, y / a, z / a);
        return n; // point2d(x + a.x, y + a.y);
    }
    point3d operator/=(double a)
    {
        if (a == 0)
            throw "Division by zero";
        x /= a, y /= a, z /= a;
        return *this; // point2d(x + a.x, y + a.y);
    }

    point3d operator-(const point3d &a)
    {
        point3d n(x - a.x, y - a.y, z - a.z);
        return n; // point2d(x + a.x, y + a.y);
    }

    point3d operator-=(const point3d &a)
    {
        x -= a.x, y -= a.y, z -= a.z;
        return *this; // point2d(x + a.x, y + a.y);
    }

    GLdouble norm()
    {
        return sqrt(x * x + y * y + z * z);
    }
    point3d normalized()
    {
        point3d no(x, y, z);
        return no / norm();
    }

    friend ostream &operator<<(ostream &o, const point3d &p)
    {
        return (o << "(" << p.x << "," << p.y << "," << p.z << ")");
    }
};

struct point2d : point3d
{
    GLdouble x, y;
    point2d(GLdouble x, GLdouble y) : point3d(x, y, 0) {}
    point2d() {}
};

#endif