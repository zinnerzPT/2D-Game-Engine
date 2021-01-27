#pragma once
#include <glm/glm.hpp> // GLM header files
#include <glm/ext.hpp> // perspective, translate, rotate

class Transform
{
public:
	Transform();
	~Transform();

	void Translate(float x, float y);
	void setPosition(float x, float y);
	glm::mat4 glmTransform;

private:
	
};

