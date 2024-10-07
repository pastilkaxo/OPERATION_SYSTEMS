#include <Windows.h>
#include <iostream>
#include <bitset>
#include <string>
using namespace std;




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



void CreateXProcesses(int prty1 , int prty2) {
	LPCWSTR f1 = L"C:\\Users\\Влад\\Desktop\\Лемешевский_ОС_ИСиТ_3_2\\Lab_05\\OS05_02x\\x64\\Debug\\OS05_02x.exe"; // ссыкла на исполняемые модули
	LPCWSTR f2 = L"C:\\Users\\Влад\\Desktop\\Лемешевский_ОС_ИСиТ_3_2\\Lab_05\\OS05_02x\\x64\\Debug\\OS05_02x.exe";

	STARTUPINFO si1, si2; // структура для определения внешнего вида окна для нового процесса
	PROCESS_INFORMATION pi1, pi2; // структура с информацией о процессе и его потоке

	ZeroMemory(&si1, sizeof(STARTUPINFO));
	si1.cb = sizeof(STARTUPINFO); // size

	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si2.cb = sizeof(STARTUPINFO);

	if (  // Создание дочернего процесса
		CreateProcess(
			f1, // имя исполняемого модуля
			NULL,// командная строка параметры
			NULL, // может ли возвращаемый дескриптор быть унаследован дочерними процессами
			NULL, // может ли возвращаемый дескриптор быть унаследован дочерними потоками
			FALSE, // каждый возвращаемый дескриптор наследуется дочерним процессом
			CREATE_NEW_CONSOLE | getProcessPrty(prty1), // флаги создания, управляющие приоритетом и параметрами процесса; конкретно этот создает новый инстанс консоли
			NULL, // блок конфигурации нового процесса
			NULL, // олный путь дочернего процесса
			&si1, // внешний вид окна
			&pi1 // дескрипторы процесса и первичного потока
		)
		) {
		cout << "==== Process: OS03_02_01 created ====";
	}
	else {
		cout << "==== Process: OS03_02_01 not created ====";

	}

	if (
		CreateProcess(
			f2,
			NULL,
			NULL,
			NULL,
			FALSE,
			CREATE_NEW_CONSOLE | getProcessPrty(prty2),
			NULL,
			NULL,
			&si2,
			&pi2
		)
		) {
		cout << "==== Process: OS03_02_02 created ====\n" << endl;
	}
	else {
		cout << "==== Process: OS03_02_02 not created ====\n" << endl;

	}



	WaitForSingleObject(pi1.hProcess, INFINITE); // Бесконечное ожидание завершения дочернего процесса пока оба не завершаться
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess); // Закритие происходит вручную/явно

}

void ShowResult(string par1 , string par2 ,string par3) {
	int p1 = stoi(par1);
	int p2 = stoi(par2);
	int p3 = stoi(par3);



	HANDLE process = GetCurrentProcess();
	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;


	GetPrevInfo(process);
	cout << "============================================\n";
	if (!SetProcessAffinityMask(process, p1)) throw "SetProcessAffinityMask [Exception]";
	GetUpdatedInfo(process);
	cout << "============================================\n";
	cout << "1. [PriorityClass]: " << to_string(getProcessPrty(p2)) << endl;
	cout << "2. [PriorityClass]: " << to_string(getProcessPrty(p3)) << endl;
	cout << "============================================\n";
	CreateXProcesses(p2, p3);

}

int main(int argc,char* argv[]) {

		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		
		ShowResult("255","3","3");
		//ShowResult("255", "2", "5");
		//ShowResult("1", "2", "5");

		return 0;

}

// 65535 - 16 потоков | 16383 - 14 | 4095 - 12 | 1023 - 10 |
//  255 - 8 | 63 - 6 | 15 - 4 | 3 - 2 | 1 - 1