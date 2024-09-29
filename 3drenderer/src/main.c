#include <stdio.h> ///Compiller
#include <SDL2/SDL.h>
#include <stdbool.h>
///int main(void){
///	printf("Hello, World!\n");
///	return 0;
///
bool is_running = false;
SDL_Window* window = NULL; //Pointer to SDL Window
SDL_Renderer* renderer = NULL;
/* Create an SDL window*/
bool initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){ //INIT_EVERYTHING is a boilerplate function 
		fprintf(stderr, "error initializing SDL.\n"); //stderr= standard error output
		return false;
	}
	//Create an SDL Window, SDL_CreateWindow = title, PosX, PosY, and Width, Height)
	
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);
	
	if (!window){
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}
	//Create an SDL Renderer SDL_CreateRenderer(window, default display(-1 gets the first default monitor), default flags)
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	if(!renderer){
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}
	return true;	
}
void setup(void){
	
}

void update(void){
	
}

void render(void){
	SDL_SetRenderDrawColor(renderer, 255, 0 ,0 ,255);
	SDL_RenderClear(renderer);
	
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
	
	return 0;
}