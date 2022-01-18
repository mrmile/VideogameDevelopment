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
	resumeButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Resume Button", { 200,50,108,35 }, this, resumeButton, NULL, {});
	optionsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Settings Button", { 200,100,108,35 }, this,optionsButton, NULL, {});
	backToTitleButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Title Button", { 50,100,108,35 }, this,backToTitleButton, NULL, {});
	exitButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit Button", { 50, 50, 108, 35 }, this,exitButton, NULL, {});
	
	
	

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
	
	if (app->sceneForest->PauseMenu == true)
	{
		resumeButton_->canClick = true;
		optionsButton_->canClick = true;
		backToTitleButton_->canClick = true;
		exitButton_->canClick = true;


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
		

	}
	

	return true;
}

// Called each loop iteration
bool PauseMenu::PostUpdate()
{
	bool ret = true;
	
	if (app->sceneForest->PauseMenu == true)
	{

		SDL_Rect bgquad;
		bgquad = { 20, 20, 380, 200 };
		app->render->DrawRectangle2(bgquad, 255, 255, 255, 150, 0.0f, true);
		//app->render->DrawRectangle2(quad2, 200, 200, 200, 255, 0.0f, true);
		app->render->DrawTexture2(PauseFrame, 20, 20, NULL);
		exitButton_->Draw(app->render);
		resumeButton_->Draw(app->render);
		optionsButton_->Draw(app->render);
		backToTitleButton_->Draw(app->render);
	}
	


	return ret;

	return true;
}

// Called before quitting
bool PauseMenu::CleanUp()
{
	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(resumeButton);
	app->tex->UnLoad(optionsButton);
	app->tex->UnLoad(backToTitleButton);
	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(PauseFrame);

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
			app->sceneForest->PauseMenu = false;
		}

		if (control->id == 2)
		{
			//SETTINGS BUTTON
			app->audio->PlayFx(buttonClickedFx);

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