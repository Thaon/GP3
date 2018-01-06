#pragma once
#include "Common.h"

/***
	The Display class first initializes the window, then creates and configures the OpenGl context.
*/

class Display
{
public:
	Display(int width, int height);
	Display();
	~Display();
	void initDisplay();
	void swapBuffer();
	void clearDisplay(float r, float g, float b, float a);

	float getWidth();
	float getHeight();

private:

	void returnError(std::string errorString);
	
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	int screenWidth, screenHeight;
};

