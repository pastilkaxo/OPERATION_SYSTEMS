#include <iostream>
#include <Windows.h>
using namespace std;

DWORD pid = NULL;

DWORD WINAPI OS04_02_T1() { // Спецификатор типа
	DWORD tid = GetCurrentThreadId();
	unsigned long long d = MAXLONGLONG / 1000000000;
	for (unsigned long long i = 0; i < 50; i++) {
			Sleep(1000);
			cout << i << " -> " << "PID: " << pid <<
				"; OS04_02_T1: " << tid << endl;
	
	}
	return 0;
}

DWORD WINAPI OS04_02_T2() {
	DWORD tid = GetCurrentThreadId();
	unsigned long long d = MAXLONGLONG / 1000000000;
	for (unsigned long long i = 0; i < 125; i++) {
			Sleep(1000);
			cout << i << " -> " << "PID: " << pid <<
				"; OS04_02_T2: " << tid << endl;
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
	NULL, // Параметры безопастности
	0,  // Размер стека
	(LPTHREAD_START_ROUTINE)OS04_02_T1 //  функция потока
	,NULL // Параметры для функции
	,0 // Флаги создания
	,&Child1Id // Ид потока
	);

	HANDLE t2Child = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)OS04_02_T2
		, NULL
		, 0
		, &Child2Id
	);



	for (int i = 0; i < 100; i++) {
		Sleep(1000);
		cout <<" Main -> " << "OS04_02: " << pid << "; TID:" << tid << endl;
		cout << "===========================" << endl;
   }

	WaitForSingleObject(t1Child,INFINITE); //  ожидает завершения указанного объекта
	WaitForSingleObject(t2Child, INFINITE);
	CloseHandle(t1Child); //  закрывает дескрпиторы обьекта
	CloseHandle(t2Child);

	system("pause");
	return 0;

}

