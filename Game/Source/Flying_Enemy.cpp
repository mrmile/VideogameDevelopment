#include "Flying_Enemy.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Enemies.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "Input.h"
#include "Map.h"
#include "Pathfinding.h"
#include "ModulePhysics.h"

Flying_Enemy::Flying_Enemy(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHP = 2;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	Flying_Enemy_Left.PushBack({890,248,38,35});
	Flying_Enemy_Left.PushBack({841,248,38,35});
	Flying_Enemy_Left.PushBack({791,248,38,35});
	Flying_Enemy_Left.PushBack({741,248,38,35});
	Flying_Enemy_Left.PushBack({700,248,38,35});
	Flying_Enemy_Left.loop = true;
	Flying_Enemy_Left.speed = 0.3f;

	Flying_Enemy_Right.PushBack({334,248,38,35});
	Flying_Enemy_Right.PushBack({381,248,38,35});
	Flying_Enemy_Right.PushBack({431,248,38,35});
	Flying_Enemy_Right.PushBack({482,248,38,43});
	Flying_Enemy_Right.PushBack({522,248,38,35});
	Flying_Enemy_Right.loop = true;
	Flying_Enemy_Right.speed = 0.3f;



	collider = app->collisions->AddCollider({ position.x, position.y, 38, 35 }, Collider::Type::ENEMY, (Module*)app->enemies);
	//ALSO NEED TO ADD THE BOX2D PHYSICS
	
	Flying_Enemy_List.add(app->physics->CreateFlyingEnemyBox(position.x, position.y, 38, 35));
	//Flying_Enemy_List.end->data->listener = this;
	
	if (app->map->Load("forest_walkable.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	
}

void Flying_Enemy::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	currentAnim = &Flying_Enemy_Right;
	app->pathfinding->CreatePath(position, app->player->position);
	
	for (int i = 0; app->pathfinding->GetLastPath()->GetCapacity(); i++)
	{
		if (position.x < app->pathfinding->GetLastPath()->At(i)->x)
		{
			Flying_Enemy_List.end->data->body->ApplyLinearImpulse({ 5.0f,0 }, { 0,0 }, true);
		}
		if (position.x > app->pathfinding->GetLastPath()->At(i)->x)
		{
			Flying_Enemy_List.end->data->body->ApplyLinearImpulse({ -5.0f,0 }, { 0,0 }, true);
		}
		if (position.y > app->pathfinding->GetLastPath()->At(i)->y)
		{
			Flying_Enemy_List.end->data->body->ApplyLinearImpulse({ 0,0 }, { 5.0f,0 }, true);
		}
		if (position.y < app->pathfinding->GetLastPath()->At(i)->y)
		{
			Flying_Enemy_List.end->data->body->ApplyLinearImpulse({ 0,0 }, { -5.0f,0 }, true);
		}
	}
	



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update(dt);
}
