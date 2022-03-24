#pragma once
#include <vector>
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Asteroid.h"
#include "Score.h"

using std::vector;

class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	Renderer& GetRenderer() { return renderer; }

	//Game Specific
	vector<Asteroid*>& GetAsteroids() { return asteroids; }
	void AddAsteroid(Asteroid* asteroid);
	void RemoveAsteroid(Asteroid* asteroid);

private:
	Game(){};

public:
	bool Initialize();
	void Load();
	void Loop();
	void Unload();
	void Close();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);
	void CreateAsteroid();

	Score* GetScore() { return &score; }

private:
	void ProcessInput();
	void Update(float dt);
	void Render();

	bool isRunning{ true };
	Window window;
	Renderer renderer;

	bool isUpdatingActors {false}; //sert � lock pour empecher d'ajouter des actors quand c'est pas la bonne situation
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
	vector<Asteroid*> asteroids;

	Score score;
};

