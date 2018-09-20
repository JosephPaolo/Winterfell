//Display the CPU speed and architecture.

#include "InitBlueRapsol.h"
#include <windows.h>
#include <iostream> 
#include <string>

using namespace std;

//Display CPU Speed
void InitBlueRapsol::DisplayCPUSpeed() {
	string sMHz;
	string sArch;
	DWORD BufSize = _MAX_PATH;
	DWORD dwMHz = _MAX_PATH;
	DWORD type = REG_DWORD;
	HKEY hKey;
	
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0)", 0, KEY_READ, &hKey);
	if (lError != ERROR_SUCCESS) {
		cout << "CPU Speed: Error! Cannot display CPU Speed; Key not found.\n";
		return;
	}
	RegQueryValueEx(hKey, "~MHz", NULL, NULL, (LPBYTE)&dwMHz, &BufSize);
	sMHz = to_string(dwMHz);
	cout << "CPU Speed: " << sMHz << endl;

}

//Display CPU Architecture
void InitBlueRapsol::DisplayCPUArch() {
	SYSTEM_INFO system;

	GetSystemInfo(&system);
	//GetNativeSystemInfo(&system);

	//Info on https://msdn.microsoft.com/en-us/library/windows/desktop/ms724958(v=vs.85).aspx
	switch (system.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_ALPHA:
			cout << "CPU Architecture: Alpha 32 bit by Digital Equipment Corp" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_ALPHA64:
			cout << "CPU Architecture: Alpha 64 bit by Digital Equipment Corp" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_AMD64:
			cout << "CPU Architecture: AMD/Intel x64" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_ARM:
			cout << "CPU Architecture: ARM" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_ARM64:
			cout << "CPU Architecture: ARM64" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_IA64:
			cout << "CPU Architecture: Intel Itanium Based" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
			cout << "CPU Architecture: 0A" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_INTEL:
			cout << "CPU Architecture: Intel x86" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_MIPS:
			cout << "CPU Architecture: MIPS" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_MSIL:
			cout << "CPU Architecture: MSIL" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_PPC:
			cout << "CPU Architecture: PowerPC" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_SHX:
			cout << "CPU Architecture: ShX" << endl;
			return;
		case PROCESSOR_ARCHITECTURE_UNKNOWN:
			cout << "CPU Architecture: Unknown" << endl;
			return;
		default:
			cout << "CPU Architecture: Not Detected" << endl;
			return;
	}

}