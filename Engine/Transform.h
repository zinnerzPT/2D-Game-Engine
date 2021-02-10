#pragma once
#include <glm/glm.hpp> // GLM header files
#include <glm/ext.hpp> // perspective, translate, rotate

class Transform
{
public:
	Transform();
	~Transform();

	void Translate(float x, float y, float z = 0);
	void setPosition(float x, float y, float z);

	inline glm::mat4 getGlmTransform() { return glmTransform; };
private:
	glm::mat4 glmTransform;

};

