#pragma once

namespace BlueRapsolEnums {
	enum ShapeType {
		Square,
		Circle
	};

	enum ComponentType {
		Transform,
		Physics,
		Renderer,
		Mobile,
		Controllable,
		Projectile
	};

	enum AxisType {
		None = 0,
		Diagonal = 1,
		Vertical = 2,
		Horizontal = 3
	};

	enum ObjectType {
		Doodad, //Traversible
		Solid,
		Liquid,
		Playable,
		Enemy,
		PickUp,
		PowerUp
	};

}