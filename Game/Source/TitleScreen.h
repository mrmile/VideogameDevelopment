#ifndef __TITLE_SCREEN_H__
#define __TITLE_SCREEN_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class TitleScreen : public Module
{
public:

	TitleScreen(bool start_enabled = false);

	// Destructor
	virtual ~TitleScreen();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Define multiple Gui Event methods
	bool OnGuiMouseClickEvent(GuiControl* control);

	bool SaveState(pugi::xml_node&) const;
	bool CheckSave(pugi::xml_node&);

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);


	int sceneTimer;
	int delay;
	int delayToCredits;
	int delayToContinue;
	bool transition=false;
	bool transitionCredits=false;
	bool continueTransition=false;
	

	bool GameHasContinued = false;

	int buttonClickedFx = 0;

	bool titleScreenWait = true;
	bool SavedGame;

	bool Vsync = false;
	bool FullScreen = false;
public:

	bool MainMenu = true;
	bool OptionsMenu = false;

	SDL_Texture* titleScreen;
	SDL_Texture* titleScreen2;
	SDL_Texture* loading;
	//BUTTONS TEXTURES
	SDL_Texture* startButton;
	SDL_Texture* continueButton;
	SDL_Texture* continueButtonOff;
	SDL_Texture* optionsButton;
	SDL_Texture* creditsButton;
	SDL_Texture* returnButton;
	SDL_Texture* exitButton;
	//CHECBOX TEXTURES
	SDL_Texture* fullScreenCheckOn;
	SDL_Texture* fullScreenCheckOff;
	SDL_Texture* VSyncOn;
	SDL_Texture* VSyncOff;
	//SLIDER TEXTURES
	SDL_Texture* baseSlider;
	SDL_Texture* sliderSelector;

	//GUI BUTTONS
	GuiButton* startButton_;
	GuiButton* continueButton_;
	GuiButton* optionsButton_;
	GuiButton* creditsButton_;
	GuiButton* returnButton_;
	GuiButton* exitButton_;
	//GUI CHECKBOX
	GuiCheckbox* fullScreenCheck;
	GuiCheckbox* VSyncCheck;
	//GUI SLIDER
	GuiSlider* musicVolumeSlider;
	GuiSlider* fxVolumeSlider;
};

#endif // __TITLE_SCREEN_H__