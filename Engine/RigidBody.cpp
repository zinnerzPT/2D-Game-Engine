#include "RigidBody.h"

#include <box2d/box2d.h>

#include "Engine.h"


RigidBody::RigidBody()
{
	bodyDef = nullptr;
	body = nullptr;
	fixtureDef = nullptr;
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
		body->CreateFixture(fixtureDef);
	}
	else
	{
		body->CreateFixture(&boxShape, 0.0f);
	}
}

void RigidBody::setVelocity(float linearVelocity[2])
{
	body->SetLinearVelocity(b2Vec2(linearVelocity[0], linearVelocity[1]));
}


float* RigidBody::getPosition()
{
	b2Vec2 bodyPos = body->GetPosition();
	float position[2] = { bodyPos.x, bodyPos.y };
	return position;
}

b2Body* RigidBody::getBody()
{
	return body;
}

class b2BodyDef* RigidBody::getBodyDef()
{
	return bodyDef;
}

class b2FixtureDef* RigidBody::getFixtureDef()
{
	return fixtureDef;
}

RigidBody::~RigidBody()
{
	Engine::getLevel()->getWorld()->DestroyBody(body);
}