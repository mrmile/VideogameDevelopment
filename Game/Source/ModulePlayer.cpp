#include "ModulePlayer.h"

#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Window.h"
//#include "ModuleFonts.h"
#include "Log.h"

#include "Scene.h"
#include "Map.h"
#include "ModulePhysics.h"
#include <stdio.h>
#include <time.h>

//ModulePlayer::ModulePlayer( bool start_enabled) : Module(start_enabled)


ModulePlayer::ModulePlayer()
{
	// idle left
	idleLeftAnim.PushBack({ 0, 167, 28, 33 });
	idleLeftAnim.PushBack({ 27, 167, 28, 33 });
	idleLeftAnim.PushBack({ 54, 167, 28, 33 });
	idleLeftAnim.PushBack({ 82, 167, 28, 33 });
	idleLeftAnim.PushBack({ 109, 167, 27, 33 });
	idleLeftAnim.PushBack({ 135, 167, 28, 33 });
	idleLeftAnim.PushBack({ 162, 167, 28, 33 });
	idleLeftAnim.PushBack({ 189, 167, 28, 33 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.15f;

	// idle left
	idleRightAnim.PushBack({ 190, 207, 28, 33 });
	idleRightAnim.PushBack({ 163, 207, 28, 33 });
	idleRightAnim.PushBack({ 136, 207, 28, 33 });
	idleRightAnim.PushBack({ 108, 207, 28, 33 });
	idleRightAnim.PushBack({ 82, 207, 27, 33 });
	idleRightAnim.PushBack({ 55, 207, 28, 33 });
	idleRightAnim.PushBack({ 28, 207, 28, 33 });
	idleRightAnim.PushBack({ 1, 207, 28, 33 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.15f;

	// idle left 2
	idleLeftAnim2.PushBack({ 0, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 27, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 53, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 79, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 105, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 131, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 157, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 131, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 157, 247, 27, 33 });
	idleLeftAnim2.PushBack({ 184, 247, 27, 33 });
	idleLeftAnim2.loop = true;
	idleLeftAnim2.speed = 0.15f;

	// idle right 2
	idleRightAnim2.PushBack({ 184, 287, 27, 33 });
	idleRightAnim2.PushBack({ 157, 287, 27, 33 });
	idleRightAnim2.PushBack({ 131, 287, 27, 33 });
	idleRightAnim2.PushBack({ 105, 287, 27, 33 });
	idleRightAnim2.PushBack({ 79, 287, 27, 33 });
	idleRightAnim2.PushBack({ 53, 287, 27, 33 });
	idleRightAnim2.PushBack({ 27, 287, 27, 33 });
	idleRightAnim2.PushBack({ 53, 287, 27, 33 });
	idleRightAnim2.PushBack({ 27, 287, 27, 33 });
	idleRightAnim2.PushBack({ 0, 287, 27, 33 });
	idleRightAnim2.loop = true;
	idleRightAnim2.speed = 0.15f;

	// move left
	leftAnim.PushBack({ 1, 7, 28, 33 });
	leftAnim.PushBack({ 28, 7, 28, 33 });
	leftAnim.PushBack({ 55, 7, 28, 33 });
	leftAnim.PushBack({ 82, 7, 28, 33 });
	leftAnim.PushBack({ 109, 7, 28, 33 });
	leftAnim.PushBack({ 136, 7, 28, 33 });
	leftAnim.PushBack({ 163, 7, 28, 33 });
	leftAnim.PushBack({ 190, 7, 28, 33 });
	leftAnim.PushBack({ 217, 7, 28, 33 });
	leftAnim.PushBack({ 244, 7, 28, 33 });
	leftAnim.loop = true;
	leftAnim.speed = 0.3f;

	// Move right
	rightAnim.PushBack({ 244, 47, 28, 33 });
	rightAnim.PushBack({ 217, 47, 28, 33 });
	rightAnim.PushBack({ 190, 47, 28, 33 });
	rightAnim.PushBack({ 163, 47, 28, 33 });
	rightAnim.PushBack({ 136, 47, 28, 33 });
	rightAnim.PushBack({ 109, 47, 28, 33 });
	rightAnim.PushBack({ 82, 47, 28, 33 });
	rightAnim.PushBack({ 55, 47, 28, 33 });
	rightAnim.PushBack({ 28, 47, 28, 33 });
	rightAnim.PushBack({ 1, 47, 28, 33 });
	rightAnim.loop = true;
	rightAnim.speed = 0.3f;

	// Run left
	leftRunAnim.PushBack({ 308, 7, 35, 33 });
	leftRunAnim.PushBack({ 343, 7, 36, 33 });
	leftRunAnim.loop = true;
	leftRunAnim.speed = 0.3f;

	// Run right
	rightRunAnim.PushBack({ 344, 47, 36, 33 });
	rightRunAnim.PushBack({ 308, 47, 36, 33 });
	rightRunAnim.loop = true;
	rightRunAnim.speed = 0.3f;

	// Jump left
	jumpLeftAnim.PushBack({ 1, 130, 26, 33 });
	jumpLeftAnim.loop = false;
	jumpLeftAnim.speed = 0.3f;

	// fall
	fallLeftAnim.PushBack({ 27, 130, 25, 33 });
	fallLeftAnim.PushBack({ 51, 130, 25, 33 });
	fallLeftAnim.loop = false;
	fallLeftAnim.speed = 0.3f;

	// Jump right
	jumpRightAnim.PushBack({ 52, 90, 28, 33 });
	jumpRightAnim.loop = false;
	jumpRightAnim.speed = 0.3f;

	// fall
	fallRightAnim.PushBack({ 28, 90, 25, 33 });
	fallRightAnim.PushBack({ 2, 90, 26, 33 });
	fallRightAnim.loop = false;
	fallRightAnim.speed = 0.3f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Awake()
{
	return true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = app->tex->Load("Assets/textures/player.png");
	currentAnimation = &idleRightAnim;

	jumpSound = app->audio->LoadFx("Assets/audio/fx/Jump.wav");

	//laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	position = app->map->MapToWorld(5, 21);
	//position.x = 0;
	//position.y = 0;

	//scale = 1
	// ofset x = 500
	// ofset y = 50

	//scale = 2
	// ofset Px = 1 = Cx = 2 
	// ofset Py = 1 = Cy = 2

	//app->render->camera.x = app->map->MapToWorld(32, 4100).x;
	//app->render->camera.y = app->map->MapToWorld(32, 4100).y;

	app->render->camera.x = app->map->MapToWorld(0, -15).x;
	app->render->camera.y = app->map->MapToWorld(0, -15).y;

	destroyed = false;

	Player = app->physics->CreatePlayerBox(position.x+14, position.y+16, 28, 33);

	TestingGround = app->physics->CreateColliderRectangle(app->map->MapToWorld(5, 26).x, app->map->MapToWorld(5, 26).y, 1000, 100);
	//TestingGround = app->physics->CreateColliderRectangle(0, 50, 1000, 100);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	PlayerLookingPosition = 2;

	playerTimer = 0;
	playerIdleAnimationTimer = 0;

	jump = false;

	//srand(time(NULL));

	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	return ret;
}

bool ModulePlayer::Update(float dt)
{

	playerTimer++;
	app->render->camera.x = -(Player->body->GetPosition().x * 100) + 640;
	//app->render->camera.x = -(Player->body->GetPosition().x * 100); <-- Este es el que se aplica al final
	//app->win->GetWindowSize()
	
	//LOG("Player %s", Player->body->GetPosition().x);
	//LOG("Camera %s", app->render->camera.x);

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT)
	{
		
		if (run == false)
		{
			if (Player->body->GetLinearVelocity().x >= -2) Player->body->ApplyLinearImpulse({ -5.0f,0 }, { 0,0 }, true);

			if (currentAnimation != &leftAnim)
			{
				leftRunAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}
		else if (run == true)
		{
			if (Player->body->GetLinearVelocity().x >= -4) Player->body->ApplyLinearImpulse({ -5.0f,0 }, { 0,0 }, true);

			if (currentAnimation != &leftRunAnim)
			{
				leftRunAnim.Reset();
				currentAnimation = &leftRunAnim;
			}
		}

		PlayerLookingPosition = 1;
		
	}
	
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT)
	{	
		
		if (run == false)
		{
			if (Player->body->GetLinearVelocity().x <= 2) Player->body->ApplyLinearImpulse({ 5.0f,0 }, { 0,0 }, true);

			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}
		}
		else if (run == true)
		{
			if (Player->body->GetLinearVelocity().x <= 4) Player->body->ApplyLinearImpulse({ 5.0f,0 }, { 0,0 }, true);

			if (currentAnimation != &rightRunAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightRunAnim;
			}
		}
		
		
		
		PlayerLookingPosition = 2;
		
	}

	if (app->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_DOWN && jump == false)
	{
		Player->body->ApplyLinearImpulse({ 0,-160 }, { 0,0 }, true);
		app->audio->PlayFx(jumpSound);
		//jump = true;
	}

	if (Player->body->GetLinearVelocity().y < 0)
	{
		jump = true;
	}

	if (Player->body->GetLinearVelocity().y == 0)
	{
		jump = false;
	}

	if (PlayerLookingPosition == 1 && jump == true)
	{
		if (Player->body->GetLinearVelocity().y < 0)
		{
			if (currentAnimation != &jumpLeftAnim)
			{
				jumpLeftAnim.Reset();
				currentAnimation = &jumpLeftAnim;
			}
		}
		if (Player->body->GetLinearVelocity().y > 0)
		{
			if (currentAnimation != &fallLeftAnim)
			{
				fallLeftAnim.Reset();
				currentAnimation = &fallLeftAnim;
			}
		}
	}
	if (PlayerLookingPosition == 2 && jump == true)
	{
		if (Player->body->GetLinearVelocity().y < 0)
		{
			if (currentAnimation != &jumpRightAnim)
			{
				jumpRightAnim.Reset();
				currentAnimation = &jumpRightAnim;
			}
		}
		if (Player->body->GetLinearVelocity().y > 0)
		{
			if (currentAnimation != &fallRightAnim)
			{
				fallRightAnim.Reset();
				currentAnimation = &fallRightAnim;
			}
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_X) == KeyState::KEY_REPEAT)
	{
		run = true;
	}
	else
	{
		run = false;
	}
	/*
	if (doubleJump == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN)
		{
			if (PlayerLookingPosition == 1)
			{
				Player->body->ApplyForce({ 0,-500 }, { 0,0 }, true);
				doubleJump = false;
			}
			if (PlayerLookingPosition == 2)
			{
				Player->body->ApplyForce({ 0,-500 }, { 0,0 }, true);
				doubleJump = false;
			}
		}
	}
	*/
	
	
	// If no up/down movement detected, set the current animation back to idle
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_IDLE && jump == false)
	{
		playerIdleAnimationTimer++;
		speed = 0;

		switch (PlayerLookingPosition)
		{
		case 1:
			if (playerIdleAnimationTimer <= 180)
			{
				if (currentAnimation != &idleLeftAnim)
				{
					idleLeftAnim.Reset();
					currentAnimation = &idleLeftAnim;
				}
			}
			else if (playerIdleAnimationTimer > 180) // <-- Should be random
			{
				if (currentAnimation != &idleLeftAnim2)
				{
					idleLeftAnim2.Reset();
					currentAnimation = &idleLeftAnim2;
				}
				if (playerIdleAnimationTimer >= 243) playerIdleAnimationTimer = 0; // <-- Should also be random
			}

			break;
		case 2:
			if (playerIdleAnimationTimer <= 180)
			{
				if (currentAnimation != &idleRightAnim)
				{
					idleRightAnim.Reset();
					currentAnimation = &idleRightAnim;
				}
			}
			else if (playerIdleAnimationTimer > 180) // <-- Should be random
			{
				if (currentAnimation != &idleRightAnim2)
				{
					idleRightAnim2.Reset();
					currentAnimation = &idleRightAnim2;
				}
				if (playerIdleAnimationTimer >= 243) playerIdleAnimationTimer = 0; // <-- Should also be random
			}

			break;
		}
	}
	
	/*
	if ((PlayerLookingPosition == 1) && (position.x < app->render->camera.x / app->win->GetScale() + 190))
	{
		app->render->camera.x -= 5;
	}
	if ((PlayerLookingPosition == 2) && (position.x > app->render->camera.x / app->win->GetScale() + 140))
	{
		app->render->camera.x += 5;
	}
	*/
	

	currentAnimation->Update();

	Player->GetPosition(position.x, position.y);
	
	
	return true;
}

bool ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		
	}

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &rect);

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	//app->fonts->BlitText(58, 248, scoreFont, scoreText);

	//app->fonts->BlitText(150, 248, scoreFont, "this is just a font test message");

	return true;
}

bool ModulePlayer::CleanUp() // Implementar???
{
	return true;
}
