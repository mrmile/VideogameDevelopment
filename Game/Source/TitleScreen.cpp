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
#include "GuiButton.h"
#include "PauseMenu.h"

#include "Defs.h"
#include "Log.h"

#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
using namespace std;

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
	creditsScene = app->tex->Load("Assets/textures/creditsScreen3.png");

	startButton = app->tex->Load("Assets/textures/GUI/startButton.png");
	continueButton = app->tex->Load("Assets/textures/GUI/continueButton.png");
	continueButtonOff = app->tex->Load("Assets/textures/GUI/continueButtonOff.png");
	optionsButton = app->tex->Load("Assets/textures/GUI/optionsButton.png");
	creditsButton = app->tex->Load("Assets/textures/GUI/creditsButton.png");
	exitButton = app->tex->Load("Assets/textures/GUI/exitButton.png");
	returnButton = app->tex->Load("Assets/textures/GUI/returnButton.png");
	baseSlider = app->tex->Load("Assets/textures/GUI/BaseSlider.png");
	sliderSelector = app->tex->Load("Assets/textures/GUI/sliderInput.png");

	startButtonOnIdle = app->tex->Load("Assets/textures/GUI/startButton_onIdle.png");
	continueButtonOnIdle = app->tex->Load("Assets/textures/GUI/continueButton_onIdle.png");
	continueButtonOffOnIdle = app->tex->Load("Assets/textures/GUI/continueButtonOff_onIdle.png");
	optionsButtonOnIdle = app->tex->Load("Assets/textures/GUI/optionsButton_onIdle.png");
	creditsButtonOnIdle = app->tex->Load("Assets/textures/GUI/creditsButton_onIdle.png");
	exitButtonOnIdle = app->tex->Load("Assets/textures/GUI/exitButton_onIdle.png");
	returnButtonOnIdle = app->tex->Load("Assets/textures/GUI/returnButton_onIdle.png");
	baseSliderOnIdle = app->tex->Load("Assets/textures/GUI/BaseSlider_onIdle.png");
	sliderSelectorOnIdle = app->tex->Load("Assets/textures/GUI/sliderInput_onIdle.png");

	startButtonPressed = app->tex->Load("Assets/textures/GUI/startButton_pressed.png");
	continueButtonPressed = app->tex->Load("Assets/textures/GUI/continueButton_pressed.png");
	continueButtonOffPressed = app->tex->Load("Assets/textures/GUI/continueButtonOff_pressed.png");
	optionsButtonPressed = app->tex->Load("Assets/textures/GUI/optionsButton_pressed.png");
	creditsButtonPressed = app->tex->Load("Assets/textures/GUI/creditsButton_pressed.png");
	exitButtonPressed = app->tex->Load("Assets/textures/GUI/exitButton_pressed.png");
	returnButtonPressed = app->tex->Load("Assets/textures/GUI/returnButton_pressed.png");
	baseSliderPressed = app->tex->Load("Assets/textures/GUI/BaseSlider_pressed.png");
	sliderSelectorPressed = app->tex->Load("Assets/textures/GUI/sliderInput_pressed.png");

	// Load music
	//app->audio->PlayMusic("Assets/audio/music/fortress.ogg");
	buttonClickedFx = app->audio->LoadFx("Assets/audio/fx/Advice.wav");
	buttonNotClickedFx = app->audio->LoadFx("Assets/audio/fx/No.wav");

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	//BUTTONS
	startButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "Start Button", { 105, 120, 108, 35 }, this,startButton,NULL, {}); //Observer (this): Class that will receive the event
	continueButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "Continue Button", { 105, 160, 108, 35 }, this,continueButton, NULL, {});
	optionsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "Options Button", { 105, 200, 108, 35 }, this,optionsButton, NULL, {});
	creditsButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "Credits Button", { 215, 120, 108, 35 }, this,creditsButton, NULL, {});
	exitButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "Exit Button", { 215, 160, 108, 35 }, this,exitButton, NULL, {});
	returnButton_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "Return Button", { 10, 10, 71, 35 }, this, returnButton, NULL, {});

	//SLIDERS
	fxVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, "Fx slider", { 20,80,195,35 }, this, baseSlider, sliderSelector, {214,90,14,16});
	musicVolumeSlider = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 8, "Music slider", { 20,120,195,35 }, this, baseSlider, sliderSelector, { 214,130,14,16 });

	
	sceneTimer = 0;
	delay = 0;
	delayToContinue = 0;
	delayToCredits = 0;
	transition = false;
	continueTransition = false;
	GameHasContinued = false;
	credits = false;

	app->render->camera.x = 0;
	app->render->camera.y = 0;


	app->CheckGameRequest();
	

	return true;
}

bool TitleScreen::PreUpdate()
{
	//app->LoadGameRequest();

	return true;
}

