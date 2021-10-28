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
#include "ModulePhysics.h"
#include <stdio.h>
#include <time.h>

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
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = app->tex->Load("Assets/player.png");
	currentAnimation = &idleRightAnim;

	laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 830;
	position.y = 180;

	destroyed = false;


	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	PlayerLookingPosition = 2;

	playerTimer = 0;
	playerIdleAnimationTimer = 0;

	//srand(time(NULL));

	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	return ret;
}

bool ModulePlayer::Update(float dt)
{
	// Moving the player with the camera scroll
	//app->player->position.x += 1;

	playerTimer++;


	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT)
	{
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
		speed = 1;
		position.x -= speed;
		app->render->camera.x -= 3;
		PlayerLookingPosition = 1;
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT)
	{
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
		speed = 1;
		position.x += speed;
		app->render->camera.x += 3;
		PlayerLookingPosition = 2;
	}

	// If no up/down movement detected, set the current animation back to idle
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_IDLE)
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

	if ((PlayerLookingPosition == 1) && (position.x < app->render->camera.x / app->win->GetScale() + 190))
	{
		app->render->camera.x -= 5;
	}
	if ((PlayerLookingPosition == 2) && (position.x > app->render->camera.x / app->win->GetScale() + 140))
	{
		app->render->camera.x += 5;
	}

	/*
	if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT)
	{

		if (app->render->camera.x / SCREEN_SIZE + app->render->camera.w + speed < 1242)
		{

			if (position.x + 70 > app->render->camera.x / SCREEN_SIZE + app->render->camera.w - horizontalMargin)
			{
				app->render->camera.x += speed + (SCREEN_SIZE - 1);
			}

		}

	}
	if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT)
	{


		if (app->render->camera.x / SCREEN_SIZE - app->render->camera.w - speed < 1242)
		{

			if (position.x - 285 < app->render->camera.x / SCREEN_SIZE - app->render->camera.w + horizontalMargin)
			{
				app->render->camera.x -= speed + (SCREEN_SIZE - 1);
			}

		}
	}
	*/

	

	currentAnimation->Update();

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


	