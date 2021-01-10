#pragma once

#include "RigidBody.h"

class ContactSensor
{
public:
	ContactSensor();
	virtual void onContact() = 0;
	virtual ~ContactSensor();

protected:
	RigidBody* rigidBody;
};