bool TitleScreen::Update(float dt)
{
	sceneTimer++;

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		transition = true;
	}
	if (MainMenu == true)
	{
		startButton_->canClick = true;
		continueButton_->canClick = true;
		optionsButton_->canClick = true;
		creditsButton_->canClick = true;
		exitButton_->canClick = true;
		returnButton_->canClick = false;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;

	}
	if (OptionsMenu == true)
	{
		startButton_->canClick = false;
		continueButton_->canClick = false;
		optionsButton_->canClick = false;
		creditsButton_->canClick = false;
		exitButton_->canClick = false;
		returnButton_->canClick = true;
		fxVolumeSlider->canClick = true;
		musicVolumeSlider->canClick = true;
	}
	if (credits == true)
	{
		startButton_->canClick = false;
		continueButton_->canClick = false;
		optionsButton_->canClick = false;
		creditsButton_->canClick = false;
		exitButton_->canClick = false;
		returnButton_->canClick = true;
		fxVolumeSlider->canClick = false;
		musicVolumeSlider->canClick = false;
	}


	if (MainMenu == true)
	{
		//No sirve de nada
		/*
		//START BUTTON
		if (startButton_->state == GuiControlState::PRESSED && startButton_->canClick==true)
		{
			OnGuiMouseClickEvent(startButton_);
		}
		//CONTINUE BUTTON
		if (continueButton_->state == GuiControlState::PRESSED && continueButton_->canClick == true)
		{
			OnGuiMouseClickEvent(continueButton_);
		}
		//SETTINGS BUTTON
		if (optionsButton_->state == GuiControlState::PRESSED && optionsButton_->canClick == true)
		{
			OnGuiMouseClickEvent(optionsButton_);
			//cout << "Pressed " << endl;
		}
		//CREDITS BUTTON
		if (creditsButton_->state == GuiControlState::PRESSED && creditsButton_->canClick == true)
		{
			OnGuiMouseClickEvent(creditsButton_);
		}
		//EXIT BUTTON
		if (exitButton_->state == GuiControlState::PRESSED && exitButton_->canClick == true)
		{
			OnGuiMouseClickEvent(exitButton_);
		}
		*/
		
		//FOR CONTINUE BUTTON
		if (continueTransition == true) delayToContinue++;

		if (delayToContinue > 90 && delayToContinue <= 91)
		{
			//app->physics->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->map->Start();
			app->particles->Enable();
			app->sceneForest->Enable();
			app->player->Enable();
			app->enemies->Enable();
			app->fonts->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->particles->Enable();
			app->sceneForest->Enable();
			app->player->Enable();
			app->enemies->Enable();
			app->fonts->Enable();
			app->tex->Enable();
			app->pause_menu->Enable();

		
			GameHasContinued = true;

			app->titleScreen->Disable();
			//app->fade->FadeToBlack(app->titleScreen, app->sceneCastle, 60);
		}

		//FOR START BUTTON
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
			app->tex->Enable();
			app->pause_menu->Enable();
			app->player->score = 0;
			app->player->lives = 3;
			SavedGame = false;
			

			app->titleScreen->Disable();
			//app->fade->FadeToBlack(app->titleScreen, app->sceneCastle, 60);
		}
	}

	if (OptionsMenu == true)
	{
		//RETURN TO MAIN MENU BUTTON
		
		//No sirve de nada
		/*
		if (returnButton_->state == GuiControlState::PRESSED && returnButton_->canClick == true)
		{
			OnGuiMouseClickEvent(returnButton_);
		}
		if (fxVolumeSlider->state == GuiControlState::PRESSED && fxVolumeSlider->canClick == true)
		{
			OnGuiMouseClickEvent(fxVolumeSlider);
		} 
		if (musicVolumeSlider->state == GuiControlState::PRESSED && musicVolumeSlider->canClick == true)
		{
			OnGuiMouseClickEvent(musicVolumeSlider);
		}
		*/
		//METER LOGICA SLIDER
		//FALTA MIRAR COMO CAMBIAR VOLUMEN MUSICA Y VOLUMEN FX Y MODIFICARLO SEGUN EL SLIDER LEVEL FX O SLIDER LEVEL MUSIC
	}
	
	return true;
}

