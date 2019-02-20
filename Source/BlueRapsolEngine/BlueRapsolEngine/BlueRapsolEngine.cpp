//*************************************************************************** 
// File name: InitBlueRapsol.h
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Sept. 19, 2018
// Version: 0.0.1A
// Description: 
//   This Class will represent the Game Application layer of the Blue Rapsol Engine
// *****************************************************************************


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
	float splashDuration = 4.0f; //splash screen duration in seconds
	//sf::RenderTexture renderTexture;
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	mTimer.Start(); //Start the game timer
	mTimer.Reset();

	//Give some time to show splash screen because initializing might be too quick. All this does is delay the main loop.
	while (mTimer.TotalTime() < splashDuration && renderWindow.isOpen()) {
		mTimer.Tick(); //Ticks the timer
	}

	mTimer.Reset();

	OutputDebugString(L"\nEntering main loop...\n");

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

		renderWindow.clear(sf::Color::Black); //Clear the window with black color
		//window.draw(...); //Draw everything here...
		renderWindow.display(); //End the current frame
	}
}

void BlueRapsolEngine::GameStart() {

}

void BlueRapsolEngine::GameUpdate() {

}

//Insures only one of this application is running
bool BlueRapsolEngine::IsOnlyInstance(LPCTSTR appName) {
	HANDLE handle = CreateMutex(NULL, TRUE, appName);

	if (GetLastError() != ERROR_SUCCESS) {
		//std::cout << "Error: An instance of this appication is already running" << std::endl;
		OutputDebugString(L"Error: An instance of this appication is already running\n");
		return false;
	}
	//std::cout << "No other instance of this application is found running" << std::endl;
	OutputDebugString(L"No other instance of this application is found running\n");
	return true;
}

//Check for required Storage space, notify user on insufficient space
bool BlueRapsolEngine::ChkStorage(unsigned long long requiredBytes, LPCWSTR directory) {
	std::wstring msg;
	ULARGE_INTEGER availableStorage;
	::GetDiskFreeSpaceEx(directory, &availableStorage, NULL, NULL);
	//std::cout << "Available storage memory: " + std::to_string(availableStorage.QuadPart / toMB) + " MB\n";
	msg = L"Available storage memory: " + std::to_wstring(availableStorage.QuadPart / toMB) + L" MB\n";
	OutputDebugString(msg.c_str());

	if (availableStorage.QuadPart < requiredBytes) {
		//std::cout << "Insufficient storage space! You require at least " + std::to_string(requiredBytes / toMB) + "MB in storage space.\n";
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
	//std::cout << "Available physical memory: " + std::to_string(memStat.ullAvailPhys / toMB) + " MB\n";
	//std::cout << "Available virtual memory: " + std::to_string(memStat.ullAvailVirtual / toMB) + " MB\n";

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
		//std::cout << "CPU Speed: Error! Cannot display CPU Speed; Key not found." << std::endl;
		OutputDebugString(L"CPU Speed: Error! Cannot display CPU Speed; Key not found.\n");
		return;
	}
	RegQueryValueEx(hKey, L"~MHz", NULL, NULL, (LPBYTE)&dwMHz, &BufSize);
	sMHz = std::to_wstring(dwMHz);

	//std::cout << "CPU Speed: " << sMHz << std::endl;
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
		//std::cout << "CPU Architecture: Alpha 32 bit by Digital Equipment Corp" << std::endl;
		OutputDebugString(L"CPU Architecture : Alpha 32 bit by Digital Equipment Corp\n");
		return;
	case PROCESSOR_ARCHITECTURE_ALPHA64:
		//std::cout << "CPU Architecture: Alpha 64 bit by Digital Equipment Corp" << std::endl;
		OutputDebugString(L"CPU Architecture: Alpha 64 bit by Digital Equipment Corp\n");
		return;
	case PROCESSOR_ARCHITECTURE_AMD64:
		//std::cout << "CPU Architecture: AMD/Intel x64" << std::endl;
		OutputDebugString(L"CPU Architecture: AMD/Intel x64\n");
		return;
	case PROCESSOR_ARCHITECTURE_ARM:
		//std::cout << "CPU Architecture: ARM" << std::endl;
		OutputDebugString(L"CPU Architecture: ARM\n");
		return;
	case PROCESSOR_ARCHITECTURE_ARM64:
		//std::cout << "CPU Architecture: ARM64" << std::endl;
		OutputDebugString(L"CPU Architecture: ARM64\n");
		return;
	case PROCESSOR_ARCHITECTURE_IA64:
		//std::cout << "CPU Architecture: Intel Itanium Based" << std::endl;
		OutputDebugString(L"CPU Architecture: Intel Itanium Based\n");
		return;
	case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
		//std::cout << "CPU Architecture: 0A" << std::endl;
		OutputDebugString(L"CPU Architecture: 0A\n");
		return;
	case PROCESSOR_ARCHITECTURE_INTEL:
		//std::cout << "CPU Architecture: Intel x86" << std::endl;
		OutputDebugString(L"CPU Architecture: Intel x86\n");
		return;
	case PROCESSOR_ARCHITECTURE_MIPS:
		//std::cout << "CPU Architecture: MIPS" << std::endl;
		OutputDebugString(L"CPU Architecture: MIPS\n");
		return;
	case PROCESSOR_ARCHITECTURE_MSIL:
		//std::cout << "CPU Architecture: MSIL" << std::endl;
		OutputDebugString(L"CPU Architecture: MSIL\n");
		return;
	case PROCESSOR_ARCHITECTURE_PPC:
		//std::cout << "CPU Architecture: PowerPC" << std::endl;
		OutputDebugString(L"CPU Architecture: PowerPC\n");
		return;
	case PROCESSOR_ARCHITECTURE_SHX:
		//std::cout << "CPU Architecture: ShX" << std::endl;
		OutputDebugString(L"CPU Architecture: ShX\n");
		return;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		//std::cout << "CPU Architecture: Unknown" << std::endl;
		OutputDebugString(L"CPU Architecture: Unknown\n");
		return;
	default:
		//std::cout << "CPU Architecture: Not Detected" << std::endl;
		OutputDebugString(L"CPU Architecture: Not Detected\n");
		return;
	}

}