#include "vector.h"

vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
float fov_factor = 128.0f; // used for scaling the projected points

vec2_t orthographic_projection(vec3_t point){
    vec2_t ortho_point = {.x = point.x * fov_factor, .y = point.y * fov_factor};
    return ortho_point;
}
