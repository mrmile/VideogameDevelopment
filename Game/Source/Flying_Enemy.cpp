#include "Flying_Enemy.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "Enemies.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "Input.h"

Flying_Enemy::Flying_Enemy(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHP = 2;
	//HERE WE ADD THE ANIMATIONS WITH GIMP

	//Have the Soldiers describe a path in the screen taking into account the collisions


	collider = app->collisions->AddCollider({ position.x, position.y, 20, 30 }, Collider::Type::ENEMY, (Module*)app->enemies);
	//ALSO NEED TO ADD THE BOX2D PHYSICS


}

void Flying_Enemy::Update()
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT








	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
