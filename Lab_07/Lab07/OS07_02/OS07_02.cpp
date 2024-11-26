#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	unsigned long long i = 0;
	clock_t t1 = clock();
	bool flag = false;

	while (true)
	{
		i++;

		if (((clock() - t1) / CLOCKS_PER_SEC) == 5 && !flag) {
			cout << "[5 SEC] i:" << i << "\n";
			flag = true;
		}
		if (((clock() - t1) / CLOCKS_PER_SEC) == 10 && flag) {
			cout << "[10 SEC] i:" << i << "\n";
			flag = false;
		}
		if (((clock() - t1) / CLOCKS_PER_SEC) == 15) {
			cout << "[15 SEC] i:" << i << "\n";
			break;
		}
	}

	system("pause");
	return 0;
}