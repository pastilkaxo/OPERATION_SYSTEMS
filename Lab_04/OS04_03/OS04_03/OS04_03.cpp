#include <iostream>
#include <Windows.h>
using namespace std;

DWORD pid = NULL;

DWORD WINAPI OS04_03_T1() {
	DWORD tid = GetCurrentThreadId();
	for (unsigned long long i = 0; i < 50; i++) {
		Sleep(1000);
		cout << i << " -> " << "PID: " << pid <<
			"; OS04_03_T1: " << tid << endl;

	}
	return 0;
}

DWORD WINAPI OS04_03_T2() {
	DWORD tid = GetCurrentThreadId();
	for (unsigned long long i = 0; i < 125; i++) {
		Sleep(1000);
		cout << i << " -> " << "PID: " << pid <<
			"; OS04_03_T2: " << tid << endl;
	}
	return 0;
}


int main()
{
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId(); // хранилище инициализатора описатель типа
	unsigned long long d = MAXLONGLONG / 1000000000;
	DWORD Child1Id = NULL,
		Child2Id = NULL;

	HANDLE t1Child = CreateThread(  // дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс. С помощью дескприторов можно ссылаться на окна, объекты ядра, графические объекты и т.п.
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)OS04_03_T1
		, NULL
		, 0
		, &Child1Id
	);

	HANDLE t2Child = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)OS04_03_T2
		, NULL
		, 0
		, &Child2Id
	);



	for (int i = 0; i < 100; i++) {
		if (i == 5) { SuspendThread(t1Child); cout << "OS04_03_T1: Suspended\n"; }
		if (i == 10) { ResumeThread(t1Child); cout << "OS04_03_T1: Resumed\n"; }
		if (i == 40) { SuspendThread(t2Child); cout << "OS04_03_T2: Suspended\n"; }
		Sleep(1000);
		cout << " Main -> " << "OS04_03: " << pid << "; TID:" << tid << endl;
		cout << "===========================" << endl;
	}
	cout << "OS04_03_T2: Resumed\n";
	ResumeThread(t2Child);

	WaitForSingleObject(t1Child, INFINITE); // ждет, когда объект, хэндл которого был передан первым аргументом, перейдет в сигнальное состояние или завершится.
	WaitForSingleObject(t2Child, INFINITE);
	CloseHandle(t1Child);
	CloseHandle(t2Child);

	system("pause");
	return 0;

}

