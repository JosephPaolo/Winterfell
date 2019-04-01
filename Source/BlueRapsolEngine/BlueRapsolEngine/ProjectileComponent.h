#pragma once

#include "BRDataTypes.h"
#include "BaseComponent.h"

using namespace BRDataType;

class ProjectileComponent : BaseComponent{
	
public:
	Vector2 vector;
	float speed;
	int damage;

};
