#include "ModuleCollisions.h"
#include "Collider.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Enemies.h"
#include "ModulePhysics.h"
#include "Enemy.h"
#include "App.h"



Enemy::Enemy(int x, int y) : position(x, y)
{

}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update(float dt)
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x + 5, position.y + 5);



}

void Enemy::Draw()
{
	if (enemyHit == false)
	{
		if (currentAnim != nullptr)
			app->render->DrawTexture(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
	enemyHit = false; // For visual hit effect
}

void Enemy::OnCollision(Collider* c2)
{

}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if(collider != nullptr)
	{
		collider->pendingToDelete = true; 
	}
		
}