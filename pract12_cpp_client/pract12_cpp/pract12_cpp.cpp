#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL)); 

    cout << "=== ПРИНТЕР ЗАПУЩЕН ===" << endl << endl;

    const char* mName = "Printer";
    HANDLE hMut = CreateMutexA(NULL, FALSE, mName);
    if (hMut == NULL) {
        cout << "Ошибка создания мьютекса!" << endl;
        return GetLastError();
    }

    DWORD lastConnect = GetTickCount64();

    while (true) {
        DWORD WaitMut = WaitForSingleObject(hMut, 1000);

        if (WaitMut == WAIT_OBJECT_0) {
            lastConnect = GetTickCount64();

            cout << "Идет печать!" << endl;

            int printTime = 5 + rand() % 11;

            Sleep(printTime * 1000);

            if (printTime > 10) {
                cout << "Ошибка печати!" << endl;
            }

            cout << "Готово!" << endl << endl;

            ReleaseMutex(hMut);
        }

        if (GetTickCount64() - lastConnect > 600000) {
            cout << "Принтер выключен. Простой больше 10 минут" << endl;
            break;
        }
    }

    CloseHandle(hMut);

    cout << "Нажмите Enter для выхода...";
    cin.get();
    return 0;
}