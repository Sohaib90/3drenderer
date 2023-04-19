#include <math.h>
#include "vector.h"

vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
vec3_t camera_positon = {0.0f, 0.0f, -5.0f};
float fov_factor = 640.0f; // used for scaling the projected points

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

vec2_t perspective_projection(vec3_t point){
    // adding to the points meaning pushing the points into the screen
    point.z = point.z - camera_positon.z; 
    vec2_t prespective_point = {
                .x = (point.x / point.z) * fov_factor, 
                .y = (point.y / point.z) * fov_factor
            };
    return prespective_point;
}
