#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"

using namespace BRComponentType;

TransformComponent::TransformComponent() {
	type = Transform;

	position.x = 0;
	position.y = 0;
	position.z = 0;

	eulerAngles.x = 0;
	eulerAngles.y = 0;
	eulerAngles.z = 0;

	scalar.x = 1;
	scalar.y = 1;
	scalar.z = 1;
}