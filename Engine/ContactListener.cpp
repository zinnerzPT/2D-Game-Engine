#include "ContactListener.h"
#include "ContactSensor.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	uintptr_t userData = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	if (userData)
	{
		ContactSensor* cs = (ContactSensor*)userData;
		cs->onContact();
		contact->GetFixtureA()->GetBody()->GetUserData().pointer = reinterpret_cast<uintptr_t>(nullptr);
	}
	userData = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (userData)
	{
		ContactSensor* cs = (ContactSensor*)userData;
		cs->onContact();
		contact->GetFixtureB()->GetBody()->GetUserData().pointer = reinterpret_cast<uintptr_t>(nullptr);
	}
}
