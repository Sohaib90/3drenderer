#ifndef VECTOR_H
#define VECTOR_H

#define N_POINTS ( 9 * 9 * 9)

typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

extern vec3_t cube_points[N_POINTS];
extern vec2_t projected_points[N_POINTS];
extern vec3_t camera_positon;
extern float fov_factor;
vec2_t orthographic_projection(vec3_t point);
vec2_t perspective_projection(vec3_t point);
vec2_t isometric_projection(vec3_t point, float angle);
vec3_t rotate_vector_x(vec3_t vector, float angle);
vec3_t rotate_vector_y(vec3_t vector, float angle);
vec3_t rotate_vector_z(vec3_t vector, float angle);

#endif