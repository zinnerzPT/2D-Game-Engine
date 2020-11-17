#pragma once
#include "Actor.h"
#include "Projectile.h"
#include "Tilemap.h"
#include "Animation.h"

class Missile :
    public Actor,
    public Projectile
{
public:
    Missile(float position[2], float halfSize[2], float density, float linearVelocity[2]);

    virtual void update(float deltaTime) override;

    virtual void onContact() override;

    ~Missile();
private:

	Tilemap* tilemap = nullptr;
	Animation* animation = nullptr;

};

