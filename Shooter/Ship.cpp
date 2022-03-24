#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Maths.h"
#include "Laser.h"
#include "Log.h"
#include "Game.h"

Ship::Ship() : Actor() {

	vector<Texture*> animTextures{
		&Assets::GetTexture("Ship01"),
		&Assets::GetTexture("Ship02"),
		&Assets::GetTexture("Ship03"),
		&Assets::GetTexture("Ship04"),
	};

	AnimSpriteComponent* asc = new AnimSpriteComponent(this, animTextures);
	InputComponent* ic = new InputComponent(this);
	ic->SetMaxAngularSpeed(Maths::twoPi);
	ic->SetMaxForwardSpeed(300.f);

	collision = new CircleCollisionComponent(this);
	collision->SetRadius(40.f);

	lifePts = 3;
	LifeCooldown = 3.0f;
	vulnerability = true;
}

void Ship::ActorInput(const Uint8* keyState) {
	if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.f) {
		Laser* laser = new Laser();
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		laserCooldown = 0.2f;
	}
}

void Ship::UpdateActor(float dt) {
	laserCooldown -= dt;
	if (vulnerability == false) {
		LifeCooldown -= dt;
		if (LifeCooldown <= 0) {
			vulnerability = true;
			LifeCooldown = 3.0f;
		}
	}

	//collision
	if (vulnerability == true) {
		auto asteroids = GetGame().GetAsteroids();
		for (auto asteroid : asteroids) {
			if (IsIntersect(*collision, asteroid->GetCollision())) {
				lifePts--;
				vulnerability = false;
				Log::info("-1 vie");
				if (lifePts <= 0) {
					SetState(Actor::ActorState::Dead);
					asteroid->SetState(ActorState::Dead);
					GetGame().Unload();
					GetGame().Close();
				}
				break;
			}
		}
	}
}