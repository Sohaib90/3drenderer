#include <stdio.h>
#include <stdbool.h> // since we dont have native support for bool in c
#include <SDL2/SDL.h>
#include "dynamic_array/dynamic_array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

array_t triangle_to_render;
bool is_running = false;
uint32_t previous_frame_time = 0;

void setup(void){
    // allocate memory for color buffer
    color_buffer = (uint32_t*) malloc(sizeof(color_buffer) * window_width * window_height);
    if (!color_buffer) {
       fprintf(stderr, "Error Allocating memory for color buffer");
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
    if (!texture) {
       fprintf(stderr, "Error creating texture");
    }

    /* Load the cube values in the mesh data structure (mesh,h) */
    load_cube_mesh_data();
}

void process_input(void){
    SDL_Event event;

    while(SDL_PollEvent(&event)){

        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Log("Quit key was pressed. Exiting window.");
            SDL_Quit();
            is_running = false;        
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE){
                SDL_Log("Esc key was released. Exiting window.");
                SDL_Quit();
                is_running = false;
                break;
            }
        }
    }
}

void update(void){

    if (FRAME_TARGET_TIME >= SDL_GetTicks() - previous_frame_time){
        SDL_Delay(FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time));
    };

    triangle_to_render = array_create(1, ARR_TRIANGLE); 

    // how many ms have passed since the last frame
    previous_frame_time = SDL_GetTicks();
    
    mesh.mesh_rotation.x += 0.01;
    mesh.mesh_rotation.y += 0.01;
    mesh.mesh_rotation.z += 0.01;

    for (int i = 0; i < mesh.faces.occupied; i++){
        vec3_t vertices[3];
        vertices[0] = ((vec3_t*)mesh.vertices.data)[((face_t*)mesh.faces.data)[i].a - 1];
        vertices[1] = ((vec3_t*)mesh.vertices.data)[((face_t*)mesh.faces.data)[i].b - 1];
        vertices[2] = ((vec3_t*)mesh.vertices.data)[((face_t*)mesh.faces.data)[i].c - 1];

        triangle_t projected_triangle;

        for (int j = 0; j < 3; j++){
            vec3_t transformed_vertex = rotate_vector_x(vertices[j], mesh.mesh_rotation.x);
            transformed_vertex = rotate_vector_y(transformed_vertex, mesh.mesh_rotation.y);
            transformed_vertex = rotate_vector_z(transformed_vertex, mesh.mesh_rotation.z);

            // move the camera away
            transformed_vertex.z -= camera_positon.z;
            
            // the triangle which needs to be projected
            vec2_t projected_point = perspective_projection(transformed_vertex);
            projected_point.x += window_width / 2;
            projected_point.y += window_height /2 ;
            projected_triangle.points[j] = projected_point; 
        }

        array_push(&triangle_to_render, i, &projected_triangle);
    }    
}

void render(void){
    
    draw_grid();
    for (size_t i = 0; i < triangle_to_render.occupied; i++){
        triangle_t triangle = ((triangle_t*)triangle_to_render.data)[i];

        //draw vertices
        draw_rectangle(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xffffff00);
        draw_rectangle(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xffffff00);
        draw_rectangle(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xffffff00);

        // draw triangle
        draw_triangle(triangle, 0xff0000ff);
    }

    array_free(&triangle_to_render);

    render_color_buffer();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

void free_mem_resources(void){
    /* Free resources for dynamic arrays*/
    free(color_buffer);
    array_free(&mesh.faces);
    array_free(&mesh.vertices);
}

int main(void) {

    is_running = initialize_window();

    setup();
    // Game loop
    while (is_running) {
        process_input();
        update();
        render();
    }

    free_window_resources();
    free_mem_resources();
    return 0;
}