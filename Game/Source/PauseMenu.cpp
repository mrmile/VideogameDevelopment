#include "PauseMenu.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneForest.h"
#include "TitleScreen.h"
#include "GuiManager.h"

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
	exitButton2 = app->tex->Load("Assets/textures/GUI/exitButton.png");
	exitButton_2 = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Exit Button", { 5, 5, 108, 35 }, this);
	exitButton_2->SetTexture(exitButton2);

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
 
	//SETTINGS BUTTON
	/*
	if (optionsButton_->state == GuiControlState::PRESSED)
	{
		OnGuiMouseClickEvent(optionsButton_);
	}
	*/
	//CREDITS BUTTON
	if (app->sceneForest->PauseMenu == true)
	{
		

		exitButton_2->canClick = true;

		if (exitButton_2->state == GuiControlState::PRESSED)
		{
			OnGuiMouseClickEvent(exitButton_2);
		}

	}

	//FOR CREDITS BUTTOn


	return true;
}

// Called each loop iteration
bool PauseMenu::PostUpdate()
{
	if (app->sceneForest->PauseMenu == true)
	{
		
		SDL_Rect quad2;
		quad2 = { 50, 10, 100, 10 };

		SDL_Rect quad3;
		quad3 = { 100, 10, 100, 10 };
		app->render->DrawRectangle2(quad2, 200, 200, 200, 255, 0.0f, true);
		app->render->DrawTexture(PauseFrame, 100, 100, &quad3);
	}
	
	
	return true;
}

// Called before quitting
bool PauseMenu::CleanUp()
{
	app->tex->UnLoad(exitButton2);

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
			app->audio->PlayFx(buttonClickedFx, 0);


		}

		if (control->id == 2)
		{
			app->audio->PlayFx(buttonClickedFx);


		}
		if (control->id == 3)
		{
			app->audio->PlayFx(buttonClickedFx, 0);

		}

		if (control->id == 4)
		{
			app->audio->PlayFx(buttonClickedFx, 0);


		}
		if (control->id == 5)
		{
			app->audio->PlayFx(buttonClickedFx, 0);
			exit(0);
		}
		if (control->id == 6)
		{
			app->audio->PlayFx(buttonClickedFx, 0);

		}


	}

	default: break;
	}

	return true;
}