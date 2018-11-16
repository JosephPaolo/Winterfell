#pragma once

namespace BRDataType {
	struct Vector2 {
		float x;
		float y;

		//Constructors
		Vector2() {
			x = 0; y = 0;
		}

		Vector2(float getX, float getY) {
			x = getX; y = getY;
		}
	};

	struct Vector3 {
		float x;
		float y;
		float z;

		//Constructors
		Vector3() {
			x = 0; y = 0; z = 0;
		}

		Vector3(float getX, float getY, float getZ) {
			x = getX; y = getY; z = getZ;
		}
	};

	struct Vector4 {
		float x;
		float y;
		float z;
		float w;

		//Constructors
		Vector4() {
			x = 0; y = 0; z = 0; w = 0;
		}

		Vector4(float getX, float getY, float getZ, float getW) {
			x = getX; y = getY; z = getZ; w = getW;
		}
	};
}


