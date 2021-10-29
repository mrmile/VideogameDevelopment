#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModulePhysics.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer();

	// Destructor
	~ModulePlayer();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Collision callback, called when the player intersects with another collider
	

public:
	// Position of the player in the map
	iPoint position;

	//Player body for physics implementation
	PhysBody* Player;
	
	//TEST OF IMPLEMENTATION
	PhysBody* TestingGround;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleRightAnim;
	Animation idleLeftAnim;
	Animation idleRightAnim2;
	Animation idleLeftAnim2;
	Animation rightAnim;
	Animation leftAnim;
	Animation rightRunAnim;
	Animation leftRunAnim;
	Animation jumpRightAnim;
	Animation jumpLeftAnim;
	Animation fallRightAnim;
	Animation fallLeftAnim;

	// Sound effects indices
	uint jumpSound = 0;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int PlayerLookingPosition;

	int playerTimer;
	int playerIdleAnimationTimer;

	//Margin of movement
	int horizontalMargin = 45;

	//Collision bools
	bool plantCollision;

	//Action things
	bool run = false;
	bool jump;
	bool doubleJump;
	bool inTheAir = false;
};

#endif //!__MODULE_PLAYER_H__