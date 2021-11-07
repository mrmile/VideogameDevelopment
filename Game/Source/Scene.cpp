#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene(bool start_enabled) : Module(start_enabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// L03: DONE: Load map
	//app->map->Load("hello.tmx");
	app->map->Load("fortress.tmx");
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/fortress.ogg");

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

	app->render->camera.x = app->map->MapToWorld(0, -15).x;
	app->render->camera.y = app->map->MapToWorld(0, -15).y;

	//NULL COLLIDER --> (experimental test for camera functions and other mechanical stuff related with old type colliders
	app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(1200), app->map->MapToWorldSingle(100) }, Collider::Type::NULL_COLLIDER);

	app->collisions->AddCollider({ app->map->MapToWorldSingle(0), app->map->MapToWorldSingle(16), app->map->MapToWorldSingle(19), app->map->MapToWorldSingle(7) }, Collider::Type::H_CB);
	app->collisions->AddCollider({ app->map->MapToWorldSingle(118), app->map->MapToWorldSingle(13), app->map->MapToWorldSingle(10), app->map->MapToWorldSingle(10) }, Collider::Type::H_CB);

	//app->map->LoadColliders(); Old version makes the game laggy but with TMX 
	 app->map->LoadCollidersNewer(); //New version creating the colliders by hand
	 app->map->LoadLavaColliders();

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	sceneTimer++;
	//app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 640;
	//app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 160; //<-- Este es el que se aplica al final

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
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	if (app->player->horizontalCM == false && sceneTimer > 1) app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 630;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	//App->scene_game->holeSensor3->body->DestroyFixture(App->scene_game->holeSensor3->body->GetFixtureList());
	

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

		if (bodyB->body == app->player->Player->body && bodyA->body == app->scene->h_CB1->body)
		{

			filter.categoryBits = 0x0002;
			filter.maskBits = 0x0002 | 0x0001;

			//b2Vec2 position;
			//position.x = 688;
			//position.y = 820;

			LOG("Player Collision");
			//app->player->Player->body->GetFixtureList()->SetFilterData(filter);
			//app->player->player->body->DestroyFixture();

			if (app->player->horizontalCM == false)
			{
				app->player->horizontalCM = true;
			}
			
		}
		else if (bodyB->body == app->player->Player->body && bodyA->body != app->scene->h_CB1->body)
		{
			if (app->player->horizontalCM == true)
			{
				app->player->horizontalCM = false;
			}
		}
	}
}
*/