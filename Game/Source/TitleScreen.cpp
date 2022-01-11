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
#include "ModuleFonts.h"
#include "GuiManager.h"

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

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	startButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Start Button", { 110, 170, 265, 15 }, this); //Observer (this): Class that will receive the event
	
	
	
	
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

	

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		app->render->camera.y -= 5;

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		app->render->camera.y += 5;

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		app->render->camera.x -= 5;

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		app->render->camera.x += 5;

	if (MainMenu == true)
	{
		startButton_->canClick = true;
		continueButton_->canClick = true;
		optionsButton_->canClick = true;
		creditsButton_->canClick = true;
		exitButton_->canClick = true;
	}
	if (OptionsMenu == true)
	{

	}


	if (MainMenu == true)
	{
		//START BUTTON
		if (startButton_->state == GuiControlState::PRESSED)
		{
			transition = true;
		}
		//CONTINUE BUTTON
		if (continueButton_->state == GuiControlState::PRESSED)
		{
			app->LoadGameRequest();
			transition = true;
		}
		//SETTINGS BUTTON
		if (optionsButton_->state == GuiControlState::PRESSED)
		{
			MainMenu = false;
			OptionsMenu = true;
		}
		//CREDITS BUTTON
		if (creditsButton_->state == GuiControlState::PRESSED)
		{
			transitionCredits = true;
		}
		//EXIT BUTTON
		if (exitButton_->state == GuiControlState::PRESSED)
		{
			return false;
		}
		if (transitionCredits == true) delayToCredits++;

		if (delayToCredits > 90 && delayToCredits <= 91)
		{
			//app->credits->Enable();    NEED TO ADD THE CREDITS SCENE
			app->player->Enable();
			app->fonts->Enable();

			app->titleScreen->Disable();
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
			app->fonts->Enable();

			app->titleScreen->Disable();
			//app->fade->FadeToBlack(app->titleScreen, app->sceneCastle, 60);
		}
	}

	if (OptionsMenu == true)
	{
		//RETURN TO MAIN MENU BUTTON
		if (returnButton_->state == GuiControlState::PRESSED)
		{
			OptionsMenu = false;
			MainMenu = true;
		}
	}
	
	return true;
}

bool TitleScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->render->DrawTexture(titleScreen, 0, 0, NULL);

	//if (((sceneTimer / 30) % 2 == 0)&& button1->state==GuiControlState::PRESSED) button1->Draw(app->render);
	
	
	startButton_->SetTexture(startButton);
	
	if (MainMenu == true)
	{
		startButton_->Draw(app->render);
		continueButton_->Draw(app->render);
		optionsButton_->Draw(app->render);
		creditsButton_->Draw(app->render);
		exitButton_->Draw(app->render);
	}
	if (OptionsMenu == true)
	{
		returnButton_->Draw(app->render);
	}
	

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

bool TitleScreen::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1)
		{
			LOG("Click on button 1");
		}

		if (control->id == 2)
		{
			LOG("Click on button 2");
		}

	}
	//Other cases here

	default: break;
	}

	return true;
}