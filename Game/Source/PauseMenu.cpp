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


	fullScreenTag = app->tex->Load("Assets/textures/GUI/Fullscreen_tag.png");
	VSyncOff = app->tex->Load("Assets/textures/GUI/VsyncOff.png");
	VSyncOn = app->tex->Load("Assets/textures/GUI/VsyncOn.png");
	fullScreenCheckOff = app->tex->Load("Assets/textures/GUI/checkBoxOff.png");
	fullScreenCheckOn = app->tex->Load("Assets/textures/GUI/checkBoxOn.png");
	baseSlider_fx = app->tex->Load("Assets/textures/GUI/BaseSlider_fx.png");
	baseSlider_music = app->tex->Load("Assets/textures/GUI/BaseSlider_music.png");
	sliderSelector = app->tex->Load("Assets/textures/GUI/sliderInput.png");
	returnButton = app->tex->Load("Assets/textures/GUI/returnButton.png");
	returnButtonOnIdle = app->tex->Load("Assets/textures/GUI/returnButton_onIdle.png");
	returnButtonPressed = app->tex->Load("Assets/textures/GUI/returnButton_pressed.png");

	resumeButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, "Resume Button", { 225,75,108,35 }, this, resumeButton, NULL, {});
	optionsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 13, "Settings Button", { 225,125,108,35 }, this,optionsButton, NULL, {});
	backToTitleButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 14, "Title Button", { 75,125,108,35 }, this,backToTitleButton, NULL, {});
	exitButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 15, "Exit Button", { 75, 75, 108, 35 }, this,exitButton, NULL, {});
	returnButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Return Button", { 10, 10, 71, 35 }, this, returnButton, NULL, {});
	
	//SLIDERS
	fxVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, "Fx slider", { 20,60,195,35 }, this, baseSlider_fx, sliderSelector, { 214,70,14,16 });
	musicVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 8, "Music slider", { 20,100,195,35 }, this, baseSlider_music, sliderSelector, { 214,110,14,16 });

	//CHECKBOXES
	fullScreenCheck_ = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 9, "Full Screen Check Box", { 185, 149, 17, 17 }, this, fullScreenCheckOff, NULL, {});
	fullScreenCheck_tag_ = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 10, "Full Screen Tag", { 20, 140, 161, 9 }, this, fullScreenTag, NULL, {});

	VSyncCheck = (GuiCheckbox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 11, "Vsync", { 20,180,213,35 }, this, VSyncOff, NULL, {});
	
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
		optionsButton_->canClick = true;
		backToTitleButton_->canClick = true;
		exitButton_->canClick = true;
		returnButton_->canClick = false;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;
		fullScreenCheck_->canClick = false;
		fullScreenCheck_tag_->canClick = false;
		VSyncCheck->canClick = false;

		if (TitleTransition == true)
		{
			app->titleScreen->Enable();
			app->titleScreen->MainMenu = true;
			app->player->pauseMenu = false;
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
	if (app->player->pauseMenu == false)
	{

		resumeButton_->canClick = false;
		optionsButton_->canClick = false;
		backToTitleButton_->canClick = false;
		exitButton_->canClick = false;
		returnButton_->canClick = false;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;
		fullScreenCheck_->canClick = false;
		fullScreenCheck_tag_->canClick = false;
		VSyncCheck->canClick = false;
	}
	if (options == true)
	{
		fxVolumeSlider->canClick = true;
		musicVolumeSlider->canClick = true;
		fullScreenCheck_->canClick = true;
		fullScreenCheck_tag_->canClick = false;
		VSyncCheck->canClick = true;
		returnButton_->canClick = true;
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
		if (options == false)
		{
			if (exitButton_->state == GuiControlState::NORMAL && exitButton_->canClick == true) exitButton_->SetTexture(exitButton);
			if (exitButton_->state == GuiControlState::FOCUSED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonOnIdle);
			if (exitButton_->state == GuiControlState::SELECTED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonPressed);
			exitButton_->Draw(app->render);

			if (resumeButton_->state == GuiControlState::NORMAL && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButton);
			if (resumeButton_->state == GuiControlState::FOCUSED && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButtonOnIdle);
			if (resumeButton_->state == GuiControlState::SELECTED && resumeButton_->canClick == true) resumeButton_->SetTexture(resumeButtonPressed);
			resumeButton_->Draw(app->render);

			if (optionsButton_->state == GuiControlState::NORMAL && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButton);
			if (optionsButton_->state == GuiControlState::FOCUSED && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButtonOnIdle);
			if (optionsButton_->state == GuiControlState::SELECTED && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButtonPressed);
			optionsButton_->Draw(app->render);

			if (backToTitleButton_->state == GuiControlState::NORMAL && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButton);
			if (backToTitleButton_->state == GuiControlState::FOCUSED && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButtonOnIdle);
			if (backToTitleButton_->state == GuiControlState::SELECTED && backToTitleButton_->canClick == true) backToTitleButton_->SetTexture(backToTitleButtonPressed);
			backToTitleButton_->Draw(app->render);
		}
		if (options == true)
		{
			if (returnButton_->state == GuiControlState::NORMAL && returnButton_->canClick == true) returnButton_->SetTexture(returnButton);
			if (returnButton_->state == GuiControlState::FOCUSED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonOnIdle);
			if (returnButton_->state == GuiControlState::SELECTED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonPressed);
			returnButton_->Draw(app->render);

			fxVolumeSlider->Draw(app->render);



			musicVolumeSlider->Draw(app->render);


			//fullScreenCheck_tag_->SetTexture(fullScreenTag);
			//fullScreenCheck_tag_->Draw(app->render);

			//if (FullScreen == false) fullScreenCheck_->SetTexture(fullScreenCheckOff);
			//if (FullScreen == true) fullScreenCheck_->SetTexture(fullScreenCheckOn);
			//fullScreenCheck_->Draw(app->render);

		//	if (Vsync == false) VSyncCheck->SetTexture(VSyncOff);
		//	if (Vsync == true) VSyncCheck->SetTexture(VSyncOn);
			//VSyncCheck->Draw(app->render);
		}
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
	app->guiManager->DestroyGuiControl(11);
	app->guiManager->DestroyGuiControl(12);
	app->guiManager->DestroyGuiControl(13);
	app->guiManager->DestroyGuiControl(14);
	return true;
}

bool PauseMenu::OnGuiMouseClickEvent(GuiControl* control){
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 12 && resumeButton_->canClick==true)
		{
			//RESUME BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			app->player->pauseMenu = false;
		}

		if (control->id == 13 && optionsButton_->canClick == true)
		{
			//SETTINGS BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			options = true;
			

		}
		if (control->id == 14 && backToTitleButton_->canClick == true)
		{
			//BACK TO TITLE BUTTON
			app->audio->PlayFx(buttonClickedFx, 0);
			TitleTransition = true;
		}

		if (control->id == 15 && exitButton_->canClick == true)
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