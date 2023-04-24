#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdio.h>
#include "vector.h"

typedef struct 
{
    int a, b, c;
} face_t;

typedef struct
{
    vec2_t points[3]; // three 2D points make on triangle
} triangle_t;


#endif

