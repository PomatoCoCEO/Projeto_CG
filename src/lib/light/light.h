#ifndef LIGHT_H
#define LIGHT_H
#include <GL/glut.h>
#include "../cg-lib.h"
struct Light
{
    int posLight; // GL_LIGHT0 to GL_LIGHT7
    point3d pos;
    GLfloat posw;
    colour4 amb;
    colour4 diff;
    colour4 spec;
    GLfloat constantAt, linearAt, quadAt;
    point3d spotDir;
    GLfloat spotExp, spotCutoff;
    Light(int posLight, point3d pos, float posw, colour4 amb, colour4 diff = BLACK, colour4 spec = BLACK, GLfloat constantAt = 1.0f, GLfloat linearAt = 0.f, GLfloat quadAt = 0.f, point3d spotDir = point3d(1, 0, 0), GLfloat spotExp = 0, GLfloat spotCutoff = 180)
        : posLight(posLight), pos(pos), posw(posw), amb(amb), diff(diff), spec(spec), constantAt(constantAt), linearAt(linearAt), quadAt(quadAt), spotDir(spotDir), spotExp(spotExp), spotCutoff(spotCutoff)
    {
        apply();
        on();
    }

    void apply()
    {
        float ps[] = {(float)pos.x, (float)pos.y, (float)pos.z, (float)posw};
        glLightfv(posLight, GL_POSITION, ps);
        float ambArr[] = {(float)amb.r,
                          (float)amb.g,
                          (float)amb.b};
        glLightfv(posLight, GL_AMBIENT, ambArr);
        float diffArr[] = {(float)diff.r, (float)diff.g, (float)diff.b};
        glLightfv(posLight, GL_DIFFUSE, diffArr);
        glLightf(posLight, GL_CONSTANT_ATTENUATION, constantAt);
        glLightf(posLight, GL_LINEAR_ATTENUATION, linearAt);
        glLightf(posLight, GL_QUADRATIC_ATTENUATION, quadAt);
        float spDir[] = {spotDir.x, spotDir.y, spotDir.z};
        glLightfv(posLight, GL_SPOT_DIRECTION, spDir);
        glLightf(posLight, GL_SPOT_EXPONENT, spotExp);
        glLightf(posLight, GL_SPOT_CUTOFF, spotCutoff);
    }
    void on()
    {
        glEnable(posLight);
    }
    void off()
    {
        glDisable(posLight);
    }
};
#endif