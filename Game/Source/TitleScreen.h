#ifndef __TITLE_SCREEN_H__
#define __TITLE_SCREEN_H__

#include "Module.h"
#include "GuiButton.h"

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

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);

	int sceneTimer;
	int delay;
	int delayToCredits;
	int delayToContinue;
	bool transition;
	bool transitionCredits;
	bool continueTransition;
private:

	bool MainMenu = true;
	bool OptionsMenu = false;

	SDL_Texture* titleScreen;
	SDL_Texture* titleScreen2;
	SDL_Texture* startButton;
	SDL_Texture* loading;
	SDL_Texture* continueButton;
	SDL_Texture* optionsButton;
	SDL_Texture* creditsButton;
	SDL_Texture* returnButton;
	SDL_Texture* exitButton;

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	GuiButton* startButton_;
	GuiButton* continueButton_;
	GuiButton* optionsButton_;
	GuiButton* creditsButton_;
	GuiButton* returnButton_;
	GuiButton* exitButton_;

};

#endif // __TITLE_SCREEN_H__