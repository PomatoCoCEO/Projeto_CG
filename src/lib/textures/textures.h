#ifndef TEXTURES_H
#define TEXTURES_H
#include "../external/RgbImage.h"
#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
struct Texture
{
    int pos;
    RgbImage im;
    int blend, repeat, linear;
    string nameOfFile;
    Texture(int pos, string nameOfFile, int blend, int repeat, int linear) : pos(pos), nameOfFile(nameOfFile), blend(blend), linear(linear), repeat(repeat)
    {
        im = RgbImage();
        // im.LoadBmpFile(nameOfFile.c_str());
    }
};
void applyTexture(Texture &texture);
void initTextures();
static vector<uint> texture_ids; //  = vector<uint>(10);
const Texture WOOD = Texture(0, "../lib/textures/images/madeira.bmp", GL_DECAL, GL_REPEAT, GL_LINEAR);
const Texture SKY = Texture(1, "../lib/textures/images/sky.bmp", GL_MODULATE, GL_REPEAT, GL_LINEAR);
const Texture RUG = Texture(2, "../lib/textures/images/tapete.bmp", GL_MODULATE, GL_REPEAT, GL_LINEAR);
const Texture TEA = Texture(3, "../lib/textures/images/tea.bmp", GL_MODULATE, GL_REPEAT, GL_LINEAR);
const Texture COLOURED = Texture(4, "../lib/textures/images/colorida.bmp", GL_MODULATE, GL_REPEAT, GL_LINEAR);
static vector<Texture> textures = {WOOD, SKY, RUG, TEA, COLOURED};
#endif