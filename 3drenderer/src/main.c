#include <stdio.h> ///Compiller
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "vector.h"


//Declare an array of vectors/points 
const int N_POINTS = 9 * 9 *9;

vec3_t cube_points[N_POINTS]; //9 by 9 by 9 cube as an array from the struct

vec2_t projected_points[N_POINTS];

vec3_t camera_position = {.x =0, .y = 0, .z = -5};

vec3_t cube_rotation = {.x = 0, .y = 0, .z = 0};

int fov_factor = 600;

bool is_running = false;

int previous_frame_time = 0;

/* Create an SDL window*/

void setup(void){
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
		//allocates the required bytes to memory to hold the color buffer
	if(!color_buffer){
		fprintf(stderr, "error allocating color buffer to memory\n");
		//return false; //TODO: MAKE THIS WORK
	}
	///Creating an SDL texture to display the colour. args=render, pixelformat, streaming(changes)
	color_buffer_texture = SDL_CreateTexture(renderer, 
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
	window_width, window_height);
	
	int point_count = 0;
	
	//Load array of vectors from -1 to 1 in cube
	for (float x = -1; x <= 1; x+= 0.25){
		for (float y = -1; y <= 1; y+= 0.25){
			for (float z = -1; z <= 1; z += 0.25){
				vec3_t new_point  = {.x = x, .y = y, .z = z};
				cube_points[point_count] = new_point;
				point_count++;
			}
		}
	}
}
// Receive a 3d vector and return as a 2d point (Orthographic???)
vec2_t project(vec3_t point){
	vec2_t projected_point = {
		.x = (fov_factor * point.x) / point.z,
		.y=(fov_factor * point.y) / point.z
	};
	return projected_point;
}

void update(void){
	while (!SDL_TICKS_PASSED(SDL_GetTicks(),previous_frame_time+FRAME_TARGET_TIME)); //locks render update until target frame per milisecond is reached
	
	previous_frame_time = SDL_GetTicks(); //returns how many miliseconds have passed from SDL init
	
	cube_rotation.x += 0.01;
	cube_rotation.y += 0.01;
	cube_rotation.z += 0.01;
	
	for (int i = 0; i < N_POINTS; i++){
		vec3_t point = cube_points[i];
		
		vec3_t transformed_point = vec3_rotate_y(point, cube_rotation.y);
		
		transformed_point = vec3_rotate_x(transformed_point, cube_rotation.x);
		
		transformed_point = vec3_rotate_z(transformed_point, cube_rotation.z);
		
		// Move z point away based on camera pos
		transformed_point.z -= camera_position.z;
		
		// project the ccorrect point
		vec2_t projected_point = project(transformed_point);
		
		
		//Save projected 2d point vector in the array of projected points
		projected_points[i] = projected_point;
	}
}



void render(void){
	//SDL_SetRenderDrawColor(renderer, 255, 0 ,0 ,255);
	//SDL_RenderClear(renderer);
	
	draw_grid();
	
	//loop through all projected points and render
	
	for (int i = 0; i < N_POINTS; i++){
		vec2_t projected_point = projected_points[i];
		draw_rect(projected_point.x +(window_width /4), projected_point.y + (window_height / 4), 4, 4, 0xFFFFFF00);
	};
	
	render_color_buffer();
	
	clear_color_buffer(0x000000);
	
	//draw_pixel(345, 400, 0x00FF0000);
	//draw_rect(500, 20, 50, 100, 0x00FF0000);
	
	
	SDL_RenderPresent(renderer);
}

void process_input(void){
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
			break;
	}
}


int main(void){
	
	is_running = initialize_window(); 
	
	setup();
	
	while(is_running){ 
		process_input(); //check for inputs
		update();	//update the positions of objects to render based on inputs
		render();	//render 
	}
	
	destroy_window();

}