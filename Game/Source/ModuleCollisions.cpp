#include "ModuleCollisions.h"

#include "app.h"

#include "Render.h"
#include "Input.h"
#include "Log.h"

#include "SDL/include/SDL_Scancode.h"

//ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
ModuleCollisions::ModuleCollisions(bool start_enabled) : Module(start_enabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::H_CB] = false;
	matrix[Collider::Type::WALL][Collider::Type::V_CB] = false;
	matrix[Collider::Type::WALL][Collider::Type::LAVA] = false;
	matrix[Collider::Type::WALL][Collider::Type::NULL_COLLIDER] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::H_CB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::V_CB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::LAVA] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::NULL_COLLIDER] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::H_CB] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::V_CB] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::LAVA] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::NULL_COLLIDER] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::H_CB] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::V_CB] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::LAVA] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::NULL_COLLIDER] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::H_CB] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::V_CB] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::LAVA] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::NULL_COLLIDER] = false;

	matrix[Collider::Type::H_CB][Collider::Type::WALL] = false;
	matrix[Collider::Type::H_CB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::H_CB][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::H_CB][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::H_CB][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::H_CB][Collider::Type::H_CB] = true;
	matrix[Collider::Type::H_CB][Collider::Type::V_CB] = true;
	matrix[Collider::Type::H_CB][Collider::Type::LAVA] = false;
	matrix[Collider::Type::H_CB][Collider::Type::NULL_COLLIDER] = false;

	matrix[Collider::Type::V_CB][Collider::Type::WALL] = false;
	matrix[Collider::Type::V_CB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::V_CB][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::V_CB][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::V_CB][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::V_CB][Collider::Type::H_CB] = true;
	matrix[Collider::Type::V_CB][Collider::Type::V_CB] = true;
	matrix[Collider::Type::V_CB][Collider::Type::LAVA] = false;
	matrix[Collider::Type::V_CB][Collider::Type::NULL_COLLIDER] = false;

	matrix[Collider::Type::LAVA][Collider::Type::WALL] = false;
	matrix[Collider::Type::LAVA][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LAVA][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LAVA][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::LAVA][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::LAVA][Collider::Type::H_CB] = false;
	matrix[Collider::Type::LAVA][Collider::Type::V_CB] = false;
	matrix[Collider::Type::LAVA][Collider::Type::LAVA] = false;
	matrix[Collider::Type::LAVA][Collider::Type::NULL_COLLIDER] = false;

	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::WALL] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::H_CB] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::V_CB] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::LAVA] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::NULL_COLLIDER] = false;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::Awake()
{
	return true;
}

bool ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool ModuleCollisions::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return true;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case Collider::Type::WALL: // blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case Collider::Type::PLAYER: // green
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case Collider::Type::PLAYER_SHOT: // yellow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case Collider::Type::ENEMY_SHOT: // magenta
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case Collider::Type::H_CB: // orange
			app->render->DrawRectangle(colliders[i]->rect, 255, 155, 0, alpha);
			break;
			case Collider::Type::V_CB: // light blue
			app->render->DrawRectangle(colliders[i]->rect, 0, 240, 255, alpha);
			break;
			case Collider::Type::LAVA: // light green
			app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
			break;
			case Collider::Type::NULL_COLLIDER: // black
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}