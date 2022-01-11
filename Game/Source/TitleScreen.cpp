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
	titleScreen2 = app->tex->Load("Assets/textures/island.png");
	loading = app->tex->Load("Assets/textures/loadingScreen3.png");
	startButton = app->tex->Load("Assets/textures/GUI/startButton.png");
	continueButton = app->tex->Load("Assets/textures/GUI/continueButton.png");
	optionsButton = app->tex->Load("Assets/textures/GUI/optionsButton.png");
	creditsButton = app->tex->Load("Assets/textures/GUI/creditsButton.png");
	exitButton = app->tex->Load("Assets/textures/GUI/exitButton.png");
	returnButton = app->tex->Load("Assets/textures/GUI/returnButton.png");
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/fortress.ogg");

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	startButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Start Button", { 105, 120, 108, 35 }, this); //Observer (this): Class that will receive the event
	continueButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Continue Button", { 105, 160, 108, 35 }, this);
	optionsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Options Button", { 105, 200, 108, 35 }, this);
	creditsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits Button", { 215, 120, 108, 35 }, this);
	exitButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Exit Button", { 215, 160, 108, 35 }, this);
	returnButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Return Button", { 10, 10, 71, 35 }, this);
	

	
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
		returnButton_->canClick = true;
	}


	if (MainMenu == true)
	{
		
		//START BUTTON
		if (startButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(startButton_);
		}
		//CONTINUE BUTTON
		if (continueButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(continueButton_);
		}
		//SETTINGS BUTTON
		if (optionsButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(optionsButton_);
		}
		//CREDITS BUTTON
		if (creditsButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(creditsButton_);
		}
		//EXIT BUTTON
		if (exitButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(exitButton_);
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
			OnGuiMouseClickEvent(returnButton_);
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
	continueButton_->SetTexture(continueButton);
	optionsButton_->SetTexture(optionsButton);
	creditsButton_->SetTexture(creditsButton);
	exitButton_->SetTexture(exitButton);
	returnButton_->SetTexture(returnButton);

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
		//app->render->DrawTexture(titleScreen2, 0, 0, NULL);
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
			transition = true;
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

		if (control->id == 2)
		{
			//app->LoadGameRequest();
			transition = true;
		}
		if (control->id == 3)
		{
			MainMenu = false;
			OptionsMenu = true;
		}

		if (control->id == 4)
		{
			transitionCredits = true;
			if (transitionCredits == true) delayToCredits++;

			if (delayToCredits > 90 && delayToCredits <= 91)
			{
				//app->credits->Enable();    //NEED TO ADD THE CREDITS SCEN
				app->titleScreen->Disable();
			}
		}
		if (control->id == 5)
		{
			exit(0);
		}
		if (control->id == 6)
		{
			OptionsMenu = false;
			MainMenu = true;
		}


	}
	//Other cases here

	default: break;
	}

	return true;
}