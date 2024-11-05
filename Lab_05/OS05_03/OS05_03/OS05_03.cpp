#include <Windows.h>
#include <iostream>
#include <bitset>
#include <string>
using namespace std;


void printProcessPrty(HANDLE h) {
	DWORD prty = GetPriorityClass(h);
	cout << "-----> PID: " << dec << GetCurrentProcessId() << endl;
	switch (prty) {
	case IDLE_PRIORITY_CLASS: cout << "----+ priority [P]: IDLE_PRIORITY_CLASS\n"; break;
	case BELOW_NORMAL_PRIORITY_CLASS: cout << "----+ priority [P]:  BELOW_NORMAL_PRIORITY_CLASS\n"; break;
	case NORMAL_PRIORITY_CLASS: cout << "----+ priority [P]: NORMAL_PRIORITY_CLASS\n"; break;
	case ABOVE_NORMAL_PRIORITY_CLASS: cout << "----+ priority [P]: ABOVE_NORMAL_PRIORITY_CLASS\n"; break;
	case HIGH_PRIORITY_CLASS: cout << "----+ priority [P]: HIGH_PRIORITY_CLASS\n"; break;
	case REALTIME_PRIORITY_CLASS: cout << "----+ priority [P]: REALTIME_PRIORITY_CLASS\n"; break;
	default: cout << "----+ priority [P]: [NULL] \n"; break;
	}
}
void printThreadPrty(HANDLE h) {
	DWORD prty = GetThreadPriority(h);

	switch (prty) {
	case THREAD_PRIORITY_LOWEST: cout << "---+ priority [T]: THREAD_PRIORITY_LOWEST\n"; break;
	case THREAD_PRIORITY_BELOW_NORMAL: cout << "---+  priority [T]:  THREAD_PRIORITY_BELOW_NORMAL\n"; break;
	case THREAD_PRIORITY_NORMAL: cout << "---+  priority [T]:  THREAD_PRIORITY_NORMAL\n"; break;
	case THREAD_PRIORITY_ABOVE_NORMAL: cout << "---+  priority [T]: THREAD_PRIORITY_ABOVE_NORMAL\n"; break;
	case THREAD_PRIORITY_HIGHEST: cout << "---+ priority [T]: THREAD_PRIORITY_HIGHEST\n"; break;
	case THREAD_PRIORITY_IDLE: cout << "---+ priority [T]: THREAD_PRIORITY_IDLE\n"; break;
	case THREAD_PRIORITY_TIME_CRITICAL: cout << "---+ priority [T]: THREAD_PRIORITY_TIME_CRITICAL\n"; break;
	default: cout << "---+ priority [T]: [NULL] \n"; break;
	}

}


void PrintAffinityMask(HANDLE h) {
	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
	char buf[10];
	if (!GetProcessAffinityMask(h, &pa, &sa)) throw "GetProcessAffinityMask [Exception]";

	cout << "[Process Affinity Mask] HEX:" << showbase << hex << pa << " BIN: " << bitset<sizeof(sa) * 2>(pa) << endl;
	cout << "[System Affinity Mask]  HEX:" << showbase << hex << sa << " BIN: " << bitset<sizeof(sa) * 2>(sa) << endl;

}


void PrintTotalProcessors(HANDLE h1, HANDLE h2) {
	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
	SYSTEM_INFO sys_info;


	if (!GetProcessAffinityMask(h1, &pa, &sa)) throw "GetProcessAffinityMask";

	GetSystemInfo(&sys_info);
	cout << "Max processors count:  " << dec << sys_info.dwNumberOfProcessors << "\n";
	icpu = SetThreadIdealProcessor(h2, MAXIMUM_PROCESSORS);
	cout << "Thread IdealProcessor: " << dec << icpu << "\n";

}



DWORD WINAPI TA() {
	HANDLE hp = GetCurrentProcess(); // текущий процесс
	HANDLE ht = GetCurrentThread(); // текущий поток
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	for (int i = 0; i < 1000000; i++) {
		if (i % 1000 == 0) {
			cout << "=================== OS05_02x: Лемешевский В.О. =======================\n";

			cout << "I: " << dec << i << endl;
			cout << "PID: "<< dec << pid << dec << " TID: " << tid << endl;
			//printProcessPrty(hp);
			printThreadPrty(ht);
			//PrintAffinityMask(hp);
			Sleep(2000);
		}
	}
	return 0;
}


