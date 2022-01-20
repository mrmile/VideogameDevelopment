#include "ModulePlayer.h"

#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
#include "Enemies.h"
#include "Enemy.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Window.h"
//#include "ModuleFonts.h"
#include "Log.h"

#include "SceneForest.h"
#include "SceneCastle.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Audio.h"
#include "TitleScreen.h"
#include "ModuleFonts.h"

#include <stdio.h>
#include <time.h>
#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
#include <Optick/include/optick.h>
using namespace std;

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	name.Create("player");

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

	// hover left
	hoverLeftAnim.PushBack({ 110, 92, 24, 34 });
	hoverLeftAnim.PushBack({ 133, 92, 25, 34 });
	hoverLeftAnim.PushBack({ 158, 92, 26, 34 });
	hoverLeftAnim.loop = true;
	hoverLeftAnim.speed = 0.3f;

	// hover right
	hoverRightAnim.PushBack({ 158, 132, 24, 34 });
	hoverRightAnim.PushBack({ 135, 132, 24, 34 });
	hoverRightAnim.PushBack({ 109, 132, 26, 34 });
	hoverRightAnim.loop = true;
	hoverRightAnim.speed = 0.3f;

	// die left
	dieLeft.PushBack({ 429, 9, 28, 40 });
	dieLeft.PushBack({ 456, 9, 28, 40 });
	dieLeft.loop = false;
	dieLeft.speed = 0.2f;

	//die right
	dieRight.PushBack({ 455, 59, 28, 40 });
	dieRight.PushBack({ 428, 59, 28, 40 });
	dieRight.loop = false;
	dieRight.speed = 0.2f;
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
	coinsForScore = app->tex->Load("Assets/textures/coins_score.png");
	livesForScore = app->tex->Load("Assets/textures/lives_score.png");
	currentAnimation = &idleRightAnim;

	jumpSound = app->audio->LoadFx("Assets/audio/fx/Jump.wav");
	hoverSound = app->audio->LoadFx("Assets/audio/fx/Flutter_s.wav");
	hoverSoundL = app->audio->LoadFx("Assets/audio/fx/Flutter_l.wav");
	dead = app->audio->LoadFx("Assets/audio/fx/dead.wav");
	damaged = app->audio->LoadFx("Assets/audio/fx/Whsiup.wav");
	halfWayPoint = app->audio->LoadFx("Assets/audio/fx/Advice.wav");
	coin = app->audio->LoadFx("Assets/audio/fx/Coin.wav");
	recoverLifePowerUp = app->audio->LoadFx("Assets/audio/fx/itemGet.wav");
	levelClear = app->audio->LoadFx("Assets/audio/fx/levelClear.wav");
	firework = app->audio->LoadFx("Assets/audio/fx/fireworks.wav");
	paused = app->audio->LoadFx("Assets/audio/fx/pause.wav");

	//laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	//position = app->map->MapToWorld(5, 21); // En el load objects
	b2VelocitySet.x = 0;
	b2VelocitySet.y = -0.5f;
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

	destroyed = false;
	deletePlayer = false;
	checkPointReached = false;

	collider = app->collisions->AddCollider({ position.x + 5, position.y + 3, 28, 23 }, Collider::Type::PLAYER, this); //{ position.x + 5, position.y + 3, 28, 33 
	colliderFeet = app->collisions->AddCollider({ position.x + 5, position.y + 23, 18, 10 }, Collider::Type::PLAYER_FEET, this);

	Player = app->physics->CreatePlayerBox(position.x, position.y, 28, 33);
	//app->physics->CreateRectangleSensor(position.x, position.y + 16, 28, 1);
	//Player = app->physics->CreatePlayerCircle(position.x, position.y, 20);
	

	//TestingGround = app->physics->CreateColliderRectangle(app->map->MapToWorld(5, 26).x, app->map->MapToWorld(5, 26).y, 1000, 100); // Tendria que estar en Scene.cpp
	//TestingGround = app->physics->CreateColliderRectangle(0, 50, 1000, 100);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	//LOADING FONT FOR GAME
	char lookupTable[] = { "0123456789" };
	scoreFont = app->fonts->Load("Assets/textures/numbers.png", lookupTable, 1);

	PlayerLookingPosition = 2;

	playerTimer = 0;
	playerIdleAnimationTimer = 0;
	hoverTimer = 0;
	destroyedDelay = 0;
	winDelay = 0;
	TransationToTilteDelay = 0;
	jump = false;
	createPlayer = false;

	playerWin = false;

	layerZeroReveal = false;

	//srand(time(NULL));

	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	playerHP = 100;
	invincibleDelay = 120;
	playerFPS = 0;

	pauseMenu = false;
	
	return ret;
}

