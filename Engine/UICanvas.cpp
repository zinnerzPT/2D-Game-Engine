#include "UICanvas.h"
#include "Engine.h"
#include "Level.h"
//#include <glm/glm.hpp>
#include "Transform.h"
#include "SceneViewer.h"

UICanvas::UICanvas()
{
	Engine::getLevel()->addCanvas(this);
	transform = new Transform();
}

void UICanvas::draw(SceneViewer* v)
{
	for (Texture* t : textures)
	{
		t->draw(v);
		// SDL render
		//Engine::renderer->copy(t, t->getSrcRect(), t->getDstRect());
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

void UICanvas::drawText(std::string text, BitmapFont* font, float x, float y)
{
	font->drawText(x, y, text, Engine::getInstance()->getSceneViewer());
}