bool TitleScreen::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	app->render->DrawTexture2(titleScreen, 0, 0, NULL);	
	
	if (MainMenu == true) 
	{

		if (startButton_->state == GuiControlState::NORMAL && startButton_->canClick == true) startButton_->SetTexture(startButton);
		if (startButton_->state == GuiControlState::FOCUSED && startButton_->canClick == true) startButton_->SetTexture(startButtonOnIdle);
		if (startButton_->state == GuiControlState::SELECTED && startButton_->canClick == true) startButton_->SetTexture(startButtonPressed);
		startButton_->Draw(app->render);

		if (SavedGame == true)
		{
			if (continueButton_->state == GuiControlState::NORMAL && continueButton_->canClick == true) continueButton_->SetTexture(continueButton);
			if (continueButton_->state == GuiControlState::FOCUSED && continueButton_->canClick == true) continueButton_->SetTexture(continueButtonOnIdle);
			if (continueButton_->state == GuiControlState::SELECTED && continueButton_->canClick == true) continueButton_->SetTexture(continueButtonPressed);
			continueButton_->Draw(app->render);
		}
		if (SavedGame == false)
		{
			continueButton_->SetTexture(continueButtonOff);
			continueButton_->Draw(app->render);
		}

		if (optionsButton_->state == GuiControlState::NORMAL && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButton);
		if (optionsButton_->state == GuiControlState::FOCUSED && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButtonOnIdle);
		if (optionsButton_->state == GuiControlState::SELECTED && optionsButton_->canClick == true) optionsButton_->SetTexture(optionsButtonPressed);
		optionsButton_->Draw(app->render);

		if (creditsButton_->state == GuiControlState::NORMAL && creditsButton_->canClick == true) creditsButton_->SetTexture(creditsButton);
		if (creditsButton_->state == GuiControlState::FOCUSED && creditsButton_->canClick == true) creditsButton_->SetTexture(creditsButtonOnIdle);
		if (creditsButton_->state == GuiControlState::SELECTED && creditsButton_->canClick == true) creditsButton_->SetTexture(creditsButtonPressed);
		creditsButton_->Draw(app->render);

		if (exitButton_->state == GuiControlState::NORMAL && exitButton_->canClick == true) exitButton_->SetTexture(exitButton);
		if (exitButton_->state == GuiControlState::FOCUSED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonOnIdle);
		if (exitButton_->state == GuiControlState::SELECTED && exitButton_->canClick == true) exitButton_->SetTexture(exitButtonPressed);
		exitButton_->Draw(app->render);
	}
	if (OptionsMenu == true)
	{
		app->render->DrawTexture2(titleScreen2, 0, 0, NULL);

		if (returnButton_->state == GuiControlState::NORMAL && returnButton_->canClick == true) returnButton_->SetTexture(returnButton);
		if (returnButton_->state == GuiControlState::FOCUSED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonOnIdle);
		if (returnButton_->state == GuiControlState::SELECTED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonPressed);
		returnButton_->Draw(app->render);

		fxVolumeSlider->Draw(app->render);



		musicVolumeSlider->Draw(app->render);



	}
	if (credits == true)
	{
		app->render->DrawTexture2(titleScreen2, 0, 0, NULL);
		app->render->DrawTexture2(creditsScene, 0, 0, NULL);

		if (returnButton_->state == GuiControlState::NORMAL && returnButton_->canClick == true) returnButton_->SetTexture(returnButton);
		if (returnButton_->state == GuiControlState::FOCUSED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonOnIdle);
		if (returnButton_->state == GuiControlState::SELECTED && returnButton_->canClick == true) returnButton_->SetTexture(returnButtonPressed);
		returnButton_->Draw(app->render);
	}

	if (transition == true || continueTransition == true) app->render->DrawTexture2(loading, 0, 0, NULL);

	return ret;
	
	//return true;
}

bool TitleScreen::CleanUp()
{
	app->tex->UnLoad(titleScreen);
	app->tex->UnLoad(startButton);
	app->tex->UnLoad(creditsScene);
	app->tex->UnLoad(titleScreen2);
	app->tex->UnLoad(loading);

	app->tex->UnLoad(continueButton);
	app->tex->UnLoad(continueButtonOff);
	app->tex->UnLoad(optionsButton);
	app->tex->UnLoad(creditsButton);
	app->tex->UnLoad(exitButton);
	app->tex->UnLoad(returnButton);
	app->tex->UnLoad(sliderSelector);
	app->tex->UnLoad(baseSlider);

	app->tex->UnLoad(continueButtonOnIdle);
	app->tex->UnLoad(continueButtonOffOnIdle);
	app->tex->UnLoad(optionsButtonOnIdle);
	app->tex->UnLoad(creditsButtonOnIdle);
	app->tex->UnLoad(exitButtonOnIdle);
	app->tex->UnLoad(returnButtonOnIdle);
	app->tex->UnLoad(sliderSelectorOnIdle);
	app->tex->UnLoad(baseSliderOnIdle);

	app->tex->UnLoad(continueButtonPressed);
	app->tex->UnLoad(continueButtonOffPressed);
	app->tex->UnLoad(optionsButtonPressed);
	app->tex->UnLoad(creditsButtonPressed);
	app->tex->UnLoad(exitButtonPressed);
	app->tex->UnLoad(returnButtonPressed);
	app->tex->UnLoad(sliderSelectorPressed);
	app->tex->UnLoad(baseSliderPressed);

	return true;
}

