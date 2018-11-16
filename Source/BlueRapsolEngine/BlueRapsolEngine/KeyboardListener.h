#include "IUserInput.h" 
#include <Windows.h>
#include <WinBase.h>
#include <conio.h>
#include <string>

#pragma once

class KeyboardListener : IUserInput {
private:
	std::wstring initMsg;

	void VDebugPrintInput(unsigned int const kcode);
public:
	KeyboardListener();

	bool VOnBtnDown(unsigned int const kcode);
	bool VOnBtnUp(unsigned int const kcode);
};