#pragma once

namespace BRShapeType {
	enum ShapeType {
		None,
		Square,
		Circle
	};
}

namespace BRComponentType {
	enum ComponentType {
		None,
		Transform,
		Physics,
		Renderer,
		Player
	};
}

namespace BRAxisType {
	enum AxisType {
		None = 0,
		Diagonal = 1,
		Vertical = 2,
		Horizontal = 3
	};
}

namespace BRObjectType {
	enum ObjectType {
		None,
		Doodad, //Traversible
		Solid,
		Liquid,
		Player,
		Enemy,
		PickUp,
		PowerUp
	};

}