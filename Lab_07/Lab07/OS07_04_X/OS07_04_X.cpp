#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

bool flag = true;

bool isSimple(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void printNumberedPrimes() {
    int number = 2;  
    int i = 1;  

    while (true) {
        if (isSimple(number)) {
            cout  << "[i]:" << i << " [Number]: " << number << std::endl;
            i++;
            Sleep(100);
        }
        number++;
    }
}


int main(){
	cout << clock() << " : OS07_04_x - 1" << endl;
	HANDLE htimer = OpenWaitableTimer(TIMER_ALL_ACCESS,FALSE,L"vladTimer2");

    if (!htimer)
        cout << "Timer not opened!\n";

    printNumberedPrimes();



	WaitForSingleObject(htimer, INFINITE);
	


	cout << clock() << " : OS07_04_x - 2" << endl;
	system("pause");
	return 0;
}