bool ModulePlayer::Update(float dt)
{
	
	if (pauseMenu==true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
		return true;
	}
	if (pauseMenu == false)
	{
		playerFPS++;
		invincibleDelay++;

		//OPTICK_EVENT();
		collider->SetPos(position.x, position.y);
		colliderFeet->SetPos(position.x + 5, position.y + 23);
		playerTimer++;
		//------------------------------------------------------------------------------------------------------------------------------------------
		if (destroyed == false && playerWin == false && app->sceneCastle->godMode == false && app->sceneForest->godMode == false)
		{
			if (app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
			{

				if (run == false)
				{
					if (Player->body->GetLinearVelocity().x >= -2) Player->body->ApplyLinearImpulse({ -5.0f,0 }, { 0,0 }, true);

					if (currentAnimation != &leftAnim && hover == false)
					{
						leftAnim.Reset();
						currentAnimation = &leftAnim;
					}
				}
				else if (run == true)
				{
					if (Player->body->GetLinearVelocity().x >= -4) Player->body->ApplyLinearImpulse({ -5.0f,0 }, { 0,0 }, true);

					if (currentAnimation != &leftRunAnim && hover == false)
					{
						leftRunAnim.Reset();
						currentAnimation = &leftRunAnim;
					}
				}

				PlayerLookingPosition = 1;

			}

			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
			{

				if (run == false)
				{
					if (Player->body->GetLinearVelocity().x <= 2) Player->body->ApplyLinearImpulse({ 5.0f,0 }, { 0,0 }, true);

					if (currentAnimation != &rightAnim && hover == false)
					{
						rightAnim.Reset();
						currentAnimation = &rightAnim;
					}
				}
				else if (run == true)
				{
					if (Player->body->GetLinearVelocity().x <= 4) Player->body->ApplyLinearImpulse({ 5.0f,0 }, { 0,0 }, true);

					if (currentAnimation != &rightRunAnim && hover == false)
					{
						rightRunAnim.Reset();
						currentAnimation = &rightRunAnim;
					}
				}



				PlayerLookingPosition = 2;

			}

			if ((app->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN) && jump == false && inTheAir == false)
			{
				Player->body->ApplyLinearImpulse({ 0,-160 }, { 0,0 }, true);
				app->audio->PlayFx(jumpSound);
				//jump = true;
			}

			if (Player->body->GetLinearVelocity().y < 0 && (app->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN))
			{
				jump = true;
			}

			if (Player->body->GetLinearVelocity().y == 0 && app->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_IDLE && app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_IDLE)
			{
				jump = false;
				inTheAir = false;
				hover = false;
				hoverTimer = 0;
			}



			if ((app->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_REPEAT) && Player->body->GetLinearVelocity().y > 0) // <--
			{
				hover = true;
				run = false;

				if (hoverTimer < 75)
				{
					Player->body->ApplyForce({ 0,-1800 }, { 0,0 }, true);
					if (hoverTimer < 2 && hover == true) app->audio->PlayFx(hoverSound);
					if (hoverTimer > 30 && hoverTimer < 34 && hover == true) app->audio->PlayFx(hoverSound);
				}

				if (PlayerLookingPosition == 1)
				{
					if (Player->body->GetLinearVelocity().x < -1) Player->body->ApplyLinearImpulse({ 3.0f,0 }, { 0,0 }, true);
					if (currentAnimation != &hoverLeftAnim)
					{
						hoverLeftAnim.Reset();
						currentAnimation = &hoverLeftAnim;
					}
				}
				if (PlayerLookingPosition == 2)
				{
					if (Player->body->GetLinearVelocity().x > 1) Player->body->ApplyLinearImpulse({ -3.0f,0 }, { 0,0 }, true);
					if (currentAnimation != &hoverRightAnim)
					{
						hoverRightAnim.Reset();
						currentAnimation = &hoverRightAnim;
					}
				}
			}
			if (app->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_UP && app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_UP)
			{
				hover = false;
			}
			if (hover == true)
			{
				hoverTimer++;
			}
			if (hoverTimer > 75)
			{
				hover = false;
			}

			if (PlayerLookingPosition == 1 && jump == true && hover == false)
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
			if (PlayerLookingPosition == 2 && jump == true && hover == false)
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

			if ((app->input->GetKey(SDL_SCANCODE_X) == KeyState::KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_REPEAT))
			{
				if (hover == false) run = true;
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
				&& app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_IDLE
				&& jump == false && Player->body->GetLinearVelocity().x == 0)
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
		}
		//------------------------------------------------------------------------------------------------------------------------------------------
		if (destroyed == false && playerWin == false && (app->sceneCastle->godMode == true || app->sceneForest->godMode == true))
		{
			if (app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_A))
			{

				if (run == false)
				{
					if (Player->body->GetLinearVelocity().x >= -2) Player->body->ApplyLinearImpulse({ -5.0f,0 }, { 0,0 }, true);

					if (currentAnimation != &leftAnim && hover == false)
					{
						leftRunAnim.Reset();
						currentAnimation = &leftAnim;
					}
				}
				else if (run == true)
				{
					if (Player->body->GetLinearVelocity().x >= -4) Player->body->ApplyLinearImpulse({ -5.0f,0 }, { 0,0 }, true);

					if (currentAnimation != &leftRunAnim && hover == false)
					{
						leftRunAnim.Reset();
						currentAnimation = &leftRunAnim;
					}
				}

				PlayerLookingPosition = 1;

			}

			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D))
			{

				if (run == false)
				{
					if (Player->body->GetLinearVelocity().x <= 2) Player->body->ApplyLinearImpulse({ 5.0f,0 }, { 0,0 }, true);

					if (currentAnimation != &rightAnim && hover == false)
					{
						rightAnim.Reset();
						currentAnimation = &rightAnim;
					}
				}
				else if (run == true)
				{
					if (Player->body->GetLinearVelocity().x <= 4) Player->body->ApplyLinearImpulse({ 5.0f,0 }, { 0,0 }, true);

					if (currentAnimation != &rightRunAnim && hover == false)
					{
						rightAnim.Reset();
						currentAnimation = &rightRunAnim;
					}
				}



				PlayerLookingPosition = 2;

			}

			if ((app->input->GetKey(SDL_SCANCODE_Z) == KeyState::KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN) && Player->body->GetLinearVelocity().y >= -2)
			{
				Player->body->ApplyLinearImpulse({ 0,-160 }, { 0,0 }, true);
				app->audio->PlayFx(jumpSound);

			}

			if (app->input->GetKey(SDL_SCANCODE_X) == KeyState::KEY_REPEAT)
			{
				if (hover == false) run = true;
			}
			else
			{
				run = false;
			}

			// If no up/down movement detected, set the current animation back to idle
			if (app->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_IDLE
				&& app->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_IDLE
				&& app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_IDLE
				&& app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_IDLE
				&& jump == false && Player->body->GetLinearVelocity().x == 0)
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
		}
		//------------------------------------------------------------------------------------------------------------------------------------------
		if (destroyed == true)
		{
			if (destroyedDelay < 1)
			{
				//Mix_PauseMusic();
				app->audio->PlayFx(dead);
				lives--;
			}
			if (PlayerLookingPosition == 1)
			{
				if (destroyedDelay < 60) Player->body->SetLinearVelocity(b2VelocitySet);

				if (currentAnimation != &dieLeft)
				{
					dieLeft.Reset();
					currentAnimation = &dieLeft;
				}
			}
			if (PlayerLookingPosition == 2)
			{
				if (destroyedDelay < 60) Player->body->SetLinearVelocity(b2VelocitySet);


				if (currentAnimation != &dieRight)
				{
					dieRight.Reset();
					currentAnimation = &dieRight;
				}
			}
		}
		//------------------------------------------------------------------------------------------------------------------------------------------
		if (playerWin == true)
		{
			if (winDelay < 1)
			{
				//Mix_PauseMusic();
				app->audio->PlayFx(firework);
			}
			if (PlayerLookingPosition == 1)
			{

			}
			if (PlayerLookingPosition == 2)
			{

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
		
		/*
		if (lives == 0)
		{
			//SDL_Delay(600); <-- Esto pausa el juego completo no hace que se espere algo.
			
			app->titleScreen->SavedGame = false;
			app->titleScreen->Enable();
			app->CheckGameRequest();
			app->titleScreen->MainMenu = true;
			
			app->map->Disable();
			app->collisions->Disable();
			app->particles->Disable();
			app->sceneForest->Disable();
			app->player->Disable();
			app->enemies->Disable();
			app->fonts->Disable();
			
		}
		*/

		currentAnimation->Update();

		Player->GetPosition(position.x, position.y);

		//cout << "PosX: " << position.x << " PosY: " << position.y << endl;

		
	}
	
	
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN && app->player->destroyed == false && app->player->playerWin == false)
	{
		app->audio->PlayFx(paused);
		pauseMenu = !pauseMenu;
	}

	
	//------------------------------------------------------------------------------------------------------------------------------------------
	return true;
}

