//Check for multiple Instances

#include "InitBlueRapsol.h" 
#include <windows.h>
#include <WinBase.h>
#include <iostream> 

using namespace std;

bool InitBlueRapsol::IsOnlyInstance(LPCTSTR appName) {
	HANDLE handle = CreateMutex(NULL, TRUE, appName); //attempt to create Mutex

	if (GetLastError() != ERROR_SUCCESS) { //if attempt to create mutex causes error
		cout << "Error: An instance of this application is already running!" << endl;
		return false;
	}

	//if mutex is created successfully, attempts to run another of the same 
	//program will have then first check for the existance of this created Mutex.
	//Note: Mutex insure only one of the app can be running on a machine.
	cout << "No other instance of this application is found running." << endl;
	return true;
}