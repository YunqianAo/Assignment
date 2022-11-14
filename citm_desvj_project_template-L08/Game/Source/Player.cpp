#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Window.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
	name.Create("players");
	idleAnim1.PushBack({ 1, 0, 14,17  });
	idleAnim1.loop = true;
	idleAnim1.speed = 0.001f;

	leftAnim1.PushBack({ 1, 36, 14, 17 });
	leftAnim1.PushBack({ 17,36, 14, 17 });
	leftAnim1.PushBack({ 33, 36, 14, 17 });
	leftAnim1.loop = true;
	leftAnim1.speed = 0.1f;

	rightAnim1.PushBack({ 2, 54, 14, 17 });
	rightAnim1.PushBack({ 18, 54, 14, 17 });
	rightAnim1.PushBack({ 34, 54, 14, 17 });
	rightAnim1.loop = true;
	rightAnim1.speed = 0.1f;
}

Player::~Player() {
	
}

bool Player::Awake() {

	//L02: DONE 1: Initialize Player parameters
	//pos = position;
	

	//L02: DONE 5: Get Player parameters from XML
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	//texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {
	
	
	//initilize textures
	texture = app->tex->Load(texturePath);
	currentAnim1 = &idleAnim1;

	// L07 DONE 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateCircle(position.x, position.y, 8, bodyType::DYNAMIC);

	// L07 DONE 6: Assign player class (using "this") to the listener of the pbody. This makes the Physics module to call the OnCollision method
	pbody->listener = this; 

	// L07 DONE 7: Assign collider type
	pbody->ctype = ColliderType::PLAYER;

	//initialize audio effect - !! Path is hardcoded, should be loaded from config.xml
	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");

	return true;
}

bool Player::Update()
{

	// L07 DONE 5: Add physics to the player - updated player position using physics

	int speed = 5; 
	int speedY = 5;
	b2Vec2 vel = b2Vec2(0, -GRAVITY_Y); 
	currentAnim1 = &idleAnim1;
	//L02: DONE 4: modify the position of the player using arrow keys and render the texture
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		//
		speedY = -150;
		vel = b2Vec2(0, speedY);
	}
	
		
	
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP) {
		//
	}
		
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		currentAnim1 = &leftAnim1;
		vel = b2Vec2(-speed, -GRAVITY_Y);
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		currentAnim1 = &rightAnim1;
		vel = b2Vec2(speed, -GRAVITY_Y);
	}

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	//app->render->DrawTexture(texture, position.x , position.y);
	currentAnim1->Update();
	
	return true;
}

bool Player::CleanUp()
{
	
	return true;
}
bool Player::PostUpdate() {
	SDL_Rect rect = currentAnim1->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x+9, position.y+25 - rect.h, &rect);
	return true;
}

// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
		case ColliderType::ITEM:
			LOG("Collision ITEM");
			app->audio->PlayFx(pickCoinFxId);
			break;
		case ColliderType::PLATFORM:
			LOG("Collision PLATFORM");
			break;
		case ColliderType::UNKNOWN:
			LOG("Collision UNKNOWN");
			break;
	}
	


}
