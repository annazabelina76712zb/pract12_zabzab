#include <iostream>
#include <windows.h>

using namespace std;

void SetProcessPriority(int choice) {
    HANDLE hProcess = GetCurrentProcess();

    switch (choice) {
    case 1: 
        SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS);
        cout << "Установлен приоритет: Фоновый (низкий)" << endl;
        break;
    case 2: 
        SetPriorityClass(hProcess, BELOW_NORMAL_PRIORITY_CLASS);
        cout << "Установлен приоритет: Ниже среднего" << endl;
        break;
    case 3: 
        SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
        cout << "Установлен приоритет: Нормальный" << endl;
        break;
    case 4: 
        SetPriorityClass(hProcess, ABOVE_NORMAL_PRIORITY_CLASS);
        cout << "Установлен приоритет: Выше среднего" << endl;
        break;
    case 5: 
        SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
        cout << "Установлен приоритет: Высокий" << endl;
        break;
    default:
        SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
        cout << "Установлен приоритет: Нормальный (по умолчанию)" << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "КЛИЕНТ" << endl << endl;
    cout << "Выберите приоритет процесса:" << endl;
    cout << "1 - Фоновый (низкий)" << endl;
    cout << "2 - Ниже среднего" << endl;
    cout << "3 - Нормальный" << endl;
    cout << "4 - Выше среднего" << endl;
    cout << "5 - Высокий" << endl;


    int priorityChoice;
    cin >> priorityChoice;
    cin.ignore(); 
    SetProcessPriority(priorityChoice);

    cout << endl << "Клиент запущен!" << endl << endl;

    const char* mName = "Printer";
    HANDLE hMut = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, mName);
    if (hMut == NULL) {
        cout << "Ошибка открытия мьютекса! Принтер не найден." << endl;
        cout << "Убедитесь, что процесс 'Принтер' запущен." << endl;
        return GetLastError();
    }

    cout << "Принтер найден!" << endl;
    cout << "Нажмите Enter для отправки задания на печать..." << endl;
    cin.get();

    cout << "Пытаемся захватить принтер..." << endl;
    WaitForSingleObject(hMut, INFINITE);
    cout << "Отправлено на печать!" << endl;
    ReleaseMutex(hMut);

    cout << "Ожидание завершения печати!" << endl;
    WaitForSingleObject(hMut, INFINITE);
    cout << "Печать завершена!" << endl;
    ReleaseMutex(hMut);

    CloseHandle(hMut);

    cout << endl << "Нажмите Enter для выхода...";
    cin.get();
    return 0;
}