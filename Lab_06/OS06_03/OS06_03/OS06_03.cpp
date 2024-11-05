#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;


int main() {
	pid = GetCurrentProcessId();
	LPCWSTR an1 = L"C:\\Users\\Влад\\Desktop\\OS06_03A\\x64\\Debug\\OS06_03A.exe";
	LPCWSTR an2 = L"C:\\Users\\Влад\\Desktop\\OS06_03B\\x64\\Debug\\OS06_03B.exe";
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;


	HANDLE hm = CreateMutex(NULL, FALSE, L"vladMutex");
	if (hm == NULL) {
		cout << "Error creating mutex: " << GetLastError() << endl;
		return 1;
	}
	else {
		cout << "Mutex created \n";
	}


	{
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		if (CreateProcess(
			an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1
		)) {
			cout << "------> OS06_03A: Created\n";
		}
		else {
			cout << "------> OS06_03A: Not Created\n";
		}

	}
	{
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		if (CreateProcess(
			an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2
		)) {
			cout << "------> OS06_03B: Created\n";
		}
		else {
			cout << "------> OS06_03B: Not Created\n";
		}

	}


	for (int i = 1; i <= 90; i++) {

		if (i == 30) {
			WaitForSingleObject(hm, INFINITE);
		}

		if (i == 60) {
			ReleaseMutex(hm);
		}

		cout << i << ". MAIN OS06_03  [PID]:" << pid << endl;
		Sleep(100);

	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);


	CloseHandle(hm);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	cout << "---------> MAIN: FINISHED\n";




	return 0;
}