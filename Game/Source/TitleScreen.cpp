#include "TitleScreen.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneForest.h"
#include "SceneCastle.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "Enemies.h"
#include "Enemy.h"
#include "ModuleParticles.h"

#include "Defs.h"
#include "Log.h"

TitleScreen::TitleScreen(bool start_enabled) : Module(start_enabled)
{
	name.Create("TitleScreen");
}

TitleScreen::~TitleScreen()
{
}

bool TitleScreen::Awake()
{
	LOG("TitleScreen Scene");
	bool ret = true;

	return ret;

	return true;
}

bool TitleScreen::Start()
{
	titleScreen = app->tex->Load("Assets/textures/titleScreen3.png");
	startButton = app->tex->Load("Assets/textures/startButton3.png");
	loading = app->tex->Load("Assets/textures/loadingScreen3.png");

	// Load music
	//app->audio->PlayMusic("Assets/audio/music/fortress.ogg");

	sceneTimer = 0;
	delay = 0;
	transition = false;

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	return true;
}

bool TitleScreen::PreUpdate()
{


	return true;
}

bool TitleScreen::Update(float dt)
{
	sceneTimer++;

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		transition = true;
	}

	if (transition == true) delay++;

	if (delay > 90 && delay <= 91)
	{
		//app->physics->Enable();
		app->collisions->Enable();
		app->map->Enable();
		app->particles->Enable();
		app->sceneForest->Enable();
		app->player->Enable();
		app->enemies->Enable();
		

		app->titleScreen->Disable();
		//app->fade->FadeToBlack(app->titleScreen, app->sceneCastle, 60);
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		app->render->camera.y -= 5;

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		app->render->camera.y += 5;

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		app->render->camera.x -= 5;

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		app->render->camera.x += 5;

	return true;
}

bool TitleScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->render->DrawTexture(titleScreen, 0, 0, NULL);
	if ((sceneTimer / 30) % 2 == 0) app->render->DrawTexture(startButton, 85, 118, NULL);

	if (transition == true) app->render->DrawTexture(loading, 0, 0, NULL);

	return ret;

	return true;
}

bool TitleScreen::CleanUp()
{
	app->tex->UnLoad(titleScreen);
	app->tex->UnLoad(startButton);
	app->tex->UnLoad(loading);

	return true;
}
