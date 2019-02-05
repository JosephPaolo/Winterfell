#pragma once

#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/BRDataTypes.h"

class TransformComponent : public BaseComponent{

public:
	TransformComponent();

	BRDataType::Vector3 position;
	BRDataType::Vector3 eulerAngles;
	BRDataType::Vector3 scalar;
};