DWORD getProcessPrty(int p) {
	switch (p) {
	case 1: return IDLE_PRIORITY_CLASS;
	case 2: return BELOW_NORMAL_PRIORITY_CLASS;
	case 3: return NORMAL_PRIORITY_CLASS;
	case 4: return ABOVE_NORMAL_PRIORITY_CLASS;
	case 5: return HIGH_PRIORITY_CLASS;
	case 6: return REALTIME_PRIORITY_CLASS;
	default: throw  "----+ priority [P]: [NULL] \n";
	}
}




DWORD getThreadPrty(int i)
{
	switch (i)
	{
	case 1: return THREAD_PRIORITY_LOWEST;
	case 2: return THREAD_PRIORITY_BELOW_NORMAL;
	case 3: return THREAD_PRIORITY_NORMAL;
	case 4: return THREAD_PRIORITY_ABOVE_NORMAL;
	case 5: return THREAD_PRIORITY_HIGHEST;
	case 6: return THREAD_PRIORITY_IDLE;
	default: throw "----+ priority [T]: [NULL] \n";
	}
}




void GetPrevInfo(HANDLE h) {
	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;

	if (!GetProcessAffinityMask(h, &pa, &sa)) throw "GetProcessAffinityMask [Exception]";

	cout << "PREV: [Process Affinity Mask] HEX:" << showbase << hex << pa << " BIN: " << bitset<sizeof(sa) * 2>(pa) << endl;
	cout << "PREV: [System Affinity Mask]  HEX:" << showbase << hex << sa << " BIN: " << bitset<sizeof(sa) * 2>(sa) << endl;

}


void GetUpdatedInfo(HANDLE h) {
	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
	if (!GetProcessAffinityMask(h, &pa, &sa)) throw "GetProcessAffinityMask [Exception]";

	cout << "NEW: [Process Affinity Mask] HEX:" << showbase << hex << pa << " BIN: " << bitset<sizeof(sa) * 2>(pa) << endl;
	cout << "NEW: [System Affinity Mask]  HEX:" << showbase << hex << sa << " BIN: " << bitset<sizeof(sa) * 2>(sa) << endl;

}



void Create_TA_Thread(int prty1, int prty2) {

	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId(); // хранилище инициализатора описатель типа
	DWORD Child1Id = NULL,
		Child2Id = NULL;

	HANDLE t1Child = CreateThread(  // дескриптор, т.е. число, с помощью которого можно идентифицировать ресурс. С помощью дескприторов можно ссылаться на окна, объекты ядра, графические объекты и т.п.
		NULL, // Параметры безопастности
		0,  // Размер стека
		(LPTHREAD_START_ROUTINE)TA//  функция потока
		, NULL // Параметры для функции
		, 0 // Флаги создания
		, &Child1Id // Ид потока
	);

	HANDLE t2Child = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)TA
		, NULL
		, 0
		, &Child2Id
	);


	SetThreadPriority(t1Child, getThreadPrty(prty1));
	SetThreadPriority(t2Child, getThreadPrty(prty2));

	printThreadPrty(t1Child);
	printThreadPrty(t2Child);


	WaitForSingleObject(t1Child, INFINITE); //  ожидает завершения указанного объекта
	WaitForSingleObject(t2Child, INFINITE);

	CloseHandle(t1Child); //  закрывает дескрпиторы обьекта
	CloseHandle(t2Child);

}

void ShowResult(int par1, int par2, int par3,int par4) {



	HANDLE process = GetCurrentProcess();
	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;


	GetPrevInfo(process);
	cout << "============================================\n";
	if (!SetProcessAffinityMask(process, par1)) throw "SetProcessAffinityMask [Exception]";
	GetUpdatedInfo(process);
	SetPriorityClass(process,getProcessPrty(par2));
	cout << "============================================\n";
	cout << "Main. [PriorityClass]: " ;
	printProcessPrty(process);
	cout << "============================================\n";
	cout << "============================================\n";
	cout << "============================================\n";
	cout << "============================================\n";
	Create_TA_Thread(par3,par4);

}

int main(int argc, char* argv[]) {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//ShowResult(255,3,3,3);
	ShowResult(255,3,1,5);
	//ShowResult(1,3,1,5);

	return 0;

}

// 65535 - 16 потоков | 16383 - 14 | 4095 - 12 | 1023 - 10 |
//  255 - 8 | 63 - 6 | 15 - 4 | 3 - 2 | 1 - 1