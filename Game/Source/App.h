#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "PerfTimer.h"
#include "Timer.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class TitleScreen;
class SceneForest;
class SceneCastle;
class Map;
class ModuleFadeToBlack;
class ModulePhysics;
class ModulePlayer;
class ModuleCollisions;
class Enemies;
class ModuleParticles;
//class Enemy;
class PathFinding;
class ModuleFonts;
class GuiManager;
class PauseMenu;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void CheckGameRequest();
	void SaveGameRequest() const;
	void SaveGameAudio();

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool CheckGame();
	bool SaveGame() const;
	bool SaveAudio();

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	TitleScreen* titleScreen;
	SceneForest* sceneForest;
	SceneCastle* sceneCastle;
	Map* map;
	ModuleFadeToBlack* fade;
	ModulePhysics* physics;
	ModulePlayer* player;
	ModuleCollisions* collisions;
	Enemies* enemies;
	ModuleParticles* particles;
	//Enemy* enemy;
	PathFinding* pathfinding;
	ModuleFonts* fonts;
	GuiManager* guiManager;
	PauseMenu* pause_menu;

	bool AppTitleScreenFull = false;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	//pugi::xml_document configFile;
	//pugi::xml_node config;
	//pugi::xml_node configApp;

	uint frames;
	//float dt;

	mutable bool saveGameRequested;
	bool checkGameRequested;
	bool loadGameRequested;
	bool saveGameAudioRequested;

	// L07: DONE 4: Calculate some timing measures
	// required variables are provided:
	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;
	float dt = 0.0f;
};

extern App* app;

#endif	// __APP_H__