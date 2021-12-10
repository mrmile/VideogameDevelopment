#include "ModuleParticles.h"

#include "App.h"

#include "Textures.h"
#include "Render.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = app->tex->Load("Assets/textures/particles.png");

	enemyDefeat.anim.PushBack({ 8, 16, 20, 20 });
	enemyDefeat.anim.PushBack({ 29, 16, 20, 20 });
	enemyDefeat.anim.PushBack({ 49, 16, 20, 20 });
	enemyDefeat.anim.PushBack({ 76, 16, 20, 20 });
	enemyDefeat.anim.PushBack({ 102, 16, 20, 20 });
	enemyDefeat.speed.x = 0;
	enemyDefeat.speed.y = 0;
	enemyDefeat.anim.loop = false;
	enemyDefeat.anim.speed = 0.15f;

	coin.anim.PushBack({ 13, 51, 12, 16 });
	coin.anim.PushBack({ 33, 51, 12, 16 });
	coin.anim.PushBack({ 53, 51, 12, 16 });
	coin.anim.PushBack({ 73, 51, 12, 16 });
	coin.speed.x = 0;
	coin.speed.y = 0;
	coin.anim.loop = true;
	coin.anim.speed = 0.15f;

	lifeRecoverPowerUp.anim.PushBack({ 51, 81, 19, 18 });
	lifeRecoverPowerUp.speed.x = 0;
	lifeRecoverPowerUp.speed.y = 0;
	lifeRecoverPowerUp.anim.loop = true;
	lifeRecoverPowerUp.anim.speed = 0.15f;

	checkPoint.anim.PushBack({ 14, 128, 22, 30 });
	checkPoint.anim.PushBack({ 36, 128, 22, 30 });
	checkPoint.anim.PushBack({ 58, 128, 22, 30 });
	checkPoint.anim.PushBack({ 80, 128, 22, 30 });
	checkPoint.anim.PushBack({ 103, 128, 22, 30 });
	checkPoint.speed.x = 0;
	checkPoint.speed.y = 0;
	checkPoint.anim.loop = true;
	checkPoint.anim.speed = 0.15f;

	checkPointGrabbed.anim.PushBack({ 137, 129, 22, 30 });
	checkPointGrabbed.anim.PushBack({ 157, 129, 22, 30 });
	checkPointGrabbed.speed.x = 0;
	checkPointGrabbed.speed.y = 0;
	checkPointGrabbed.anim.loop = true;
	checkPointGrabbed.anim.speed = 0.15f;

	return true;
}

bool ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
	
}

bool ModuleParticles::Update(float dt)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return true;
}

bool ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			app->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return true;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = app->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}