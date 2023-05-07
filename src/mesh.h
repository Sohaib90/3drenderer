#ifndef MESH_H
#define MESH_H

#include <stdbool.h>
#include <string.h>
#include "vector.h"
#include "triangle.h"
#include "dynamic_array/dynamic_array.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)

extern vec3_t cubeVertices[N_CUBE_VERTICES];
extern face_t cubeFaces[N_CUBE_FACES];

/* Defines a dynamic array of mesh */
typedef struct
{
    array_t vertices;
    array_t faces;
    vec3_t mesh_rotation; // rotation x, y, and z for mesh

} mesh_t;

extern mesh_t mesh;

void load_cube_mesh_data(void);
void init_mesh_data(void);
bool load_obj_file(char *filename);

#endif