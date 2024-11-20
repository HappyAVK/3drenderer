#include <stdio.h> ///Compiller
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
///int main(void){
///	printf("Hello, World!\n");
///	return 0;
///
bool is_running = false;

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
}

void update(void){
	
}



void render(void){
	SDL_SetRenderDrawColor(renderer, 255, 0 ,0 ,255);
	SDL_RenderClear(renderer);
	
	render_color_buffer();
	
	clear_color_buffer(0xFFFFFF00);
	draw_grid();
	draw_rect(345, 400, 120, 200, 0x00FF0000);
	
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