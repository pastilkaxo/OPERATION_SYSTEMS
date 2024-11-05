#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;


int main() {
	pid = GetCurrentProcessId();
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"VladSemaphore");
	
	if (hs == NULL) {
		cout << "Semaphore Error: " << GetLastError() << endl;
	}
	else {
		cout << "OS06_04A: Open Semaphore\n";
	}
	
	

	for (int i = 1; i <= 90; i++) {

		if(i == 30)
			WaitForSingleObject(hs, INFINITE);

		if(i==60)
			ReleaseSemaphore(hs, 1, NULL);


		cout << i << ". OS06_04A  [PID]:" << pid << endl;




		Sleep(100);

	}
	CloseHandle(hs);
	cout << "---------> OS06_04A: FINISHED\n";



	return 0;
}