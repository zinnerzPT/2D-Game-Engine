#pragma once

#include "Texture.h"
#include "Tilemap.h"

#include <string>
#include <vector>

class Animation;

class Actor
{
public:
	Actor(int x = 0, int y = 0);

	inline void setLayer(int l) { this->layer = l; }

	virtual void update(float deltaTime) = 0;

	//virtual void render(); // Old SDL way

	void draw(class SceneViewer* v = nullptr);
	void destroy();

	virtual ~Actor();

	inline class Transform* getTransform() { return transform; }

protected:
	int layer = 0;

	float xpos = 0.0f;
	float ypos = 0.0f;
	std::vector<Texture*> textures;
	std::vector<Tilemap*> tilemaps;
	std::vector<Animation*> animations;

	bool flipHorizontal = false;
	bool flipVertical = false;

	class Transform* transform;
};
