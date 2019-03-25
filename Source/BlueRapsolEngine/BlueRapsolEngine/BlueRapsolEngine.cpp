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
	OutputDebugString(L"\nChecking System Memory...\n");
	ChkMem();
	ChkStorage(REQUIRED_STORAGE, STORAGE_DIRECTORY); //TODO terminate on false

	OutputDebugString(L"\nChecking CPU...\n");
	DisplayCPUArch();
	DisplayCPUSpeed();
}

bool BlueRapsolEngine::Initialize() {

	//System Check
	if (!IsOnlyInstance(MUTEX_APP_NAME)) {
		return false;
	}

	return true;
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

	while (renderWindow.isOpen()) {
		sf::Event event;
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { // "close requested" event: we close the window
				renderWindow.close();
			}
		}

		if (!isPaused) {
			mTimer.Tick(); //Ticks the timer
			GameUpdate(); //Update game logic
			physicsSys.UpdatePhysics(allObjects);
		}

		graphicsSys.DrawRenderObjects(renderWindow, allObjects);
		//DrawRenderObjects(renderWindow); //Draw Object in the scene
	}
}

//this code executes once at the beginning
//NOTICE: Moved to BlueRapsolApp.cpp! Write code there instead as it overrides these functions.
void BlueRapsolEngine::GameStart() {

}

//This code executes every tick
//NOTICE: Moved to BlueRapsolApp.cpp! Write code there instead as it overrides these functions.
void BlueRapsolEngine::GameUpdate() {
	
}

int BlueRapsolEngine::Instantiate() {
	auto objHolder = std::make_unique<GameObject>();

	allObjects.push_back(std::move(objHolder));
	getObjIndex.insert(std::make_pair(std::to_string(getObjIndex.size() - 1), getObjIndex.size() - 1));

	return allObjects.size() - 1; //return allObjects index 
}

int BlueRapsolEngine::Instantiate(std::string setKey) {
	auto objHolder = std::make_unique<GameObject>();

	allObjects.push_back(std::move(objHolder));
	getObjIndex.insert(std::make_pair(setKey, allObjects.size() - 1));

	return allObjects.size() - 1; //return allObjects index 
}

int BlueRapsolEngine::Instantiate(std::string setKey, float xPos, float yPos) {
	auto objHolder = std::make_unique<GameObject>(xPos, yPos);

	allObjects.push_back(std::move(objHolder));
	getObjIndex.insert(std::make_pair(setKey, allObjects.size() - 1));

	return allObjects.size() - 1; //return allObjects index 
}

int BlueRapsolEngine::Instantiate(std::string setKey, BRDataType::Vector2 setPos) {
	auto objHolder = std::make_unique<GameObject>(setPos.x, setPos.y);

	allObjects.push_back(std::move(objHolder));
	getObjIndex.insert(std::make_pair(setKey, allObjects.size() - 1));

	return allObjects.size() - 1; //return allObjects index 
}

int BlueRapsolEngine::Instantiate(std::string setKey, float xPos, float yPos, float width, float height) {
	auto objHolder = std::make_unique<GameObject>(xPos, yPos, width, height);

	allObjects.push_back(std::move(objHolder));
	getObjIndex.insert(std::make_pair(setKey, allObjects.size() - 1));

	return allObjects.size() - 1; //return allObjects index 
}

int BlueRapsolEngine::Instantiate(std::string setKey, std::string setSprite, float xPos, float yPos) {
	auto objHolder = std::make_unique<GameObject>(xPos, yPos);
	objHolder.get()->GetRenderComponent()->renderObjPtr.get()->setTexture(graphicsSys.textureMap[setSprite]);
	objHolder.get()->GetRenderComponent()->renderObjPtr.get()->setScale(sf::Vector2f(1.0f, 1.0f));
	allObjects.push_back(std::move(objHolder));
	getObjIndex.insert(std::make_pair(setKey, allObjects.size() - 1));

	return allObjects.size() - 1; //return allObjects index 
}

int BlueRapsolEngine::Instantiate(std::string setKey, std::string setSprite, float xPos, float yPos, float colliderWidth, float colliderHeight) {
	auto objHolder = std::make_unique<GameObject>(xPos, yPos, colliderWidth, colliderHeight);
	objHolder.get()->GetRenderComponent()->renderObjPtr.get()->setTexture(graphicsSys.textureMap[setSprite]);
	//objHolder.get()->GetRenderComponent()->renderObjPtr.get()->setScale(sf::Vector2f(scaleWidth, scaleHeight));
	allObjects.push_back(std::move(objHolder));
	getObjIndex.insert(std::make_pair(setKey, allObjects.size() - 1));

	return allObjects.size() - 1; //return allObjects index 
}

//Insures only one of this application is running
bool BlueRapsolEngine::IsOnlyInstance(LPCTSTR appName) {
	HANDLE handle = CreateMutex(NULL, TRUE, appName);

	OutputDebugString(L"\nChecking if another instance of the application is running...\n");

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
		OutputDebugString(L"CPU Architecture: Alpha 32 bit by Digital Equipment Corp\n");
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