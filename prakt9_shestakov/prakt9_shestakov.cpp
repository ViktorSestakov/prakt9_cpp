#include <iostream>
#include <windows.h>

using namespace std;

STARTUPINFO si;
PROCESS_INFORMATION piApp = {0};

DWORD WINAPI start_count(LPVOID lpParam) {
	int count = 0;

	while (true) {
		count++;

		cout << "Таймер: " << count << endl;
		cout << endl;
		cout << "1. Word" << endl;
		cout << "2. Excel" << endl;
		cout << "3. Paint" << endl;
		cout << "4. Notepad" << endl;
		cout << "5. Закрыть все процессы" << endl;
		cout << "6. Выйти" << endl;
		cout << "Выберите пункт: ";

		Sleep(1000);
		system("cls");
	}
}

int openChildProc = 0; // счетчик на проверку открыто ли дочернее окно или нет
void start_process(const wchar_t* prog) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi = { 0 };

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	HANDLE hThread = NULL;
	if (openChildProc == 0) {
		HANDLE cThread = CreateThread(NULL, 0, start_count, NULL, 0, NULL);
		if (cThread == NULL) {
			cout << "Ошибка создания потока-счетчика: " << endl;
		}

		if (!DuplicateHandle(GetCurrentProcess(), cThread, GetCurrentProcess(), &hThread, 0, TRUE, THREAD_SUSPEND_RESUME | THREAD_TERMINATE)) {
			cout << "Ошибка дублирования дескриптора: " << GetLastError() << endl;
		}

		wchar_t dotch[100] = L"C:\\Users\\viktor\\Desktop\\системные\\prakt9_shestakov\\x64\\Debug\\ChildProcess.exe ";
		wchar_t temp[20];
		_itow_s((int)hThread, temp, 10);
		wcscat_s(dotch, temp);
	
		if (!CreateProcess(NULL, dotch, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			cout << "Не удалось запустить дочерний процесс!" << endl;
			CloseHandle(hThread);
			TerminateThread(cThread, 0);
			CloseHandle(cThread);
		}
	}

	wchar_t progs[256];
	wcscpy_s(progs, prog);

	if (!CreateProcess(NULL, progs, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp)) {
		cout << "Процесс не создан" << endl;
	}

	CloseHandle(hThread);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	openChildProc = 1;
}

int main()
{
	setlocale(LC_ALL, "Ru");

	int vibor = 0;

	cout << "1. Word" << endl;
	cout << "2. Excel" << endl;
	cout << "3. Paint" << endl;
	cout << "4. Notepad" << endl;
	cout << "5. Закрыть все процессы" << endl;
	cout << "6. Выйти" << endl;

	cout << "Выберите пункт: ";

	while (true) {
		cin >> vibor;

		switch (vibor) {
		case 1:
			start_process(L"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.exe ");
			break;
		case 2:
			start_process(L"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.exe ");
			break;
		case 3:
			start_process(L"C:\\Windows\\system32\\mspaint.exe ");
			break;
		case 4:
			start_process(L"C:\\Windows\\System32\\notepad.exe ");
			break;
		case 5:
			system("taskkill /F /IM WINWORD.exe >nul 2>&1");
			system("taskkill /F /IM EXCEL.exe >nul 2>&1");
			system("taskkill /F /IM mspaint.exe >nul 2>&1");
			system("taskkill /F /IM notepad.exe >nul 2>&1");
			system("taskkill /F /IM ChildProcess.exe >nul 2>&1");
			break;
		case 6:
			system("taskkill /F /IM WINWORD.exe >nul 2>&1");
			system("taskkill /F /IM EXCEL.exe >nul 2>&1");
			system("taskkill /F /IM mspaint.exe >nul 2>&1");
			system("taskkill /F /IM notepad.exe >nul 2>&1");
			system("taskkill /F /IM ChildProcess.exe >nul 2>&1");
			return 0;
			break;
		}
	}
}