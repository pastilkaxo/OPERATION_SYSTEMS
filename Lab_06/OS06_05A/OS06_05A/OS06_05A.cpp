#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;


int main() {
	pid = GetCurrentProcessId();
	HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"vladEvent");

	if (he == NULL) {
		cout << "Event Error: " << GetLastError() << endl;
	}
	else {
		cout << "OS06_05A: Open Event\n";
	}

	WaitForSingleObject(he, INFINITE);
	for (int i = 1; i <= 90; i++) {
		cout << i << ". OS06_05B  [PID]:" << pid << endl;
		Sleep(100);
	}
	CloseHandle(he);
	cout << "---------> OS06_05B: FINISHED\n";



	return 0;
}