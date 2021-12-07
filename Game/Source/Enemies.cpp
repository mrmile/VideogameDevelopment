#include "Enemies.h"

#include "App.h"

#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Collider.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "Window.h"
#include "Enemy.h"

#define SPAWN_MARGIN 50


Enemies::Enemies(bool startEnabled) : Module(startEnabled) 
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

Enemies::~Enemies()
{

}

bool Enemies::Start()
{
	texture = app->tex->Load("Assets/textures/enemies_final.png");
	
	enemyDestroyedFx = app->audio->LoadFx("Assets/audio/fx/Durp.wav");

	return true;
}


bool Enemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool Enemies::Update(float dt)
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update(60);
	}

	HandleEnemiesDespawn();

	return true;
}

bool Enemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return true;
}

// Called before quitting
bool Enemies::CleanUp()
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool Enemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}
	

	return ret;
}

void Enemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if ((spawnQueue[i].x * 1 < app->render->camera.x + (app->render->camera.w * 1) + SPAWN_MARGIN) || (spawnQueue[i].x * 1 > app->render->camera.x - (app->render->camera.w * 1) - SPAWN_MARGIN) || (spawnQueue[i].y * 1 < app->render->camera.y - (app->render->camera.h * 1) - SPAWN_MARGIN))
			{
				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void Enemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.y * 1 > (app->render->camera.y + app->win->screenSurface->h * 1) + SPAWN_MARGIN)
			{
				enemies[i]->SetToDelete();
			}

		}
	}
}

void Enemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{

		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case Enemy_Type::FLYING_TYPE:
				//enemies[i] = new Enemy_Soldier(info.x, info.y);
				break;
			case Enemy_Type::WALKING_TYPE:
				//enemies[i] = new Enemy_Soldier_Standing(info.x, info.y);
				break;

			}
			enemies[i]->texture = texture;
			//enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void Enemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c1, c2); //Notify the enemy of a collision
			break;
		}
	}

}