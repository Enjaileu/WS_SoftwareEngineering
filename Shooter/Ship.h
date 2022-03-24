#pragma once
#include "Actor.h"
#include <SDL_stdinc.h>
#include "CircleCollisionComponent.h"

class Ship : public Actor
{
public:
	Ship();

	void ActorInput(const Uint8* keyState) override;
	void UpdateActor(float dt) override;

private:
	float laserCooldown;
	CircleCollisionComponent* collision;
	int lifePts;
	float LifeCooldown;
	bool vulnerability;
};

