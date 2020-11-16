#include "RigidBody.h"

#include <box2d/box2d.h>

#include "Engine.h"
#include "Level.h"


RigidBody::RigidBody()
{
	body = nullptr;
	fixture = nullptr;

	bodyDef = new b2BodyDef;
	fixtureDef = new b2FixtureDef;
}

void RigidBody::makeDynamic(float density)
{
	isDynamic = true;
	bodyDensity = density;
}

void RigidBody::createBody(float position[2], float halfSize[2])
{
	if (isDynamic)
	{
		bodyDef->type = b2_dynamicBody;
	}
	bodyDef->position.Set(position[0], position[1]);
	body = Engine::getLevel()->getWorld()->CreateBody(bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(halfSize[0], halfSize[1]);

	if (isDynamic)
	{
		fixtureDef->shape = &boxShape;
		fixtureDef->density = bodyDensity;
		fixture = body->CreateFixture(fixtureDef);
	}
	else
	{
		fixture = body->CreateFixture(&boxShape, 0.0f);
	}
	delete bodyDef;
	delete fixtureDef;
}

void RigidBody::setVelocity(float linearVelocity[2])
{
	body->SetLinearVelocity(b2Vec2(linearVelocity[0], linearVelocity[1]));
}


float* RigidBody::getPosition()
{
	b2Vec2 bodyPos = body->GetPosition();
	position[0] = bodyPos.x;
	position[1] = bodyPos.y;
	return position;
}

b2Body* RigidBody::getBody()
{
	return body;
}

struct b2BodyDef* RigidBody::getBodyDef()
{
	return bodyDef;
}

struct b2FixtureDef* RigidBody::getFixtureDef()
{
	return fixtureDef;
}

RigidBody::~RigidBody()
{
	Engine::getLevel()->getWorld()->DestroyBody(body);
}