bool ModulePlayer::PostUpdate()
{
	
		if (destroyed == true)
		{
			destroyedDelay++;
		}
		if (playerWin == true)
		{
			winDelay++;
		}

		if (invincibleDelay <= 120)
		{
			if ((playerFPS / 5) % 2 == 0)
			{
				SDL_Rect rect = currentAnimation->GetCurrentFrame();
				app->render->DrawTexture(texture, position.x, position.y, &rect);
			}
		}
		else
		{
			SDL_Rect rect = currentAnimation->GetCurrentFrame();
			app->render->DrawTexture(texture, position.x, position.y, &rect);
		}

		// Draw UI (score) --------------------------------------
		sprintf_s(scoreText, 10, "%5d", score);


		SDL_Rect quad;
		quad = { 5, 10, playerHP, 10 };

		SDL_Rect quad2;
		quad2 = { 5, 10, 100, 10 };

		SDL_Rect bgquad;
		bgquad = { 3, 8, 104, 14 };
		app->render->DrawRectangle2(bgquad, 255, 255, 255, 255, 0.0f, true);
		app->render->DrawRectangle2(quad2, 200, 200, 200, 255, 0.0f, true);
		//app->render->DrawRectangle(bgquad, 255, 255, 255, 165, true, true);
		if (playerHP >= 100)
		{
			playerHP = 100;
			app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
		}
		else if (playerHP > 50)
		{
			app->render->DrawRectangle2(quad, 120, 255, 0, 255, 0.0f, true);
		}
		else if (playerHP > 20 && playerHP <= 50)
		{
			app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
		}
		else
		{
			if ((playerFPS / 5) % 2 == 0)
			{
				app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);
			}
			else
			{
				app->render->DrawRectangle2(quad, 255, 150, 0, 255, 0.0f, true);
			}

		}

		if (app->sceneCastle->playerRestart == true)
		{
			//horizontalCB = true;
			app->sceneCastle->sceneTimer = 0;

			//if (checkPointReached == false) position = app->map->MapToWorld(32, 14);
				//if (checkPointReached == true) position = app->map->MapToWorld(32, 14);
			score = 0;
			app->player->Disable();
			app->sceneCastle->Disable();
			app->collisions->Disable();
			app->map->Disable();
			app->enemies->Disable();
			app->particles->Disable();
			app->fonts->Disable();

			if (checkPointReached == false) position = app->map->playerStartPos;
			if (checkPointReached == true) position = app->map->playerCheckPointPos;

			app->player->Enable();
			app->sceneCastle->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->enemies->Enable();
			app->particles->Enable();
			app->fonts->Enable();

			app->sceneCastle->playerRestart = false;
		}

		if (app->sceneForest->playerRestart == true)
		{
			//horizontalCB = true;
			app->sceneForest->sceneTimer = 0;

			//if (checkPointReached == false) position = app->map->MapToWorld(32, 14);
				//if (checkPointReached == true) position = app->map->MapToWorld(32, 14);
			app->player->Disable();
			app->sceneForest->Disable();
			app->collisions->Disable();
			app->map->Disable();
			app->enemies->Disable();
			app->particles->Disable();
			app->fonts->Disable();

			if (checkPointReached == false) position = app->map->playerStartPos;
			if (checkPointReached == true) position = app->map->playerCheckPointPos;

			app->player->Enable();
			app->sceneForest->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->enemies->Enable();
			app->particles->Enable();
			app->fonts->Enable();

			app->sceneForest->playerRestart = false;
		}

		if (app->titleScreen->toTitleScreen == true)
		{
			app->titleScreen->SavedGame = false;
			app->titleScreen->Enable();
			app->CheckGameRequest();

			app->map->Disable();
			app->collisions->Disable();
			app->particles->Disable();
			app->sceneForest->Disable();
			app->player->Disable();
			app->enemies->Disable();
			app->fonts->Disable();

			app->titleScreen->toTitleScreen = false;
		}

		// TODO 3: Blit the text of the score in at the bottom of the screen
		app->render->DrawTexture2(coinsForScore, 400, 7, NULL);
		app->fonts->BlitText(350, 10, scoreFont, scoreText);
		//app->fonts->BlitText(150, 248, scoreFont, "this is just a font test message");

		return true;
	
	
}

