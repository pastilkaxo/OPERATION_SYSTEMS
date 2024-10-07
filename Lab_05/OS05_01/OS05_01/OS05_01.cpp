#include <Windows.h>
#include <iostream>
#include <bitset>

using namespace std;

void printProcessPrty(HANDLE h) {
	DWORD prty = GetPriorityClass(h);
	cout << "-----> PID: " << GetCurrentProcessId() << endl;
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
	cout << "---> TID: " << GetCurrentThreadId() << endl;

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

	cout << "[Process Affinity Mask] HEX:" << showbase << hex << pa  << " BIN: " << bitset<sizeof(sa) * 2>(pa) << endl;
	cout << "[System Affinity Mask]  HEX:" << showbase << hex << sa << " BIN: "  << bitset<sizeof(sa) * 2>(sa) << endl;

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



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "=================== OS05_01: Лемешевский В.О. =======================\n";

	HANDLE hp = GetCurrentProcess(); // текущий процесс
	HANDLE ht = GetCurrentThread(); // текущий поток

	printProcessPrty(hp);
	printThreadPrty(ht);
	PrintAffinityMask(hp);
	PrintTotalProcessors(hp, ht);



	cout << "=================== End. =======================\n";
	system("pause");
	return 0;





}

