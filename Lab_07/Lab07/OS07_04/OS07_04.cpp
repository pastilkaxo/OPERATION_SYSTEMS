#include <Windows.h>
#include <iostream>
#include <ctime>

#define SECOND 10000000  

using namespace std;

int main() {
    long long it1 = -60 * SECOND;  
    long long it2 = -120 * SECOND;

    HANDLE hTimer1 = CreateWaitableTimer(NULL, FALSE, L"vladTimer1");
    if (!hTimer1) {
        cerr << "Failed to create Timer1.\n";
        return 1;
    }

    if (!SetWaitableTimer(hTimer1, (LARGE_INTEGER*)&it1, 0, NULL, NULL, FALSE)) {
        cerr << "Failed to set Timer1.\n";
        return 1;
    }

    HANDLE hTimer2 = CreateWaitableTimer(NULL, FALSE, L"vladTimer2");
    if (!hTimer2) {
        cerr << "Failed to create Timer2.\n";
        return 1;
    }

    if (!SetWaitableTimer(hTimer2, (LARGE_INTEGER*)&it2, 0, NULL, NULL, FALSE)) {
        cerr << "Failed to set Timer2.\n";
        return 1;
    }

    LPCWSTR applicationName1 = L"C:\\Users\\Влад\\Desktop\\Процессы\\OS07_04_X.exe";
    LPCWSTR applicationName2 = L"C:\\Users\\Влад\\Desktop\\Процессы\\OS07_04_X2.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (CreateProcess(applicationName1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1)) {
        cout << "[1] OS07_04_X - Created\n";
    }
    else {
        cerr << "[1] OS07_04_X - Not Created\n";
        return 1;
    }

    if (CreateProcess(applicationName2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2)) {
        cout << "[2] OS07_04_X - Created\n";
    }
    else {
        cerr << "[2] OS07_04_X - Not Created\n";
        return 1;
    }

    WaitForSingleObject(hTimer1, INFINITE);
    cout << "[Timer1] 1 minute out\n";
    TerminateProcess(pi1.hProcess, 0); 
    CloseHandle(hTimer1);

    WaitForSingleObject(pi1.hProcess, INFINITE);
    cout << "[Process 1] Finished\n";

    WaitForSingleObject(hTimer2, INFINITE);
    cout << "[Timer2] 2 minutes out\n";
    TerminateProcess(pi2.hProcess, 0); 
    CloseHandle(hTimer2);

    WaitForSingleObject(pi2.hProcess, INFINITE);
    cout << "[Process 2] Finished\n";

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    cout << "Main process completed.\n";
    system("pause");
    return 0;
}
