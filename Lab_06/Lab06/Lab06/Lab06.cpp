
#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;
int check;
DWORD pid = NULL;


void EnterCriticalSectionAssembly()
{
	_asm // спецификатор, используемый для вставки кода на ассемблере непосредственно в C++ код. Следующий за ним блок {} выполнится на уровне ассемблера.
	{
	CriticalSection: // метка, которая позволяет организовать цикл ожидания. Поток будет возвращаться к этой метке, если он не может войти в критическую секцию.
		// префикс для обеспечения атомарного выполнения команды
		lock bts check, 0; //  проверяет значение бита 0 в переменной check и устанавливает его в 1 
		jc CriticalSection  // Если бит уже был установлен, переходит к метке CriticalSection и ждет
	}
}



void LeaveCriticalSectionAssembly()
{
	_asm lock btr check, 0 // которая проверяет значение бита 0 и сбрасывает его в 0.
	// Сброс бита 0 переменной check означает, что поток выходит из критической секции и освобождает ее для других потоков
}


DWORD WINAPI A() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 1; i <= 90; i++) {
		if (i == 30)
			EnterCriticalSectionAssembly();

		cout << i << ". " << "[A]:" << tid <<  " [Check]:" << check << endl;

		if (i == 60)
			LeaveCriticalSectionAssembly();

		Sleep(100);
	}
	cout << "---------> A: FINISHED\n";
	return 0;
}


DWORD WINAPI B() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 1; i <= 90; i++) {
		if (i == 30)
			EnterCriticalSectionAssembly();

		cout << i << ". " << "[B]:" << tid << " [Check]:" << check << endl;


		if (i == 60)
			LeaveCriticalSectionAssembly();


		Sleep(100);
	}
	cout << "---------> B: FINISHED\n";

	return 0;
}



int main()
{
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	DWORD ChildId = NULL;
	HANDLE hChild[2];

	hChild[0] = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)A, NULL, 0, &ChildId);

	hChild[1] = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)B, NULL, 0, &ChildId);

	for (int i = 1; i <= 90; i++) {
		if(i==30)
			EnterCriticalSectionAssembly();

		cout << i << ".  [PID]:" << pid << "; [Thread]:" << tid << " [Check]:"<< check << endl;

		if (i == 90)
			LeaveCriticalSectionAssembly();

		Sleep(100);

	}

	cout << "---------> MAIN: FINISHED\n";



	WaitForMultipleObjects(2, hChild, TRUE, INFINITE);

	CloseHandle(hChild[0]);
	CloseHandle(hChild[1]);

	return 0;
}