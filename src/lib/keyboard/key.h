#include "../cg-lib.h"
class Key : public Cuboid
{
public:
    GLdouble velZ = 0, deltaZ = 0;
    char letter;
    Key() {}
    Key(point3d base, GLdouble x, GLdouble y, GLdouble z, colour4 colour, char letter) : Cuboid(base, x, y, z, colour), letter(letter)
    {
    }
    void drawLetter()
    {
        glColor4f(0, 0, 0, 1);
        point3d aid = faces[0].points[0], aid2 = faces[2].points[3];
        glRasterPos3d(aid.x + 0.5, aid.y + 0.5, aid2.z + 0.01);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
};