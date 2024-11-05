#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;


int main() {
	pid = GetCurrentProcessId();
	HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"vladMutex");
	if (hm == NULL) {
		cout << "OS06_03A: Error Open Mutex! Error code: " << GetLastError() << endl;
	}
	else {
		cout << "OS06_03A: Opened Mutex\n";
	}
	for (int i = 1; i <= 90; i++) {

		if (i == 30)
			WaitForSingleObject(hm, INFINITE);

		if (i == 60)
			ReleaseMutex(hm);

		cout << i << ". OS06_03A  [PID]:" << pid << endl;

		Sleep(100);

	}
	CloseHandle(hm);
	cout << "---------> OS06_03A: FINISHED\n";



	return 0;
}