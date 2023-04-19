#include <math.h>
#include "vector.h"

vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
float fov_factor = 128.0f; // used for scaling the projected points

vec2_t orthographic_projection(vec3_t point){
    vec2_t ortho_point = {.x = point.x * fov_factor, .y = point.y * fov_factor};
    return ortho_point;
}

vec2_t isometric_projection(vec3_t point, float angle){

    float u = point.x*cos(angle) + point.y*cos(angle+120) + point.z*cos(angle-120);
    float v = point.x*sin(angle) + point.y*sin(angle+120) + point.z*sin(angle-120);
    vec2_t iso_point = {
                        .x = u * fov_factor, 
                        .y = v * fov_factor
                        };
    return iso_point;
}