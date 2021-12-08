#include "Walking_Enemy.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Enemies.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "Input.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "Pathfinding.h"

Walking_Enemy::Walking_Enemy(int x, int y) : Enemy(x, y)
{	
	Enemy::EnemyHP = 1;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	
	//Have the Soldiers describe a path in the screen taking into account the collisions
	Walking_Enemy_Right.PushBack({64,449,16,18});
	Walking_Enemy_Right.PushBack({93,447,17,20});
	Walking_Enemy_Right.PushBack({123,449,18,18});
	Walking_Enemy_Right.PushBack({151,449,20,18});
	Walking_Enemy_Right.PushBack({181,449,20,19});
	Walking_Enemy_Right.PushBack({213,449,17,19});
	Walking_Enemy_Right.loop = true;
	Walking_Enemy_Right.speed = 0.3f;

	Walking_Enemy_Left.PushBack({1179,448,17,19});
	Walking_Enemy_Left.PushBack({1150,448,17,19});
	Walking_Enemy_Left.PushBack({1119,448,18,19});
	Walking_Enemy_Left.PushBack({1089,448,20,19});
	Walking_Enemy_Left.PushBack({1060,448,18,20});
	Walking_Enemy_Left.PushBack({1030,448,17,20});
	Walking_Enemy_Left.loop = true;
	Walking_Enemy_Left.speed = 0.3f;

	collider = app->collisions->AddCollider({ position.x, position.y, 20, 30 }, Collider::Type::ENEMY, (Module*)app->enemies);
	//ALSO NEED TO ADD THE BOX2D PHYSICS

	Walking_Enemy_List.add(app->physics->CreateFlyingEnemyBox(position.x, position.y, 30, 30));
	//Walking_Enemy_List.end->data->listener = this;

	if (app->map->Load("forest_walkable.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	
	
	
}

void Walking_Enemy::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	
	app->pathfinding->CreatePath(position, app->player->position);

	for (int i = 0; app->pathfinding->GetLastPath()->GetCapacity(); i++)
	{
		if (position.x < app->pathfinding->GetLastPath()->At(i)->x)
		{
			Walking_Enemy_List.end->data->body->ApplyLinearImpulse({ 5.0f,0 }, { 0,0 }, true);
		}
		if (position.x > app->pathfinding->GetLastPath()->At(i)->x)
		{
			Walking_Enemy_List.end->data->body->ApplyLinearImpulse({ -5.0f,0 }, { 0,0 }, true);
		}
	}
	
	

	
		
	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update(dt);
}
