#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

struct SDL_Texture;

class Enemy : public Entity
{
public:

	Enemy();

	virtual ~Enemy();

	bool Awake();

	bool Start();

	bool Update();

	bool PostUpdate();

	bool CleanUp();

	// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
	void OnCollision(PhysBody* physA, PhysBody* physB);


public:
	Animation* currentAnim1 = nullptr;
	Animation idleAnim1;
	Animation downAnim1;
	Animation upAnim1;
	Animation rightAnim1;
	Animation leftAnim1;
	//class member variable
	int remainingJumpSteps;


private:

	//L02: DONE 1: Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// L07 DONE 5: Add physics to the player - declare a Physics body
	PhysBody* pbody;


	int pickCoinFxId;

	bool jumpTimer;
	int framesJump;


};

#endif // __ENEMY_H__