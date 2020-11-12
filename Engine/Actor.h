#pragma once

#include "Transform.h"
class Actor
{
public:
	Transform transform;

	virtual void update(float deltaTime) = 0;
};
