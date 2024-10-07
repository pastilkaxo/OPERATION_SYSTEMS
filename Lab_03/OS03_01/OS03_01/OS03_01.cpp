#include <iostream>
#include <Windows.h> // Для системных вызово
using namespace std;


int main()
{
	for (int i = 0; i < 1000; i++)
	{
		Sleep(1000);
		cout << GetCurrentProcessId() << endl;
	}
}