bool ModulePlayer::CleanUp()
{
	app->tex->UnLoad(texture);
	//deletePlayer = true;
	app->player->Player->body->DestroyFixture(app->player->Player->body->GetFixtureList());
	//app->collisions->RemoveCollider(app->player->collider);
	//app->collisions->RemoveCollider(app->player->colliderFeet);

	return true;
}

bool ModulePlayer::LoadState(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	score = data.child("atributes").attribute("score").as_int();
	playerHP = data.child("atributes").attribute("hp").as_int();
	lives = data.child("atributes").attribute("lives").as_int();


	if (app->player->IsEnabled() == true)
	{
		app->player->Player->body->DestroyFixture(app->player->Player->body->GetFixtureList());

		Player = app->physics->CreatePlayerBox(position.x + 28 / 2, position.y + 33 / 2, 28, 33);
	}
	
	
	//b2Filter b;
	//b.categoryBits = 0x0001;
	//b.maskBits = 0x0001 | 0x0002;
	//Player->body->GetFixtureList()->SetFilterData(b);
	createPlayer = false;

	//if (app->player->horizontalCB == false && app->sceneCastle->sceneTimer > 1) app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 630;

	return true;
}

// L02: DONE 8: Create a method to save the state of the renderer
// Save Game State
bool ModulePlayer::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node playerpos = data.append_child("position");
	pugi::xml_node playerAtributes = data.append_child("atributes");
	
	playerpos.append_attribute("x") = position.x;
	playerpos.append_attribute("y") = position.y;
	playerAtributes.append_attribute("score") = score;
	playerAtributes.append_attribute("hp") = playerHP;
	playerAtributes.append_attribute("lives") = lives;


	return true;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (app->sceneCastle->godMode == false && app->sceneForest->godMode == false && destroyed == false && playerWin == false)
	{
		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY) && destroyed == false && invincibleDelay >= 120)
		{

			playerHP -= 10;
			if (playerHP < 0) playerHP = 0;
			invincibleDelay = 0;
			if (playerHP != 0) app->audio->PlayFx(damaged);

			if (playerHP <= 0)
			{
				invincibleDelay = 121;
				playerHP = 0;
				//app->audio->PlayFx(dead);
				destroyed = true;

			}


		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::H_CB) // HORIZONTAL_CAMERA_BOUND = H_CB
		{
			if (horizontalCB == false)
			{
				horizontalCB = true;
			}
		}
		else if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type != Collider::Type::H_CB)
		{
			if (horizontalCB == true)
			{
				horizontalCB = false;
			}
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::V_CB) // VERTICAL_CAMERA_BOUND = V_CB
		{
			if (verticalCB == false)
			{
				verticalCB = true;
			}
		}
		else if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type != Collider::Type::V_CB)
		{
			if (verticalCB == true)
			{
				verticalCB = false;
			}
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::B_CB) // BIDIMENSIONAL_CAMERA_BOUND = B_CB
		{
			if (bidimensionalCB == false)
			{
				bidimensionalCB = true;
			}
		}
		else if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type != Collider::Type::B_CB)
		{
			if (bidimensionalCB == true)
			{
				bidimensionalCB = false;
			}
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::LAYER_ZERO)
		{
			if (layerZeroReveal == false)
			{
				layerZeroReveal = true;
			}
		}
		else if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type != Collider::Type::LAYER_ZERO)
		{
			if (layerZeroReveal == true)
			{
				layerZeroReveal = false;
			}
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::LAVA)
		{
			playerHP -= 100;
			if (playerHP < 0) playerHP = 0;
			invincibleDelay = 0;
			if (playerHP != 0) app->audio->PlayFx(damaged);

			if (playerHP <= 0)
			{
				invincibleDelay = 121;
				playerHP = 0;
				//app->audio->PlayFx(dead);
				destroyed = true;

			}
		}
		
		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::INSTANT_DEATH)
		{
			playerHP -= 100;
			if (playerHP < 0) playerHP = 0;
			invincibleDelay = 0;
			if (playerHP != 0) app->audio->PlayFx(damaged);

			if (playerHP <= 0)
			{
				invincibleDelay = 121;
				playerHP = 0;
				//app->audio->PlayFx(dead);
				destroyed = true;

			}
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::RECOVER_LIFE_POWER_UP)
		{
			playerHP += 10;
			if (playerHP > 100) playerHP = 100;
			app->audio->PlayFx(recoverLifePowerUp);
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::COIN)
		{
			score += 5;
			//if (playerScore > 1000) playerScore = 1000;
			app->audio->PlayFx(coin);
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::CHECKPOINT)
		{
			score += 10;
			//if (playerScore > 1000) playerScore = 1000;
			app->audio->PlayFx(halfWayPoint);
			app->titleScreen->SavedGame = true;
			app->SaveGameRequest();
			saved_game = true;
			checkPointReached = true;
		}

		if ((c1->type == Collider::Type::PLAYER || c1->type == Collider::Type::PLAYER_FEET) && c2->type == Collider::Type::GOAL_POINT)
		{
			//playerScore += 10;
			//if (playerScore > 1000) playerScore = 1000;
			app->audio->PlayFx(levelClear);
			app->titleScreen->SavedGame = false;
			app->SaveGameRequest();
			playerWin = true;

			app->particles->AddParticle(app->particles->enemyDefeat, app->map->goalPoolPos.x, app->map->goalPoolPos.y - 5, Collider::NONE);
			app->particles->AddParticle(app->particles->firework1, app->map->goalPoolPos.x + 6, app->map->goalPoolPos.y - 8, Collider::NONE, 6);
			app->particles->AddParticle(app->particles->firework2, app->map->goalPoolPos.x - 10, app->map->goalPoolPos.y + 4, Collider::NONE, 12);
			app->particles->AddParticle(app->particles->firework3, app->map->goalPoolPos.x + 2, app->map->goalPoolPos.y - 6, Collider::NONE, 18);

		}
	}
}
