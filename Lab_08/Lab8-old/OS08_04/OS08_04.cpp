#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <locale>

using namespace std;

void sh(HANDLE heap) {
	SetConsoleOutputCP(1251);
	PROCESS_HEAP_ENTRY phe;
	SIZE_T total = 0, unstopped = 0 , alloc = 0, unalloc = 0;
	phe.lpData = NULL;
	while (HeapWalk(heap,&phe)) {
		total += phe.cbData;
		if (phe.wFlags & PROCESS_HEAP_REGION) {
			unstopped += phe.cbData;
		}
		else if (phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) {
			unalloc += phe.cbData;
		}
		else {
			alloc += phe.cbData;
		}
	}

	cout << "[TOTAL]:" << total << endl;
	cout << "[Неприравная]:" << unstopped << endl;
	cout << "[Распределенная]:" << alloc << endl;
	cout << "[Нераспределенная]:" << unalloc << endl;
	cout << " <------------------------------------- \n\n";
}

int main() {
	HANDLE heap = GetProcessHeap();
	sh(heap);
	int size = 300000;
	int* a = new int[size];
	cout << ">-- a" << hex << a << ", arr.size = " << dec << size << "\n\n";
	sh(heap);
	system("pause");
	return 0;
}