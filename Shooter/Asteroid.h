#pragma once
#include "Actor.h"
#include "CircleCollisionComponent.h"
#include "ISubject.h"

class Asteroid : public Actor, public ISubject
{
public:
	Asteroid();
	~Asteroid();

	CircleCollisionComponent& GetCollision() { return *collision; }

	void AddObserver(IObserver* observer);
	void RemoveObserver(IObserver* observer);
	void Notify(int idEvent);

private:
	CircleCollisionComponent* collision;
};

