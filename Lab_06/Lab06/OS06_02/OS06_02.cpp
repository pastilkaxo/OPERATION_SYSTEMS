#include <iostream>
#include <Windows.h>

using namespace std;

DWORD pid = NULL;
CRITICAL_SECTION cs;

DWORD WINAPI A() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 1; i <= 90; i++) {
		if (i == 30)
			EnterCriticalSection(&cs);

		cout << i << ". " << "[A]:" << tid << endl;

		if (i == 60)
			LeaveCriticalSection(&cs);

		Sleep(1000);
	}
	cout << "---------> A: FINISHED\n";
	return 0;
}


DWORD WINAPI B() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 1; i <= 90; i++) {
		if (i == 30)
			EnterCriticalSection(&cs);

		cout << i << ". " << "[B]:" << tid << endl;


		if (i == 60)
			LeaveCriticalSection(&cs);


		Sleep(1000);
	}
	cout << "---------> B: FINISHED\n";

	return 0;
}



int main() {
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	DWORD ChildId = NULL;
	HANDLE hChild[2];



	 hChild[0] = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)A,NULL,0,&ChildId);

	 hChild[1] = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)B, NULL, 0, &ChildId);

	InitializeCriticalSection(&cs);
	for (int i = 1; i <= 90; i++) {
		if(i==30)
			EnterCriticalSection(&cs);

		cout << i << ". MAIN  [PID]:" << pid << "; [Thread]:" << tid << endl;

		if (i == 60)
			LeaveCriticalSection(&cs);

		Sleep(1000);

	}

	cout << "---------> MAIN: FINISHED\n";



	WaitForMultipleObjects(2,hChild,TRUE,INFINITE);

	DeleteCriticalSection(&cs);

	CloseHandle(hChild[0]);
	CloseHandle(hChild[1]);

	return 0;
}