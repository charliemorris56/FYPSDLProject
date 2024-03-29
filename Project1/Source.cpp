#include "SDL.h"
#undef main
#include <iostream>
#include "Simulation.h"
#include "JsonLoading.h"
#include "AStar.h"

Simulation* simulation = nullptr;

int main() {
	simulation = new Simulation();

	std::cout << "SimulationStarted\n";

	const char* title = "FPY";
	int width = 1100; //Make is a square or the tilemap will brake
	int height = 1100;
	bool fullscreen = false;
	SDL_Color backgroudColor = { 0, 0, 0, 255 };
	simulation->Init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen, backgroudColor);

	while (simulation->Running())
	{
		simulation->HandleEvents();
		simulation->Update();
		simulation->Render();
	}

	simulation->Clean();
}
