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
		Physics
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