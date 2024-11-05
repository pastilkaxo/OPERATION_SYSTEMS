#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;


int main() {
	pid = GetCurrentProcessId();
	LPCWSTR an1 = L"C:\\Users\\Влад\\Desktop\\OS06_05A\\x64\\Debug\\OS06_05A.exe";
	LPCWSTR an2 = L"C:\\Users\\Влад\\Desktop\\OS06_05B\\x64\\Debug\\OS06_05B.exe";
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	HANDLE he = CreateEvent(NULL, TRUE, FALSE, L"vladEvent");

	{
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		if (CreateProcess(
			an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1
		)) {
			cout << "------> OS06_05A: Created\n";
		}
		else {
			cout << "------> OS06_05A: Not Created\n";
		}

	}
	{
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		if (CreateProcess(
			an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2
		)) {
			cout << "------> OS06_05B: Created\n";
		}
		else {
			cout << "------> OS06_05B: Not Created\n";
		}

	}


	for (int i = 1; i <= 90; i++) {

		if (i == 16) {
			SetEvent(he); // Разрешает другим процессам начать выполнение после 15 итераций
		}

		cout << i << ". MAIN OS06_04  [PID]:" << pid << endl;

		Sleep(1000);

	}



	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(he);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	cout << "---------> MAIN: FINISHED\n";




	return 0;
}