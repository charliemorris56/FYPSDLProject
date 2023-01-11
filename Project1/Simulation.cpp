#include "Simulation.h"

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

void Simulation::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, SDL_Color backgroundColor)
{
	int flags = SDL_WINDOW_SHOWN;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initialised\n";

		m_window = SDL_CreateWindow("FYP", xpos, ypos, width, height, flags);
		if (m_window)
		{
			std::cout << "Window created\n";
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_renderer)
		{
			std::cout << "Renderer created\n";
		}

		m_isRunning = true;
	}
	else
	{
		m_isRunning = false;
	}

	m_backgroundColor = backgroundColor;
}

void Simulation::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
	default:
		break;
	}
}

void Simulation::Update()
{
}

void Simulation::Render()
{
	SDL_SetRenderDrawColor(m_renderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
	SDL_RenderClear(m_renderer);

	RenderSquare();

	SDL_RenderPresent(m_renderer);
}

void Simulation::Clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	std::cout << "Simulation cleaned\n";
}

bool Simulation::Running()
{
	return m_isRunning;
}

void Simulation::RenderSquare()
{
	SDL_Rect tileMapSquare;
	int squareSize = m_tileMap.GetSquareSize();
	int startingPosX = 5, startingPosY = 5;
	int posX = startingPosX, posY = startingPosY;

	for (int i = 0; i < ROWS * COLUMNS; i++)
	{
		SDL_SetRenderDrawColor(m_renderer, m_tileMap.GetColor(i).r, m_tileMap.GetColor(i).g, m_tileMap.GetColor(i).b, m_tileMap.GetColor(i).a);		

		if (i != 0)
		{
			posX += squareSize;
		}
		bool endOfColumn = i % COLUMNS == 0 && i != 0;
		if (endOfColumn)
		{
			posY += squareSize;
			posX = startingPosX;
		}
		tileMapSquare = { posX, posY, m_tileMap.GetSquareSize(), m_tileMap.GetSquareSize()};
		
		if (m_tileMap.GetColor(i).fill)
		{
			SDL_RenderFillRect(m_renderer, &tileMapSquare);
		}
		else
		{
			SDL_RenderDrawRect(m_renderer, &tileMapSquare);
		}
	}

	std::cout << "Square rendered\n";
}
