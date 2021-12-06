#include "textures.h"

extern vector<uint> texture_ids;
void initTextures()
{
    glEnable(GL_TEXTURE_2D);
    // cout << "Boo1\n";
    texture_ids = vector<GLuint>(10);
    // cout << "Boo2\n";
    // glGenTextures(textures.size(), &texture_ids[0]);
    // cout << "Boo3\n";
    // cout << "textures.size() = " << textures.size() << endl
    //      << "ids.size()=" << texture_ids.size() << endl;
    int i;
    for (i = 0; i < textures.size(); i++)
    {
        glGenTextures(1, &texture_ids[i]);
        // cout << "ah1\n";
        glBindTexture(GL_TEXTURE_2D, texture_ids[i]);
        // textures[i].LoadBmpFile("tapete.bmp");
        auto &imag = textures[i].im;
        imag.LoadBmpFile(textures[i].nameOfFile.c_str());
        // cout << "ah2\n";
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, textures[i].blend);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textures[i].linear);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textures[i].linear);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textures[i].repeat);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textures[i].repeat);
        // cout << "Image num cols: " << imag.GetNumCols() << " and rows" << imag.GetNumRows() << endl;
        // cout << "ah3\n";
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     imag.GetNumCols(),
                     imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     imag.ImageData());
        // cout << "ah4\n";
        // cout << "textures.size() = " << textures.size() << endl;
    }
    cout << "Before free\n";
}

void applyTexture(Texture &texture)
{
    glBindTexture(GL_TEXTURE_2D, texture_ids[texture.pos]);
}
/*glGenTextures(1, &texture[0]);
glBindTexture(GL_TEXTURE_2D, texture[0]);
imag.LoadBmpFile("tapete.bmp");
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexImage2D(GL_TEXTURE_2D, 0, 3,
             imag.GetNumCols(),
             imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
             imag.ImageData());
*/