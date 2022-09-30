#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "polygon.h"
struct Rectangle : public Polygon
{
    // has only 4 sides
    int xDivs = 1, yDivs = 1;

    void draw()
    {
        glEnable(GL_LIGHTING);
        for (int i = transform.size() - 1; i >= 0; i--)
            transform[i].apply();
        if (text != nullptr)
        {
            glEnable(GL_TEXTURE_2D);
            applyTexture(*text);
        }
        glNormal3d(-normal.x, -normal.y, -normal.z);
        // glBegin(GL_POLYGON);
        auto c = colours[0];
        auto p0 = points[0], p1 = points[1], p3 = points[3];
        auto diffX = (p1 - p0) / (xDivs + 0.0), diffY = (p3 - p0) / (yDivs + 0.0); // point3d(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z);
        for (int i = 0; i < xDivs; i++)
        {
            for (int j = 0; j < yDivs; j++)
            {
                auto pxy = p0 + diffX * i + diffY * j, pXy = p0 + diffX * (i + 1) + diffY * j,
                     pxY = p0 + diffX * i + diffY * (j + 1), pXY = p0 + diffX * (i + 1) + diffY * (j + 1);
                // cout << "pXY=" << pxy << endl;
                glBegin(GL_QUADS);
                glColor4f(c.r, c.g, c.b, c.a);
                if (text != nullptr)
                    glTexCoord2f((i + 0.0) / (xDivs + 0.0), (j + 0.0) / (yDivs + 0.0));
                glVertex3d(pxy.x, pxy.y, pxy.z);
                c = colours[1];
                // p = points[1];
                glColor4f(c.r, c.g, c.b, c.a);
                if (text != nullptr)
                    glTexCoord2f((i + 1.0) / (xDivs + 0.0), (j + 0.0) / (yDivs + 0.0));
                glVertex3d(pXy.x, pXy.y, pXy.z);
                c = colours[2];
                // p = points[2];
                glColor4f(c.r, c.g, c.b, c.a);
                if (text != nullptr)
                    glTexCoord2f((i + 1.0) / (xDivs + 0.0), (j + 1.0) / (yDivs + 0.0));
                glVertex3d(pXY.x, pXY.y, pXY.z);
                c = colours[3];
                // p = points[3];
                glColor4f(c.r, c.g, c.b, c.a);
                if (text != nullptr)
                    glTexCoord2f((i + 0.0) / (xDivs + 0.0), (j + 1.0) / (yDivs + 0.0));
                glVertex3d(pxY.x, pxY.y, pxY.z);
                c = colours[0];
                glColor4f(c.r, c.g, c.b, c.a); // colour loop
                glEnd();
            }
        }
        if (text != nullptr)
            glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
    }

    Rectangle(vector<point3d> &points, vector<colour4> &colours, point3d normal, Texture *text = nullptr, int xDivs = 1, int yDivs = 1) : Polygon(points, colours, normal, text), xDivs(xDivs), yDivs(yDivs)
    {
        if (points.size() != 4)
            throw "Incorrect no. of points";
        // draw();
    }

    Rectangle(vector<point3d> &points, colour4 colour, point3d normal, Texture *text = nullptr, int xDivs = 1, int yDivs = 1) : Polygon(points, colour, normal, text), xDivs(xDivs), yDivs(yDivs)
    {
        // draw();
        if (points.size() != 4)
            throw "Incorrect no. of points";
    }

    Rectangle(vector<point3d> &points, point3d normal, Texture *text = nullptr, int xDivs = 1, int yDivs = 1) : Polygon(points, normal, text), xDivs(xDivs), yDivs(yDivs)
    {
        // draw();
        if (points.size() != 4)
            throw "Incorrect no. of points";
    }
    Rectangle() {}
};

#endif