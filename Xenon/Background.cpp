#include "Background.h"

Background::Background(std::string filepath)
{
	Texture* texture = new Texture(filepath);
	textures.push_back(texture);

	// Set the rendering layer
	this->setLayer(-10);
}


void Background::update(float deltaTime)
{

}