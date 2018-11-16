#include "IUserInput.h" 
#include "BRDataTypes.h" 
#include <Windows.h>
#include <WinBase.h>
#include <conio.h>
#include <string>

#pragma once

using namespace BRDataType;

class MouseListener : IUserInput {
private:
	std::wstring initMsg;
	float xMousePos;
	float yMousePos;
	WPARAM btnState;

	void VDebugPrintInput(unsigned int const kcode);

public:
	MouseListener(); //Constructor

	bool VOnBtnDown(unsigned int const kcode);
	bool VOnBtnUp(unsigned int const kcode);
	bool OnMouseMove(WPARAM btnState, int x, int y);
	Vector2 getMousePos();
	void setMousePos(float getX, float getY);
};