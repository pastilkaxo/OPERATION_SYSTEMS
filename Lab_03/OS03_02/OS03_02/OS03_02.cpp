#include <iostream>
#include <Windows.h>
using namespace std;

// 5.	Приложение OS03_02 должно создавать 
// два дочерних процесса OS03_02_1 и OS03_02_2.


int main()
{

	LPCWSTR f1 = L"C:\\Users\\Влад\\Desktop\\Лемешевский_ОС_ИСиТ_3_2\\Lab_03\\OS03_02_1\\x64\\Debug\\OS03_02_1.exe"; // ссыкла на исполняемые модули
	LPCWSTR f2 = L"C:\\Users\\Влад\\Desktop\\Лемешевский_ОС_ИСиТ_3_2\\Lab_03\\OS03_02_2\\x64\\Debug\\OS03_02_2.exe";

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
			CREATE_NEW_CONSOLE, // флаги создания, управляющие приоритетом и параметрами процесса; конкретно этот создает новый инстанс консоли
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
			CREATE_NEW_CONSOLE,
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


	for (int i = 0; i < 100; i++)
	{
	Sleep(1000);
	cout << GetCurrentProcessId() << endl;
	}

	WaitForSingleObject(pi1.hProcess,INFINITE); // Бесконечное ожидание завершения дочернего процесса пока оба не завершаться
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess); // Закритие происходит вручную/явно

	return 0;
}


