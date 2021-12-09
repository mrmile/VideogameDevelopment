#include "ModuleCollisions.h"
#include "ModulePlayer.h"
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
		collider->SetPos(position.x, position.y);

	EnemyCounter++;

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
	if (enemyHit == false && EnemyCounter>2)
	{
		if (c2->type == Collider::Type::PLAYER_FEET)
		{
			app->player->Player->body->ApplyLinearImpulse({ 0.0f,-150.0f }, { 0.0f,0.0f }, true);
			enemyHit = true;
			app->audio->PlayFx(app->enemies->enemyDestroyedFx);
			EnemyCounter = 0;
			EnemyHP -= 1;
		}
	}
	enemyHit = false;
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if(collider != nullptr)
	{
		collider->pendingToDelete = true; 
	}
		
}