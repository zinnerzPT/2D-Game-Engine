#include "Transform.h"
#include "Engine.h"
#include "SceneViewer.h"

static Engine* engine;

Transform::Transform()
{
	glmTransform = glm::mat4(1.0f);
	if (!engine) {
		engine = Engine::getInstance();
	}
}

Transform::~Transform()
{

}

void Transform::Translate(float x, float y)
{
	glm::mat4 trans = translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
	glmTransform = trans * glmTransform;
}

void Transform::setPosition(float x, float y) {
	glmTransform = glm::mat4(1.0f);
	Translate(x, y);
}