#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <TlHelp32.h>
using namespace std;

int main() {
	DWORD pid = GetCurrentProcessId(); // ид текущего процесса
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL,0); // делает снапшот текущих процессов системы
	PROCESSENTRY32 peProcessEntry; // структура со списком процессов из снапшота
	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	cout << "Curr. PID: " << pid << endl << "-------------------" << endl;
	try {
		if (!Process32First(snap, &peProcessEntry)) {
			throw "Process32First";
		}
		else {
			do {
				if (peProcessEntry.th32ProcessID == pid) {
					cout << "=== !!! Currentryly running process !!! ====" << endl;
				}
					wcout << " Process Name: " << peProcessEntry.szExeFile << endl;
					wcout << " PID: " << peProcessEntry.th32ProcessID << endl;
					wcout << " Parent PID: " << peProcessEntry.th32ParentProcessID << endl;
					cout << "===================================" << endl;
			} while (Process32Next(snap, &peProcessEntry));
		}
		
	}
	catch(char* msg){
		cout << msg << endl;
	}
	system("pause");
	return 0;
}