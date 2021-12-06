#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneCastle.h"
#include "SceneForest.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "TitleScreen.h"

#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

SceneForest::SceneForest(bool start_enabled) : Module(start_enabled)
{
	name.Create("SceneForest");
}

// Destructor
SceneForest::~SceneForest()
{}

// Called before render is available
bool SceneForest::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneForest::Start()
{
	// L03: DONE: Load map
	//app->map->Load("hello.tmx");
	app->map->Load("forest.tmx");
	
	Mix_ResumeMusic();
	Mix_SetMusicPosition(0);
	// Load music
	app->audio->PlayMusic("Assets/audio/music/jungle.ogg");

	sceneTimer = 0;

	//b2Filter filter;

	//filter.categoryBits = 1;

	//filter.categoryBits = 0x0001;
	//filter.maskBits = 0x0001;

	//h_CB1 = app->physics->CreateRectangleSensor(app->map->MapToWorldSingle(0) + app->map->MapToWorldSingle(15) / 2, app->map->MapToWorldSingle(16) + app->map->MapToWorldSingle(7) / 2, app->map->MapToWorldSingle(15), app->map->MapToWorldSingle(7));
	//h_CB1->listener = this;
	//h_CB1->body->GetFixtureList()->SetFilterData(filter);

	//h_CB2 = app->physics->CreateRectangleSensor(app->map->MapToWorldSingle(118) + app->map->MapToWorldSingle(10) / 2, app->map->MapToWorldSingle(13) + app->map->MapToWorldSingle(10) / 2, app->map->MapToWorldSingle(10), app->map->MapToWorldSingle(10));
	//h_CB2->listener = this;
	//h_CB2->body->GetFixtureList()->SetFilterData(filter);

	app->render->camera.x = app->map->MapToWorld(-87, -12).x;
	app->render->camera.y = app->map->MapToWorld(-87, -12).y;

	//NULL COLLIDER --> (experimental test for camera functions and other mechanical stuff related with old type colliders
	//app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(1200), app->map->MapToWorldSingle(100) }, Collider::Type::NULL_COLLIDER);

	//app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(16), app->map->MapToWorldSingle(19), app->map->MapToWorldSingle(7) }, Collider::Type::H_CB);
	//app->collisions->AddCollider({ app->map->MapToWorldSingle(118), app->map->MapToWorldSingle(13), app->map->MapToWorldSingle(10), app->map->MapToWorldSingle(10) }, Collider::Type::H_CB);

	//app->map->LoadColliders(); Old version makes the game laggy but with TMX 
	//app->map->LoadCollidersNewer(); //New version creating the colliders by hand (not needed any more)
	//app->map->LoadCollidersSensors();
	 
	 //app->map->LoadLavaColliders();

	 godMode = false;
	 playerRestart = false;
	 destroyScene = false;
	 sceneForest = true;
	 app->sceneCastle->sceneCastle = false;

	return true;
}

// Called each loop iteration
bool SceneForest::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneForest::Update(float dt)
{
	sceneTimer++;
	//app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 640;
	//app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 160; //<-- Este es el que se aplica al final
	//F9 --> See colliders

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
		playerRestart = true;

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		godMode = !godMode;

    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		app->SaveGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		app->render->camera.y -= 5;

	if(app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		app->render->camera.y += 5;

	if(app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		app->render->camera.x -= 5;

	if(app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		app->render->camera.x += 5;

	//app->render->DrawTexture(img, 380, 100); // Placeholder not needed any more

	// Draw map
	app->map->Draw();

	if (app->player->destroyed == true && app->player->destroyedDelay < 1)
	{
		Mix_PauseMusic();
		//app->audio->PlayFx(dead);
	}

	// L03: DONE 7: Set the window title with map/tileset info
	/*
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());
	*/

	//app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool SceneForest::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	// L08: TODO 6: Make the camera movement independent of framerate

	if (app->player->horizontalCB == false && app->player->bidimensionalCB == false && sceneTimer > 1) app->render->camera.x = (-(app->player->Player->body->GetPosition().x * 150) + 630);
	//if (app->player->verticalCB == false && app->player->bidimensionalCB == false && sceneTimer > 1) app->render->camera.y = -(app->player->Player->body->GetPosition().y * 150) + 380; //450
	//if (app->player->verticalCB == false && app->player->bidimensionalCB == false && sceneTimer > 1) app->render->camera.y -= app->player->Player->body->GetLinearVelocity().y * 3;
	if (-app->player->position.y > app->render->camera.y / 2 + -52) app->render->camera.y += 10;
	if (-app->player->position.y < app->render->camera.y / 2 + -92) app->render->camera.y -= 10;

	if (app->render->camera.y < app->map->MapToWorldSingle(-12)) app->render->camera.y = app->map->MapToWorldSingle(-12);
	if (app->render->camera.y > app->map->MapToWorldSingle(0)) app->render->camera.y = app->map->MapToWorldSingle(0);

	if (app->player->destroyedDelay > 210 && app->player->destroyedDelay <= 211)
	{
		app->titleScreen->Enable();

		app->player->Disable();
		app->sceneForest->Disable();
		app->collisions->Disable();
		app->map->Disable();
		//app->physics->Disable();
	}

	return ret;
}

// Called before quitting
bool SceneForest::CleanUp()
{
	LOG("Freeing scene");

	//app->sceneCastle_game->holeSensor3->body->DestroyFixture(app->sceneCastle_game->holeSensor3->body->GetFixtureList());
	//app->collisions->RemoveCollider(app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(1200), app->map->MapToWorldSingle(100) }, Collider::Type::NULL_COLLIDER));
	//app->collisions->RemoveCollider(app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(16), app->map->MapToWorldSingle(19), app->map->MapToWorldSingle(7) }, Collider::Type::H_CB));
	//app->collisions->RemoveCollider(app->collisions->AddCollider({ app->map->MapToWorldSingle(118), app->map->MapToWorldSingle(13), app->map->MapToWorldSingle(10), app->map->MapToWorldSingle(10) }, Collider::Type::H_CB));

	//app->collisions->RemoveCollider(app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(1200), app->map->MapToWorldSingle(100) }, Collider::Type::NULL_COLLIDER));

	//app->map->DeleteCollidersSensors();
	destroyScene = true;
	sceneForest = false;

	return true;
}

/*
void Scene::b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyA != nullptr && bodyB != nullptr)
	{
		b2Filter filter;
		filter.categoryBits = 0x0001;
		filter.maskBits = 0x0001;

		if (bodyB->body == app->player->Player->body && bodyA->body == app->sceneCastle->h_CB1->body)
		{

			filter.categoryBits = 0x0002;
			filter.maskBits = 0x0002 | 0x0001;

			//b2Vec2 position;
			//position.x = 688;
			//position.y = 820;

			LOG("Player Collision");
			//app->player->Player->body->GetFixtureList()->SetFilterData(filter);
			//app->player->player->body->DestroyFixture();

			if (app->player->horizontalCB == false)
			{
				app->player->horizontalCB = true;
			}
			
		}
		else if (bodyB->body == app->player->Player->body && bodyA->body != app->sceneCastle->h_CB1->body)
		{
			if (app->player->horizontalCB == true)
			{
				app->player->horizontalCB = false;
			}
		}
	}
}
*/