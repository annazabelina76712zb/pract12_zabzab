#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RU");
	cout << "Принтер ЗАПУЩЕН" << endl;
	srand(time(nullptr));
	
	HANDLE mutex = CreateMutex(NULL, FALSE, L"Global\\PrinterMutex");
	if (mutex == NULL)
	{
		cout << "Ошибка создания мютекса!" << endl;
		
	}

	DWORD clienttime = GetTickCount();
	bool isPrinting = false;

	cout << "Мютекс успешно создан!" << endl;
	DWORD currentTime = GetTickCount();
	while (true)
	{
		DWORD time10 = GetTickCount();
		if (!isPrinting && (time10 - currentTime) > 20000)
			cout << "Бездействие 10 минут. Отключение..." << endl;
		break;
	}
	DWORD result = WaitForSingleObject(mutex, 1000);
	switch (result)
	{
	case WAIT_OBJECT_0: cout << "ПЕЧАТЬ выполняется!" << endl;
		isPrinting= true;
		clienttime = GetTickCount();
		int printTime = 5 + rand() % 11;
		cout << printTime << " сек." << endl;

		for (int i = 1; i <= printTime; i++)
		{
			Sleep(1000);
			if (i > 10 && i <= printTime)
			{
				cout << "Ошибка печати!" << endl;
				break;
			}
			cout << "Печать..." << i << " сек." << endl;
		}
		ReleaseMutex(mutex);
		cout << "Готово!" << endl;
		isPrinting = false;
		break;
	/*case WAIT_ABANDONED: ReleaseMutex(mutex);
		break;
	default: cout << "Ошибка!" << endl;
		break;*/

	}
	CloseHandle(mutex);
	cout << "Печать завершена." <<endl;
}
