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

void Transform::Translate(float x, float y, float z /*= 0*/)
{
	glm::mat4 trans = translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glmTransform = trans * glmTransform;
}

void Transform::setPosition(float x, float y, float z)
{
	glmTransform = glm::mat4(1.0f);
	Translate(x, y, z);
}