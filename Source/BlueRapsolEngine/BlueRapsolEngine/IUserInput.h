#pragma once

#include "BRDataTypes.h"

using namespace BRDataType;

class IUserInput {
public:
	virtual bool VOnBtnDown(unsigned int const kcode) = 0;
	virtual bool VOnBtnUp(unsigned int const kcode) = 0;

private:
	virtual void VDebugPrintInput(unsigned int const kcode) = 0;
	//virtual Vector2 getCursorPos() = 0; //In windows, the position of the cursor is still present even if the mouse is not used.
};