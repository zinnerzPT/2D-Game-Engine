#include "ContactSensor.h"

#include <box2d/box2d.h>

ContactSensor::ContactSensor()
{
	rigidBody = new RigidBody();
	rigidBody->getBodyDef()->userData.pointer = reinterpret_cast<uintptr_t>(this);
	rigidBody->getFixtureDef()->isSensor = true;
}

ContactSensor::~ContactSensor()
{
	delete rigidBody;
}
