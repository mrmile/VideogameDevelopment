#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "Module.h"
#include "GuiButton.h"

struct SDL_Texture;


class PauseMenu : public Module
{
public:

	PauseMenu(bool start_enabled = false);

	// Destructor
	virtual ~PauseMenu();

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

	bool transitionToGameplay;
	bool transitionToMenu;

private:
	int delayGameplay;
	int delayMainMenu;
	bool GeneralMenu = true;
	bool OptionsMenu=false;

	SDL_Texture* PauseScreen;
	SDL_Texture* continueButton;
	SDL_Texture* optionsButton;
	SDL_Texture* backToTitleButton;
	SDL_Texture* exitButton;
	SDL_Texture* returnButton;
	SDL_Texture* loading;

	// L14: TODO 2_D: Declare a GUI Button and create it using the GuiManager
	GuiButton* continueButton_;
	GuiButton* optionsButton_;
	GuiButton* backToTitleButton_;
	GuiButton* exitButton_;
	GuiButton* returnButton_;
};

#endif // __WINDOW_H__