#include "PauseMenu.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneForest.h"
#include "SceneCastle.h"
#include "TitleScreen.h"
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

PauseMenu::PauseMenu(bool start_enabled) : Module(start_enabled)
{
	name.Create("Pause menu");
}

PauseMenu::~PauseMenu()
{
}

bool PauseMenu::Awake()
{
	LOG("Pause Menu Scene");
	bool ret = true;

	return ret;

	return true;
}

bool PauseMenu::Start()
{
	PauseScreen = app->tex->Load("Assets/textures/PauseBackground.png");
	continueButton = app->tex->Load("Assets/textures/startButton3.png");
	
	loading = app->tex->Load("Assets/textures/loadingScreen3.png");
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/fortress.ogg");

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	continueButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Start Button", { 110, 170, 265, 15 }, this); //Observer (this): Class that will receive the event


	app->render->camera.x = 0;
	app->render->camera.y = 0;

	return true;
}

bool PauseMenu::PreUpdate()
{


	return true;
}

bool PauseMenu::Update(float dt)
{
	//ALL LOGIC FOR BUTTONS IN EACH STATE

	if (GeneralMenu == true)
	{
		//CONTINUE BUTTON
		//We have to add the load state so the player and the enemies spawn in the same position and with the same hp
		if (continueButton_->state == GuiControlState::PRESSED)
		{
			app->LoadGameRequest();
			transitionToGameplay = true;
		}
		if (transitionToGameplay == true) delayGameplay++;
		if (delayGameplay > 120 && delayGameplay <= 121)
		{
			app->collisions->Enable();
			app->map->Enable();
			app->particles->Enable();
			app->sceneForest->Enable();
			app->player->Enable();
			app->enemies->Enable();
			app->fonts->Enable();

			app->pauseMenu->Disable();
			
		}
		//OPTIONS BUTTON
		if (optionsButton_->state == GuiControlState::PRESSED)
		{
			GeneralMenu = false;
			OptionsMenu = true;
		}
		//BACK TO TITLE BUTTON
		if (backToTitleButton_->state == GuiControlState::PRESSED)
		{
			transitionToMenu = true;
		}
		if (transitionToMenu == true) delayMainMenu++;
		if (delayMainMenu > 30 && delayMainMenu <= 31)
		{
			app->collisions->Enable();
			app->map->Enable();
			app->particles->Enable();
			app->titleScreen->Enable();
			app->player->Enable();
			app->enemies->Enable();
			app->fonts->Enable();

			app->pauseMenu->Disable();
			
		}
		//EXIT BUTTON
		if (exitButton_->state == GuiControlState::PRESSED)
		{
			return false;
		}
	}
	if (OptionsMenu == true)
	{
		//LOGIC FOR THE OPTIONS MENU
		//STILL HAVE TO IMPLEMENT GUISLIDER AND GUICHECKBOX
		if (returnButton_->state == GuiControlState::PRESSED)
		{
			OptionsMenu = false;
			GeneralMenu = true;
		}
	}



	



	return true;
}

bool PauseMenu::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->render->DrawTexture(PauseScreen, 0, 0, NULL);

	//if (((sceneTimer / 30) % 2 == 0)&& button1->state==GuiControlState::PRESSED) button1->Draw(app->render);


	continueButton_->SetTexture(continueButton);

	app->guiManager->Draw();  //used to draw the whole GUI 
	

	//app->guiManager->Draw();  used to draw the whole GUI 

	//if (transitionToGameplay == true) app->render->DrawTexture(loading, 0, 0, NULL);

	return ret;

	return true;
}

bool PauseMenu::CleanUp()
{
	app->tex->UnLoad(PauseScreen);
	app->tex->UnLoad(continueButton);
	app->tex->UnLoad(loading);

	return true;
}

bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control)
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