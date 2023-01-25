#pragma once
#include "SDL.h"
#include "TileMap.h"
#include <iostream>

class Simulation
{
public:
	Simulation();
	~Simulation();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, SDL_Color backgroundColor);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running();
private:
	void RenderSquare();

	bool m_isRunning;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Color m_backgroundColor;

	TileMap* m_tileMap;

	int m_width;
	int m_hight;

	int m_iRows;
	int m_iCols;
};

