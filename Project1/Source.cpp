#include "SDL.h"
#undef main
#include <iostream>
#include "Simulation.h"

Simulation* simulation = nullptr;

int main() {
	simulation = new Simulation();

	const char* title = "FPY";
	int width = 800;
	int height = 800;
	bool fullscreen = false;
	SDL_Color backgroudColor = { 200, 100, 100, 255 };
	simulation->Init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen, backgroudColor);

	while (simulation->Running())
	{
		simulation->HandleEvents();
		simulation->Update();
		simulation->Render();

	}

	simulation->Clean();
}
