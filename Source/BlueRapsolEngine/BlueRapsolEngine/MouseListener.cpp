#include "MouseListener.h" 

using namespace BRDataType;

//Constructor
MouseListener::MouseListener() {
	initMsg = L"";
	xMousePos = 0;
	yMousePos = 0;
	btnState = 0;
}

bool MouseListener::VOnBtnDown(unsigned int const kcode) {

	//Display key pressed
	initMsg = L"Mouse Button Pressed Down: ";
	OutputDebugString(initMsg.c_str());
	MouseListener::VDebugPrintInput(kcode);

	return true;
}

bool MouseListener::VOnBtnUp(unsigned int const kcode) {

	//Display key released
	initMsg = L"Mouse Button Released: ";
	OutputDebugString(initMsg.c_str());
	MouseListener::VDebugPrintInput(kcode);

	return true;
}

bool MouseListener::OnMouseMove(WPARAM btnState, int x, int y) {
	return true;
}

Vector2 MouseListener::getMousePos() {
	return Vector2(xMousePos, yMousePos);
}

void MouseListener::setMousePos(float getX, float getY) {
	xMousePos = getX; yMousePos = getY;
}

void MouseListener::VDebugPrintInput(unsigned int const kcode) {
	switch (kcode) {
		case VK_LBUTTON:
			initMsg = L"Left Mouse Button";
			break;
		case VK_RBUTTON:
			initMsg = L"Right Mouse Button";
			break;
		case VK_MBUTTON:
			initMsg = L"Middle Mouse Button";
			break;
		case VK_XBUTTON1:
			initMsg = L"X1 Mouse Button";
			break;
		case VK_XBUTTON2:
			initMsg = L"X2 Mouse Button";
			break;
		default:
			initMsg = kcode;
			break;
	}

	OutputDebugString(initMsg.c_str());
	OutputDebugString(L"\n");
}