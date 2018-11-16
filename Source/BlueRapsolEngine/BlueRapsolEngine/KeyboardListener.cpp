#include "KeyboardListener.h" 

//Constructor
KeyboardListener::KeyboardListener() {
	initMsg = L"";
}

bool KeyboardListener::VOnBtnDown(unsigned int const kcode) {

	//Display key pressed
	initMsg = L"Key Pressed Down: ";
	OutputDebugString(initMsg.c_str());
	KeyboardListener::VDebugPrintInput(kcode);

	return true;
}

bool KeyboardListener::VOnBtnUp(unsigned int const kcode) {

	//Display key released
	initMsg = L"Key Released: ";
	OutputDebugString(initMsg.c_str());
	KeyboardListener::VDebugPrintInput(kcode);

	return true;
}

void KeyboardListener::VDebugPrintInput(unsigned int const kcode) {
	switch (kcode) {
		case VK_BACK:
			initMsg = L"Backspace";
			break;
		case VK_TAB:
			initMsg = L"Tab";
			break;
		case VK_CLEAR:
			initMsg = L"Clear";
			break;
		case VK_RETURN:
			initMsg = L"Return";
			break;
		case VK_LSHIFT:
			initMsg = L"Left Shift";
			break;
		case VK_RSHIFT:
			initMsg = L"Right Shift";
			break;
		case VK_SHIFT:
			initMsg = L"Shift";
			break;
		case VK_LCONTROL:
			initMsg = L"Left Control";
			break;
		case VK_RCONTROL:
			initMsg = L"Right Control";
			break;
		case VK_CONTROL:
			initMsg = L"Control";
			break;
		case VK_LMENU:
			initMsg = L"Left Menu";
			break;
		case VK_RMENU:
			initMsg = L"Right Menu";
			break;
		case VK_MENU:
			initMsg = L"Menu";
			break;
		case VK_PAUSE:
			initMsg = L"Pause";
			break;
		case VK_CAPITAL: //CAPS Lock
			initMsg = L"Caps Lock";
			break;
		case VK_ESCAPE: //ESC
			initMsg = L"Escape";
			break;
		case VK_CONVERT:
			initMsg = L"Convert";
			break;
		case VK_NONCONVERT:
			initMsg = L"Non convert";
			break;
		case VK_ACCEPT:
			initMsg = L"Accept";
			break;
		case VK_MODECHANGE:
			initMsg = L"Mode Change";
			break;
		case VK_SPACE: 
			initMsg = L"Spacebar";
			break;
		case VK_PRIOR: //Page Up
			initMsg = L"Page Up";
			break;
		case VK_NEXT: //Page Down
			initMsg = L"Page Down";
			break;
		case VK_END:
			initMsg = L"End";
			break;
		case VK_HOME:
			initMsg = L"Home";
			break;
		case VK_LEFT:
			initMsg = L"keft Arrow";
			break;
		case VK_UP:
			initMsg = L"Up Arrow";
			break;
		case VK_RIGHT:
			initMsg = L"Right Arrow";
			break;
		case VK_DOWN:
			initMsg = L"Down Arrow";
			break;
		case VK_SELECT: 
			initMsg = L"Select";
			break;
		case VK_PRINT: 
			initMsg = L"Print";
			break;
		case VK_EXECUTE:
			initMsg = L"Execute";
			break;
		case VK_SNAPSHOT: //Print Screen
			initMsg = L"Print Screen";
			break;
		case VK_INSERT:
			initMsg = L"Insert";
			break;
		case VK_DELETE:
			initMsg = L"Delete";
			break;
		case VK_HELP:
			initMsg = L"Help";
			break;
		case VK_SLEEP:
			initMsg = L"Sleep";
			break;
		case VK_NUMPAD0:
			initMsg = L"Numpad 0";
			break;
		case VK_NUMPAD1:
			initMsg = L"Numpad 1";
			break;
		case VK_NUMPAD2:
			initMsg = L"Numpad 2";
			break;
		case VK_NUMPAD3:
			initMsg = L"Numpad 3";
			break;
		case VK_NUMPAD4:
			initMsg = L"Numpad 4";
			break;
		case VK_NUMPAD5:
			initMsg = L"Numpad 5";
			break;
		case VK_NUMPAD6:
			initMsg = L"Numpad 6";
			break;
		case VK_NUMPAD7:
			initMsg = L"Numpad 7";
			break;
		case VK_NUMPAD8:
			initMsg = L"Numpad 8";
			break;
		case VK_NUMPAD9:
			initMsg = L"Numpad 9";
			break;
		case VK_MULTIPLY:
			initMsg = L"*";
			break;
		case VK_ADD:
			initMsg = L"+";
			break;
		case VK_SEPARATOR:
			initMsg = L"Separator";
			break;
		case VK_SUBTRACT:
			initMsg = L"-";
			break;
		case VK_DECIMAL: 
			initMsg = L"Decimal";
			break;
		case VK_DIVIDE: 
			initMsg = L"/";
			break;
		case VK_F1:
			initMsg = L"F1";
			break;
		case VK_F2:
			initMsg = L"F2";
			break;
		case VK_F3:
			initMsg = L"F3";
			break;
		case VK_F4:
			initMsg = L"F4";
			break;
		case VK_F5:
			initMsg = L"F5";
			break;
		case VK_F6:
			initMsg = L"F6";
			break;
		case VK_F7:
			initMsg = L"F7";
			break;
		case VK_F8:
			initMsg = L"F8";
			break;
		case VK_F9:
			initMsg = L"F9";
			break;
		case VK_F10:
			initMsg = L"F10";
			break;
		case VK_F11:
			initMsg = L"F11";
			break;
		case VK_F12:
			initMsg = L"F12";
			break;
		case VK_NUMLOCK:
			initMsg = L"Num Lock";
			break;
		case VK_SCROLL:
			initMsg = L"Scroll Lock";
			break;
		case VK_VOLUME_MUTE:
			initMsg = L"Volume Mute";
			break;
		case VK_VOLUME_UP:
			initMsg = L"Volume Up";
			break;
		case VK_VOLUME_DOWN:
			initMsg = L"Volume Down";
			break;
		case VK_OEM_PLUS:
			initMsg = L"+";
			break;
		case VK_OEM_MINUS:
			initMsg = L"-";
			break;
		case VK_OEM_2: // /?
			initMsg = L"/?";
			break;
		case VK_OEM_3: // ~
			initMsg = L"~";
			break;
		case VK_OEM_4: //[{
			initMsg = L"[{";
			break;
		case VK_OEM_5: //\|
			initMsg = L"\|";
			break;
		case VK_OEM_6: //]}
			initMsg = L"]}";
			break;
		case VK_OEM_7: //'"
			initMsg = L"\"\'";
			break;
		default: //
			initMsg = kcode;
			break;
	}

	OutputDebugString(initMsg.c_str());
	OutputDebugString(L"\n");
}

