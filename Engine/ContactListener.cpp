#include "ContactListener.h"
#include "ContactSensor.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	ContactSensor* contactSensorA = nullptr;
	ContactSensor* contactSensorB = nullptr;

	// Get the userdata and cast to contact sensor
  	void* userDataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	if (userDataA)
	{
		contactSensorA = (ContactSensor*)userDataA;
	}
	void* userDataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (userDataB)
	{
		contactSensorB = (ContactSensor*)userDataB;
	}

	// Call onContact function on the contact sensors
	if (contactSensorA && contactSensorB)
	{
		contactSensorA->onContact(contactSensorB);
		contactSensorB->onContact(contactSensorA);
	}
	else
	{
		if (contactSensorA)
		{
			contactSensorA->onContact();
		}
		else if(contactSensorB)
		{
			contactSensorB->onContact();
		}
	}
}
