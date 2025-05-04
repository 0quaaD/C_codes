/*
	This is basic SDL window creation program that generates the window around 60 FPS.
	The program can be compiled with 'gcc' like this: 
		gcc -o main main.c $(sdl-config --cflags --libs)
	
	I hope this will help some of you :D
*/

#include <SDL2/SDL.h>
#include <stdio.h>
int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int running = 1;
    while(running){
	    while(SDL_PollEvent(&event)){
		    if(event.type == SDL_QUIT){
			    running = 0;
		    }
	    }
	    SDL_Delay(16); // ~ 60 FPS delay ## 144 fps delay => 1000 ms / 144 fps = 6.94ms => almost 7 ms
			   // then ~144 FPS delay = SDL_Delay(7) will work just fine.
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
    

