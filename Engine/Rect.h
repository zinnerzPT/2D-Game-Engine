#pragma once

class Rect 
{
public:
	Rect(int x = 0, int y=0, int w=0, int h=0);
	~Rect();
	struct SDL_Rect* toSDL_Rect();

	//the x location of the rectangle's upper left corner
	int x = 0;

	//the y location of the rectangle's upper left corner
	int y = 0;

	//the width of the rectangle
	int w = 0;

	//the height of the rectangle
	int h = 0;

private:
	struct SDL_Rect* sdl_Rect;
};