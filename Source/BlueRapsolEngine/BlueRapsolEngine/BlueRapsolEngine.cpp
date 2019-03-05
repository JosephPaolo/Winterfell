//*************************************************************************** 
// File name: BlueRapsolEnigne.cpp
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Feb. 21, 2019
// Version: 0.1.0A
// Description: 
//   This Class will represent the Game Application layer of the Blue Rapsol Engine
// *****************************************************************************

#include <stdio.h>
#include "BlueRapsolEngine.h"; 
//#include <iostream> 

//Macros

//300 MB in bytes
#define REQUIRED_STORAGE 314572800
//Temp macro for storage directory
#define STORAGE_DIRECTORY L"c:\\"

//Name of this program for Mutex
#define MUTEX_APP_NAME L"BlueRapsolEngineMutex"

//Used in converting units of measurements from bytes
const LONGLONG toKB = 1024;
const LONGLONG toMB = 1024 * toKB;
const LONGLONG toGB = 1024 * toMB;

BlueRapsolEngine::BlueRapsolEngine(HINSTANCE hInstance) {
	//System Check
	OutputDebugString(L"\nChecking if another instance of the application is running...\n");
	if (!IsOnlyInstance(MUTEX_APP_NAME)) {
		return;
	}

	OutputDebugString(L"\nChecking System Memory...\n");
	ChkMem();
	ChkStorage(REQUIRED_STORAGE, STORAGE_DIRECTORY); //TODO terminate on false

	OutputDebugString(L"\nChecking CPU...\n");
	DisplayCPUArch();
	DisplayCPUSpeed();
}

void BlueRapsolEngine::Run(HINSTANCE hInstance) {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Blue Rapsol Game"); //Creates the window
	isInitializing = true;

	//Initialization
	BlueRapsolEngine::Initialize(window);

	//TODO Program loop. Move loop from d3dApp.cpp
	BlueRapsolEngine::GameLoop(window);

}

void BlueRapsolEngine::Initialize(sf::RenderWindow & renderWindow) {
	SplashScreen splashObj;

	OutputDebugString(L"\nInitializing...\n");
	OutputDebugString(L"\nShowing Splash Screen...\n");
	if (isInitializing) {
		splashObj.Show(renderWindow);
	}

}

void BlueRapsolEngine::GameLoop(sf::RenderWindow & renderWindow) {
	std::wstring msg; //Used for formatting debug messages
	float splashDuration = 1.0f; //splash screen duration in seconds

	mTimer.Start(); //Start the game timer
	mTimer.Reset();

	//Give some time to show splash screen because initializing might be too quick. All this does is delay the main loop.
	while (mTimer.TotalTime() < splashDuration && renderWindow.isOpen()) {
		mTimer.Tick(); //Ticks the timer
	}

	OutputDebugString(L"\nEntering main loop...\n");

	mTimer.Reset();

	if (renderWindow.isOpen()) {
		
		GameStart();
	}

	while (renderWindow.isOpen()){
		sf::Event event;
		while (renderWindow.pollEvent(event)){
			if (event.type == sf::Event::Closed) { // "close requested" event: we close the window
				renderWindow.close();
			}
		}

		
		mTimer.Tick(); //Ticks the timer
		GameUpdate(); //Update game logic

		if (!stopObjs) {
			physicsSys.UpdatePhysics(allObjects);
			//graphicsSys.UpdateGraphics();
		}

		graphicsSys.DrawRenderObjects(renderWindow, allObjects);
		//DrawRenderObjects(renderWindow); //Draw Object in the scene
	}
}

//this code executes once at the beginning
void BlueRapsolEngine::GameStart() {
	std::wstring msg; //Used for formatting debug messages

	//Load Sound
	audioSys.LoadBuffer();

	//Play Sound
	audioSys.SoundPlay();

	//Example
	//Instantiate() creates a new GameObject and stores it in an array. Instantiate() returns the index position so you can reference the object later on.
	//Note: It uses a unique pointer so you cannot have multiple references of the same object. So you access the object through allObjects[ObjIndex].get().
	int ObjIndex = Instantiate(); //Creates a new GameObject and since it is the first one its index will be '0'
	allObjects[ObjIndex].get()->GetPhysicsComponent()->SetVelocity(0.05f, 0.05f); //The GameObject will visually move diagonally to the bottom right. Use GetPhysicsComponent() to access Physics component properties.
	
	Instantiate(); //Creates a second new GameObject and since it is the second one its index will be '1'

	Instantiate(); //Creates a third new GameObject and since it is the third one its index will be '2'
	allObjects[2].get()->GetTransformComponent()->SetParent(*allObjects[0].get()->GetTransformComponent()); //sets parent

	//Debugging Example
	//msg = L"Value of ObjIndex: " + std::to_wstring(ObjIndex) + L"\n";
	//OutputDebugString(msg.c_str());
}

//This code executes every tick
void BlueRapsolEngine::GameUpdate() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		audioSys.SoundPlay();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (stopObjs) {
			stopObjs = false;
		}
		else {
			stopObjs = true;
		}
	}
	
	if (!stopObjs) {
		//Example
		//This moves our second created object (index 1) towards the right by 0.2f every tick
		float newPositionX = allObjects[1].get()->GetTransformComponent()->GetPosition().x + 0.05f; //The original x position + 0.2f
		float newPositionY = allObjects[1].get()->GetTransformComponent()->GetPosition().y; //The original y position doesnt change
		allObjects[1].get()->GetTransformComponent()->SetPosition(newPositionX, newPositionY); //We pass the values to the object with SetPosition()

		float newAngle = allObjects[1].get()->GetTransformComponent()->GetEulerAngle() + 0.04;
		allObjects[1].get()->GetTransformComponent()->SetEulerAngle(newAngle);
	}
}

