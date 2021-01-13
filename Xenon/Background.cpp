#include "Background.h"

Background::Background(std::string filepath)
{
	Texture* texture = new Texture(filepath);
	textures.push_back(texture);
}


void Background::update(float deltaTime)
{

}