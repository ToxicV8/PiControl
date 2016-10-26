

#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "Includes.h"

struct Color
{
    int r, g, b, a;

    Color(int r, int g, int b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 255;
    }

    Color(int r, int g, int b, int a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

};

#endif // STRUCTS_H_INCLUDED
