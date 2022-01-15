#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

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

	bool OnGuiMouseClickEvent(GuiControl* control);

	int buttonClickedFx = 0;

private:


	SDL_Texture* PauseFrame;


	SDL_Texture* resumeButton;
	SDL_Texture* optionsButton;
	SDL_Texture* backToTitleButton;
	SDL_Texture* exitButton2;
	//CHECBOX TEXTURES
	SDL_Texture* fullScreenCheckOn;
	SDL_Texture* fullScreenCheckOff;
	SDL_Texture* VSyncOn;
	SDL_Texture* VSyncOff;
	//SLIDER TEXTURES


	//GUI BUTTONS
	GuiButton* resumeButton_;
	GuiButton* optionsButton_;
	GuiButton* backToTitleButton_;
	GuiButton* exitButton_2;
	//GUI CHECKBOX
	GuiCheckbox* fullScreenCheck;
	GuiCheckbox* VSyncCheck;
	//GUI SLIDER
	GuiSlider* musicVolumeSlider;
	GuiSlider* fxVolumeSlider;
};

#endif // __SCENE_FOREST_H__