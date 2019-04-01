#pragma once

#include "BaseComponent.h"

class MobComponent : BaseComponent{

public:
	int maxhealth;
	int health;
	float speed;
	int damage;

	void ApplyDamage(int getDamage); //use negative numbers to heal
	void ApplyDeath();

};
