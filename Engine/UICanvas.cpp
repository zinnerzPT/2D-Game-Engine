#include "UICanvas.h"
#include "Engine.h"
#include "Level.h"
#include "Renderer.h"

UICanvas::UICanvas()
{
	Engine::getLevel()->addCanvas(this);
}

void UICanvas::render()
{
	for (Texture* t : textures)
	{
		// SDL render
		Engine::renderer->copy(t, t->getSrcRect(), t->getDstRect());
	}
}

void UICanvas::destroy()
{
	Engine::getLevel()->addCanvasToRemove(this);
}

UICanvas::~UICanvas()
{
	for (Texture* t : textures)
	{
		delete t;
	}
	for (Tilemap* tm : tilemaps)
	{
		delete tm;
	}
}
