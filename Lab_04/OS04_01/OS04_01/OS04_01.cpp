#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	for (int i = 0; i < 100; i++) {
		Sleep(1000);
		cout << "PID: " << GetCurrentProcessId() << " ; "
			"TID: "<< GetCurrentThreadId() << endl;
	
	}
}

