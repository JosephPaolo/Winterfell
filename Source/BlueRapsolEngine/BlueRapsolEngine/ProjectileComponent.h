#pragma once

#include "BRDataTypes.h"
#include "BaseComponent.h"

using namespace BRDataType;

class ProjectileComponent : public BaseComponent{
	
public:
	Vector2 vector;
	float speed;
	int damage;

};
