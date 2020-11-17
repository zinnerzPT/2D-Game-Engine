#pragma once

#include "RigidBody.h"

class ContactSensor
{
public:
	ContactSensor();
	virtual void onContact() = 0;
	~ContactSensor();

protected:
	RigidBody* rigidBody;
};