#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	for (int i = 0; i < 50; i++)
	{
		Sleep(1000);
		cout << i << " OS03_02_1: " << GetCurrentProcessId() << endl;
	}
}
