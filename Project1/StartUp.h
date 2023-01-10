#pragma once
#include <iostream>


class StartUp
{
public:
	StartUp();
	void handleEvents();
	void update();
	void render();
	bool returnTesting() { return testing; };
private:
	bool testing = true;
};