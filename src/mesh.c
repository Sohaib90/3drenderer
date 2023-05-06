#include "mesh.h"

mesh_t mesh = {
    .vertices = {.data = NULL, .size = 0, .occupied = 0, .type = ARR_VEC3},
    .faces = {.data = NULL, .size = 0, .occupied = 0, .type = ARR_FACE},
    .mesh_rotation = {0.0f, 0.0f, 0.0f}
};

vec3_t cubeVertices[N_CUBE_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 }, // 1
    { .x = -1, .y =  1, .z = -1 }, // 2
    { .x =  1, .y =  1, .z = -1 }, // 3
    { .x =  1, .y = -1, .z = -1 }, // 4
    { .x =  1, .y =  1, .z =  1 }, // 5
    { .x =  1, .y = -1, .z =  1 }, // 6
    { .x = -1, .y =  1, .z =  1 }, // 7
    { .x = -1, .y = -1, .z =  1 }  // 8
};

face_t cubeFaces[N_CUBE_FACES] = {
    // front
    { .a = 1, .b = 2, .c = 3 },
    { .a = 1, .b = 3, .c = 4 },
    // right
    { .a = 4, .b = 3, .c = 5 },
    { .a = 4, .b = 5, .c = 6 },
    // back
    { .a = 6, .b = 5, .c = 7 },
    { .a = 6, .b = 7, .c = 8 },
    // left
    { .a = 8, .b = 7, .c = 2 },
    { .a = 8, .b = 2, .c = 1 },
    // top
    { .a = 2, .b = 7, .c = 5 },
    { .a = 2, .b = 5, .c = 3 },
    // bottom
    { .a = 6, .b = 8, .c = 1 },
    { .a = 6, .b = 1, .c = 4 }
};

void init_mesh_data(void){
    mesh.faces.data = malloc(array_size(mesh.faces.type));
    mesh.vertices.data = malloc(array_size(mesh.vertices.type));
    mesh.faces.size += 1;
    mesh.vertices.size += 1;
}

void load_cube_mesh_data(void){
    init_mesh_data();

    if (mesh.vertices.data == NULL || mesh.faces.data == NULL){
        printf("Error allocating memory to vertices/faces array in mesh struct\n");
    }

    for (int i = 0; i< N_CUBE_VERTICES; i++){
        array_push(&mesh.vertices, i, &cubeVertices[i]);
    }

    for (int i = 0; i< N_CUBE_FACES; i++){
        array_push(&mesh.faces, i, &cubeFaces[i]);
    }
}