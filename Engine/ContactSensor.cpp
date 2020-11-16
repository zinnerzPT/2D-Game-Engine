#include "ContactSensor.h"

#include <box2d/box2d.h>

ContactSensor::ContactSensor()
{
	rigidBody.getBodyDef()->userData.pointer = reinterpret_cast<uintptr_t>(this);
	rigidBody.getFixtureDef()->isSensor = true;
}