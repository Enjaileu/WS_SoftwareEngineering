#include "Asteroid.h"
#include "Random.h"
#include "Window.h"
#include "Maths.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Assets.h"
#include "Game.h"

Asteroid::Asteroid() : Actor(), collision{ nullptr } {
	Vector2 randPos = Random::GetVector(Vector2::zero, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.f, Maths::twoPi));

	SpriteComponent* sc = new SpriteComponent(this, Assets::GetTexture("Asteroid"));
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.f);

	collision = new CircleCollisionComponent(this);
	collision->SetRadius(40.f);

	AddObserver(GetGame().GetScore());
	GetGame().AddAsteroid(this);
}

Asteroid::~Asteroid() {
	GetGame().RemoveAsteroid(this);
	GetGame().CreateAsteroid(); 
}

void Asteroid::AddObserver(IObserver* observer) {
	observers.push_back(observer);
}

void Asteroid::RemoveObserver(IObserver* observer) {
	auto iter = std::find(begin(observers), end(observers), observer);
	if (iter != end(observers)) {
		std::iter_swap(iter, end(observers) - 1);
		observers.pop_back();
	}
}

void Asteroid::Notify(int idEvent) {
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->OnNotify(idEvent);
	}
}
