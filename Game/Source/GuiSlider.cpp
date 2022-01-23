#include "GuiSlider.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "TitleScreen.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect sliderBounds,SDL_Texture* texture,SDL_Texture* sliderTexture) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->extraBounds = sliderBounds;
	this->texture = texture;
	this->textureForSlider = sliderTexture;
	//canClick = true;
	drawBasic = false;
}

GuiSlider::~GuiSlider()
{

}

bool GuiSlider::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		if (canClick == true)
		{
			int mouseX, mouseY;
			app->input->GetMousePosition(mouseX, mouseY);

			if ((mouseX > bounds.x && mouseX < (bounds.x + bounds.w)) &&
				(mouseY > bounds.y && mouseY < bounds.y + bounds.h))
			{
				state = GuiControlState::FOCUSED;

				if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
				{
					state = GuiControlState::PRESSED;
					extraBounds.x = mouseX;
				}
				else if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
				{
					NotifyObserver();
				}
				else
				{
					state = GuiControlState::NORMAL;
					NotifyObserver();
				}
			}
		}
		// L14: TODO 3_D: Update the state of the GUiButton according to the mouse position
		

	}

	return false;
}

bool GuiSlider::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		render->DrawTexture2(texture, bounds.x, bounds.y,NULL);
		render->DrawTexture2(textureForSlider, extraBounds.x, extraBounds.y, NULL);
	} break;

	case GuiControlState::NORMAL:
	{
		render->DrawTexture2(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture2(textureForSlider, extraBounds.x, extraBounds.y, NULL);
	} break;

	//L14: TODO 4: Draw the button according the GuiControl State
	case GuiControlState::FOCUSED:
	{
		render->DrawTexture2(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture2(textureForSlider, extraBounds.x, extraBounds.y, NULL);
	} break;
	case GuiControlState::PRESSED:
	{
		render->DrawTexture2(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture2(textureForSlider, extraBounds.x, extraBounds.y, NULL);
	} break;

	/******/

	case GuiControlState::SELECTED:
	{
		render->DrawTexture2(texture, bounds.x, bounds.y, NULL);
		render->DrawTexture2(textureForSlider, extraBounds.x, extraBounds.y, NULL);
	}break;
	default:
		break;
	}

	return false;
}