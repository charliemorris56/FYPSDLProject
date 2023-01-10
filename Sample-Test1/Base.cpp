#include "pch.h"
//#include "Base.h"
//
//Base::Base()
//{
//	fullscreen = false;
//	int flags = 0;
//	flags = SDL_WINDOW_RESIZABLE;
//	if (fullscreen) {
//		flags = flags | SDL_WINDOW_FULLSCREEN;
//	}
//	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
//		std::cout << "Subsystems Initialized!\n";
//
//		window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, flags);
//		if (window) {
//			std::cout << "Window Created!\n";
//			SDL_SetWindowMinimumSize(window, 100, 100);
//		}
//		renderer = SDL_CreateRenderer(window, -1, 0);
//		if (renderer) {
//			SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
//			std::cout << "Renderer created!\n";
//			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//			isRunning = true;
//		}
//
//	}
//
//	while (isRunning) {
//		handleEvents();
//		update();
//		render();
//	}
//
//	//frees memory associated with renderer and window
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);	//error here
//	SDL_Quit();
//}
//
//void Base::handleEvents()
//{
//	//the only event we'll check is the  SDL_QUIT event.
//	SDL_Event event;
//	SDL_PollEvent(&event);
//
//
//	switch (event.type) {
//	case SDL_QUIT:
//		isRunning = false;
//		break;
//	default:
//		break;
//	}
//}
//
//void Base::render()
//{
//	SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
//	SDL_RenderClear(renderer);
//
//	//your stuff to render would typically go here.
//	SDL_RenderPresent(renderer);
//}
//
//void Base::update()
//{
//	//if things could update the code would go in here.
//}
//
