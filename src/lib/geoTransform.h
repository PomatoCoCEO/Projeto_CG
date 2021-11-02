#ifndef GEOTRANSFORM_H
#define GEOTRANSFORM_H
#include <vector>
#include <iostream>
using namespace std;

enum func_code
{
    TRANSLATE,
    ROTATE,
    SCALE
};

template <typename T>
struct GeoTransform
{
    // void (*function)(T...);

    // FPointer<T> fp;
    func_code code;
    vector<T> args;
    GeoTransform(func_code code, vector<T> args) : code(code), args(args) {}
    void apply()
    {
        switch (code)
        {
        case TRANSLATE:
            glTranslatef(args[0], args[1], args[2]);
            return;
        case ROTATE:
            glRotatef(args[0], args[1], args[2], args[3]);
            return;
        case SCALE:
            glScalef(args[0], args[1], args[2]);
            return;
            throw "INVALID CODE";
        }
        // we can continue from here to fill this...
    }
};
#endif