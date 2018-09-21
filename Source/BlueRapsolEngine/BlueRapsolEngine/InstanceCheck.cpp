//Check for multiple Instances
//File Lab2 section 1
//Author Tsuzuri Terry Mizore Okada 101095454
//Created on 2018 -09 -20
//Updated on 2018 09 - 21

#include "InitBlueRapsol.h" 
#include <windows.h>
#include <WinBase.h>
#include <iostream>

using namespace std;

bool InitBlueRapsol::IsOnlyInstance(LPCTSTR appName) {
	HANDLE handle = CreateMutex(NULL, TRUE, appName);

	if (GetLastError() != ERROR_SUCCESS) {
		cout << "Error: An instance of this appication is already running" << endl;
		return false;
	}
	cout << "No other instance of this application is found running" << endl;

	return true;
}