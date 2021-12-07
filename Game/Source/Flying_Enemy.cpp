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

	//Have the Soldiers describe a path in the screen taking into account the collisions


	collider = app->collisions->AddCollider({ position.x, position.y, 20, 30 }, Collider::Type::ENEMY, (Module*)app->enemies);
	//ALSO NEED TO ADD THE BOX2D PHYSICS
	
	Flying_Enemy_List.add(app->physics->CreateFlyingEnemyBox(position.x, position.y, 30, 30));
	Flying_Enemy_List.end->data->listener = this;
	
	if (app->map->Load("forest_walkable.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	
}

void Flying_Enemy::Update()
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT

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
	Enemy::Update();
}