bool TitleScreen::OnGuiMouseClickEvent(GuiControl* control)
{

	switch (control->type)
	{
		case GuiControlType::BUTTON:
		{
			//Checks the GUI element ID
			if (control->id == 1 && startButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				transition = true;

			}

			if (control->id == 2 && continueButton_->canClick == true)
			{

				if (SavedGame == true)
				{
					app->audio->PlayFx(buttonClickedFx, 0);
					app->audio->PlayFx(buttonClickedFx, 0);
					continueTransition = true;
				}
				if (SavedGame == false)
				{
					app->audio->PlayFx(buttonNotClickedFx, 0);
				}
			}
			if (control->id == 3 && optionsButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				MainMenu = false;
				OptionsMenu = true;
			}

			if (control->id == 4 && creditsButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);

				MainMenu = false;
				credits = true;
			}
			if (control->id == 5 && exitButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				exit(0);
			}
			if (control->id == 6 && returnButton_->canClick == true)
			{
				app->audio->PlayFx(buttonClickedFx, 0);
				OptionsMenu = false; 
				credits = false;
				MainMenu = true;
			}


		}
		//Other cases here
		case GuiControlType::SLIDER:
		{
			if (control->id == 7 && fxVolumeSlider->canClick == true)
			{
				if (control->extraBounds.x > control->bounds.x + control->bounds.w - 20)
				{
					//AUN NO FUNCIONA EL 10 me da palo <-- Da igual. Este no se hace y ya est�. Es el causante de que automaticamente el volumen vuelva a 100 sin tocar nada
					//app->audio->SliderLevelFX = 100;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.9f) && control->extraBounds.x < control->bounds.x + control->bounds.w)
				{
					app->audio->SliderLevelFX = 90;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.8f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.9f))
				{
					app->audio->SliderLevelFX = 80;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.7f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.8f))
				{
					app->audio->SliderLevelFX = 70;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.6f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.7f))
				{
					app->audio->SliderLevelFX = 60;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.5f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.6f))
				{
					app->audio->SliderLevelFX = 50;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.4f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.5f))
				{
					app->audio->SliderLevelFX = 40;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.3f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.4f))
				{
					app->audio->SliderLevelFX = 30;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.2f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.3f))
				{
					app->audio->SliderLevelFX = 20;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.1f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.2f))
				{
					app->audio->SliderLevelFX = 10;
				}
				if (control->extraBounds.x > control->bounds.x && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.1f))
				{
					app->audio->SliderLevelFX = 0;
				}

			}

			if (control->id == 8 && musicVolumeSlider->canClick == true)
			{
				if (control->extraBounds.x > control->bounds.x + control->bounds.w - 20)
				{
					//AUN NO FUNCIONA EL 10 me da palo <-- Da igual. Este no se hace y ya est�. Es el causante de que automaticamente el volumen vuelva a 100 sin tocar nada
					//app->audio->SliderLevelMusic = 100;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.9f) && control->extraBounds.x < control->bounds.x + control->bounds.w)
				{
					app->audio->SliderLevelMusic = 90;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.8f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.9f))
				{
					app->audio->SliderLevelMusic = 80;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.7f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.8f))
				{
					app->audio->SliderLevelMusic = 70;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.6f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.7f))
				{
					app->audio->SliderLevelMusic = 60;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.5f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.6f))
				{
					app->audio->SliderLevelMusic = 50;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.4f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.5f))
				{
					app->audio->SliderLevelMusic = 40;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.3f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.4f))
				{
					app->audio->SliderLevelMusic = 30;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.2f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.3f))
				{
					app->audio->SliderLevelMusic = 20;
				}
				if (control->extraBounds.x > control->bounds.x + (control->bounds.w * 0.1f) && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.2f))
				{
					app->audio->SliderLevelMusic = 10;
				}
				if (control->extraBounds.x > control->bounds.x && control->extraBounds.x < control->bounds.x + (control->bounds.w * 0.1f))
				{
					app->audio->SliderLevelMusic = 0;
				}
			}

		}
		default: break;
	}
	
	return true;
}
bool TitleScreen::CheckSave(pugi::xml_node& data) 
{
	SavedGame = data.child("saved_game").attribute("bool").as_bool();
	app->audio->SliderLevelFX = data.child("saved_game").attribute("Fx").as_int();
	app->audio->SliderLevelMusic = data.child("saved_game").attribute("Music").as_int();

	return true;
}

bool TitleScreen::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node savedGame = data.append_child("saved_game");
	
	savedGame.append_attribute("bool") = SavedGame;
	savedGame.append_attribute("Fx") = app->audio->SliderLevelFX;
	savedGame.append_attribute("Music") = app->audio->SliderLevelMusic;

	return true;
}