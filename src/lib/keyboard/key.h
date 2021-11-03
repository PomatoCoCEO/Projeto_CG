#include "../cg-lib.h"
class Key : public Cuboid
{
public:
    GLdouble velZ = 0, deltaZ = 0;
    Key() {}
    Key(point3d base, GLdouble x, GLdouble y, GLdouble z, colour4 colour) : Cuboid(base, x, y, z, colour)
    {
    }
};