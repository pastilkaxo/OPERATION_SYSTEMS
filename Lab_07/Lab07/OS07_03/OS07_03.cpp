#include <Windows.h>
#include <iostream>
#include <ctime>
#define SECOND 10000000

using namespace std;

HANDLE htimer = NULL;

DWORD WINAPI ChildThread()
{
	WaitForSingleObject(htimer, INFINITE);
	cout << clock() << ": ChildThread" << "\n";
	return 0;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	htimer = CreateWaitableTimer(NULL, FALSE, NULL);
	long long it = -3 * SECOND;
	unsigned long long i = 0;
	short n = 0;
	clock_t t1 = clock();
	while (true)
	{
		i++;
		if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 0, NULL, NULL, FALSE)) throw "[ERROR]: SetWaitableTimer";
		DWORD ChildId = 0;
		HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, NULL, &ChildId);
		WaitForSingleObject(hChild, INFINITE);
		cout << ((clock() - t1) / CLOCKS_PER_SEC) << " сек. [i] = " << i << "\n";
		if (((clock() - t1) / CLOCKS_PER_SEC) == 15) {
			cout << "[DONE] i:" << i << "\n";
			break;
		}
	}

	system("pause");
	return 0;
}