int BlueRapsolEngine::Instantiate() {
	auto objHolder = std::make_unique<GameObject>();

	//drawableHolder->setFillColor(sf::Color::White);

	allObjects.push_back(std::move(objHolder));

	return allObjects.size() - 1; //return allObjects index 
}

int BlueRapsolEngine::Instantiate(float xPos, float yPos) {
	auto objHolder = std::make_unique<GameObject>();

	//drawableHolder->setFillColor(sf::Color::White);

	allObjects.push_back(std::move(objHolder));

	return allObjects.size() - 1; //return allObjects index 
}

//Insures only one of this application is running
bool BlueRapsolEngine::IsOnlyInstance(LPCTSTR appName) {
	HANDLE handle = CreateMutex(NULL, TRUE, appName);

	if (GetLastError() != ERROR_SUCCESS) {
		OutputDebugString(L"Error: An instance of this appication is already running\n");
		return false;
	}
	OutputDebugString(L"No other instance of this application is found running\n");
	return true;
}

//Check for required Storage space, notify user on insufficient space
bool BlueRapsolEngine::ChkStorage(unsigned long long requiredBytes, LPCWSTR directory) {
	std::wstring msg;
	ULARGE_INTEGER availableStorage;
	::GetDiskFreeSpaceEx(directory, &availableStorage, NULL, NULL);
	msg = L"Available storage memory: " + std::to_wstring(availableStorage.QuadPart / toMB) + L" MB\n";
	OutputDebugString(msg.c_str());

	if (availableStorage.QuadPart < requiredBytes) {
		msg = L"Insufficient storage space! You require at least " + std::to_wstring(requiredBytes / toMB) + L"MB in storage space.\n";
		OutputDebugString(msg.c_str());
		return false;
	}

	return true;
}

//Check and display RAM and Virtual memory
void BlueRapsolEngine::ChkMem() {
	MEMORYSTATUSEX memStat;
	std::wstring msg;
	memStat.dwLength = sizeof(memStat); //Note: memStat.dwLength must be initialized before calling GlobalMemoryStatusEx()
	GlobalMemoryStatusEx(&memStat);

	//Display memory stats
	msg = L"Available physical memory: " + std::to_wstring(memStat.ullAvailPhys / toMB) + L" MB\n";
	OutputDebugString(msg.c_str());
	msg = L"Available virtual memory: " + std::to_wstring(memStat.ullAvailVirtual / toMB) + L" MB\n";
	OutputDebugString(msg.c_str());
}

//Display CPU Speed
void BlueRapsolEngine::DisplayCPUSpeed() {
	std::wstring sMHz;
	std::wstring sArch;
	std::wstring msg;

	DWORD BufSize = _MAX_PATH;
	DWORD dwMHz = _MAX_PATH;
	DWORD type = REG_DWORD;
	HKEY hKey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0)", 0, KEY_READ, &hKey);
	if (lError != ERROR_SUCCESS) {
		OutputDebugString(L"CPU Speed: Error! Cannot display CPU Speed; Key not found.\n");
		return;
	}
	RegQueryValueEx(hKey, L"~MHz", NULL, NULL, (LPBYTE)&dwMHz, &BufSize);
	sMHz = std::to_wstring(dwMHz);

	msg = L"CPU Speed: " + sMHz;
	OutputDebugString(msg.c_str());
}

//Display CPU Architecture
void BlueRapsolEngine::DisplayCPUArch() {
	SYSTEM_INFO system;

	GetSystemInfo(&system);
	//GetNativeSystemInfo(&system);

	//Info on https://msdn.microsoft.com/en-us/library/windows/desktop/ms724958(v=vs.85).aspx
	switch (system.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_ALPHA:
		OutputDebugString(L"CPU Architecture : Alpha 32 bit by Digital Equipment Corp\n");
		return;
	case PROCESSOR_ARCHITECTURE_ALPHA64:
		OutputDebugString(L"CPU Architecture: Alpha 64 bit by Digital Equipment Corp\n");
		return;
	case PROCESSOR_ARCHITECTURE_AMD64:
		OutputDebugString(L"CPU Architecture: AMD/Intel x64\n");
		return;
	case PROCESSOR_ARCHITECTURE_ARM:
		OutputDebugString(L"CPU Architecture: ARM\n");
		return;
	case PROCESSOR_ARCHITECTURE_ARM64:
		OutputDebugString(L"CPU Architecture: ARM64\n");
		return;
	case PROCESSOR_ARCHITECTURE_IA64:
		OutputDebugString(L"CPU Architecture: Intel Itanium Based\n");
		return;
	case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
		OutputDebugString(L"CPU Architecture: 0A\n");
		return;
	case PROCESSOR_ARCHITECTURE_INTEL:
		OutputDebugString(L"CPU Architecture: Intel x86\n");
		return;
	case PROCESSOR_ARCHITECTURE_MIPS:
		OutputDebugString(L"CPU Architecture: MIPS\n");
		return;
	case PROCESSOR_ARCHITECTURE_MSIL:
		OutputDebugString(L"CPU Architecture: MSIL\n");
		return;
	case PROCESSOR_ARCHITECTURE_PPC:
		OutputDebugString(L"CPU Architecture: PowerPC\n");
		return;
	case PROCESSOR_ARCHITECTURE_SHX:
		OutputDebugString(L"CPU Architecture: ShX\n");
		return;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		OutputDebugString(L"CPU Architecture: Unknown\n");
		return;
	default:
		OutputDebugString(L"CPU Architecture: Not Detected\n");
		return;
	}

}