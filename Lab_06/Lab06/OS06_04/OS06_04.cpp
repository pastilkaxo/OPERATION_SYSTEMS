#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;


int main() {
	pid = GetCurrentProcessId();
	LPCWSTR an1 = L"C:\\Users\\Влад\\Desktop\\Лемешевский_ОС_ИСиТ_3_2\\Lab_06\\Lab06\\x64\\Debug\\OS06_04A.exe";
	LPCWSTR an2 = L"C:\\Users\\Влад\\Desktop\\Лемешевский_ОС_ИСиТ_3_2\\Lab_06\\Lab06\\x64\\Debug\\OS06_04B.exe";
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	

	HANDLE hs = CreateSemaphore(NULL,2,2,L"VladSemaphore");

	if (hs != NULL) {
		cout << "Semaphore created\n";
	}

	{
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		if (CreateProcess(
			an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1
		)) {
			cout << "------> OS06_04A: Created\n";
		}
		else {
			cout << "------> OS06_04A: Not Created\n";
		}

	}
	{
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		if (CreateProcess(
			an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2
		)) {
			cout << "------> OS06_04B: Created\n";
		}
		else {
			cout << "------> OS06_04B: Not Created\n";
		}

	}


	for (int i = 1; i <= 90; i++) {

		if (i == 30) {
			WaitForSingleObject(hs, INFINITE);  // Войти в критическую секцию
		}

		cout << i << ". MAIN OS06_04  [PID]:" << pid << endl;
		Sleep(100);

		if (i == 60) {
			ReleaseSemaphore(hs, 1, NULL);  // Выйти из критической секции
		}
		Sleep(100);

	}
	LONG prevcount;
	ReleaseSemaphore(hs,1,&prevcount);

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(hs);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	cout << "---------> MAIN: FINISHED\n";




	return 0;
}