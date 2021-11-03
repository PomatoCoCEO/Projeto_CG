#include "../cg-lib.h"

class MouseCube : public Cuboid
{

public:
    GLdouble angX = 0,
             angY = 0, velX = 0, velY = 0;
    MouseCube() {}
    MouseCube(point3d base, GLdouble x, GLdouble y, GLdouble z, colour4 colour) : Cuboid(base, x, y, z, colour)
    {
        cout << "Mouse Wheel constructed: " << faces.size() << "faces.\n";
        cout << "Face length: " << faces[0].points.size() << endl;
    }
};