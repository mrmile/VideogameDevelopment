#include "PauseMenu.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneForest.h"
#include "TitleScreen.h"
#include "ModulePlayer.h"
#include "GuiManager.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Map.h"
#include "Enemies.h"
#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>


PauseMenu::PauseMenu(bool start_enabled) : Module(start_enabled)
{
	name.Create("PauseMenu");
}

// Destructor
PauseMenu::~PauseMenu()
{}

// Called before render is available
bool PauseMenu::Awake()
{
	LOG("Loading PauseMenu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool PauseMenu::Start()
{
	PauseFrame = app->tex->Load("Assets/textures/GUI/PauseMenuFrame.png");

	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/Advice.wav");
	resumeButton = app->tex->Load("Assets/textures/GUI/resumeButton.png");
	optionsButton = app->tex->Load("Assets/textures/GUI/optionsButton.png");
	backToTitleButton = app->tex->Load("Assets/textures/GUI/titlescreenButton.png");
	exitButton = app->tex->Load("Assets/textures/GUI/exitButton.png");

	resumeButtonOnIdle = app->tex->Load("Assets/textures/GUI/resumeButton_onIdle.png");
	optionsButtonOnIdle = app->tex->Load("Assets/textures/GUI/optionsButton_onIdle.png");
	backToTitleButtonOnIdle = app->tex->Load("Assets/textures/GUI/titlescreenButton_onIdle.png");
	exitButtonOnIdle = app->tex->Load("Assets/textures/GUI/exitButton_onIdle.png");

	resumeButtonPressed = app->tex->Load("Assets/textures/GUI/resumeButton_pressed.png");
	optionsButtonPressed = app->tex->Load("Assets/textures/GUI/optionsButton_pressed.png");
	backToTitleButtonPressed = app->tex->Load("Assets/textures/GUI/titlescreenButton_pressed.png");
	exitButtonPressed = app->tex->Load("Assets/textures/GUI/exitButton_pressed.png");

	resumeButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Resume Button", { 200,50,108,35 }, this, resumeButton, NULL, {});
	//optionsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Settings Button", { 200,100,108,35 }, this,optionsButton, NULL, {});
	backToTitleButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Title Button", { 50,100,108,35 }, this,backToTitleButton, NULL, {});
	exitButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit Button", { 50, 50, 108, 35 }, this,exitButton, NULL, {});
	
	
	
	pauseTimer = 0;
	noPauseTimer = 0;
	sceneTimer = 0;
	return true;
}

// Called each loop iteration
bool PauseMenu::PreUpdate()
{
	
	return true;
}

// Called each loop iteration
bool PauseMenu::Update(float dt)
{
	sceneTimer++;
	
	if (app->player->pauseMenu == true)
	{
		pauseTimer++;
		noPauseTimer = 0;

		resumeButton_->canClick = true;
		//optionsButton_->canClick = true;
		backToTitleButton_->canClick = true;
		exitButton_->canClick = true;


		/* // No sirve
		if (resumeButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(resumeButton_);
		}
		if (optionsButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(optionsButton_);
		}
		if (backToTitleButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(backToTitleButton_);
		}
		if (exitButton_->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(exitButton_);
		}
		*/
		
		if (TitleTransition == true)
		{
			app->titleScreen->Enable();
			app->titleScreen->MainMenu = true;

			app->map->Disable();
			app->collisions->Disable();
			app->particles->Disable();
			app->sceneForest->Disable();
			app->player->Disable();
			app->enemies->Disable();
			app->fonts->Disable();
			app->pause_menu->Disable();
			TitleTransition = false;
		}
		
		if(pauseTimer <= 1) Mix_PauseMusic();

	}
	else
	{
		pauseTimer = 0;
		noPauseTimer++;

		if (noPauseTimer <= 1) Mix_ResumeMusic();
	}
	

	return true;
}

// Called each loop iteration
bool PauseMenu::PostUpdate()
{
	bool ret = true;
	
	if (app->player->pauseMenu == true)
	{

		SDL_Rect bgquad;
		bgquad = { 20, 20, 380, 200 };
		app->render->DrawRectangle2(bgquad, 255, 255, 255, 150, 0.0f, true);
		//app->render->DrawRectangle2(quad2, 200, 200, 200, 255, 0.0f, true);
		app->render->DrawTexture2(PauseFrame, 20, 20, NULL);

		if (exitButton_->state == GuiControlState::NORMAL && exitButton_->canClick == true) exitButton_->SetTexture(exitButton);
		if (exitButton_->state == GuiControlState::FOCUSED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonOnIdle);
		if (exitButton_->state == GuiControlState::SELECTED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonPressed);
		exitButton_->Draw(app->render);
		
		if (resumeButton_->state == GuiControlState::NORMAL && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButton);
		if (resumeButton_->state == GuiControlState::FOCUSED && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButtonOnIdle);
		if (resumeButton_->state == GuiControlState::SELECTED && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButtonPressed);
		resumeButton_->Draw(app->render);

		//optionsButton_->Draw(app->render);

		if (backToTitleButton_->state == GuiControlState::NORMAL && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButton);
		if (backToTitleButton_->state == GuiControlState::FOCUSED && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButtonOnIdle);
		if (backToTitleButton_->state == GuiControlState::SELECTED && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButtonPressed);
		backToTitleButton_->Draw(app->render);
	}
	


	return ret;

	return true;
}

// Called before quitting
bool PauseMenu::CleanUp()
{
	app->tex->UnLoad(PauseFrame);

	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(resumeButton);
	app->tex->UnLoad(optionsButton);
	app->tex->UnLoad(backToTitleButton);
	app->tex->UnLoad(exitButton);

	app->tex->UnLoad(exitButtonOnIdle);
	app->tex->UnLoad(optionsButtonOnIdle);
	app->tex->UnLoad(backToTitleButtonOnIdle);
	app->tex->UnLoad(exitButtonOnIdle);

	app->tex->UnLoad(exitButtonPressed);
	app->tex->UnLoad(resumeButtonPressed);
	app->tex->UnLoad(optionsButtonPressed);
	app->tex->UnLoad(backToTitleButtonPressed);
	app->tex->UnLoad(exitButtonPressed);

	return true;
}

bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control){
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 1)
		{
			//RESUME BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			app->player->pauseMenu = false;
		}

		if (control->id == 2)
		{
			//SETTINGS BUTTON
			//app->audio->PlayFx(buttonClickedFx, 0);

		}
		if (control->id == 3)
		{
			//BACK TO TITLE BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			TitleTransition = true;
		}

		if (control->id == 4)
		{
			//EXIT BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			exit(0);

		}
	}

	default: break;
	}

	return true;
}