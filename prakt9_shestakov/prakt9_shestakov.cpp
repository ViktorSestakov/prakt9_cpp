#include <iostream>
#include <windows.h>

using namespace std;

STARTUPINFO si;
PROCESS_INFORMATION pi = { 0 };

DWORD WINAPI start_count(LPVOID lpParam) {
	int count = 0;

	while (true) {
		count++;

		cout << "Таймер: " << count << endl;
		cout << endl;
		cout << "1 - Word, 6 - Закрыть Word" << endl;
		cout << "2 - Excel, 7 - Закрыть Excel" << endl;
		cout << "3 - Paint, 8 - Закрыть Paint" << endl;
		cout << "4 - Notepad, 9 - Закрыть Notepad" << endl;
		cout << "5 - Закрыть все процессы" << endl;
		cout << "Выберите пункт: ";

		Sleep(1000);
		system("cls");
	}
}

HANDLE cThread;
int openChildProc = 0; // счетчик на проверку открыто ли дочернее окно или нет
void start_process (const wchar_t* prog) {
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	HANDLE hThread = NULL;
	if (openChildProc == 0) {
		cThread = CreateThread(NULL, 0, start_count, NULL, 0, NULL);
		if (cThread == NULL) {
			cout << "Ошибка создания потока-счетчика" << endl;
		}

		if (!DuplicateHandle(GetCurrentProcess(), cThread, GetCurrentProcess(), &hThread, 0, TRUE, THREAD_SUSPEND_RESUME | THREAD_TERMINATE)) {
			cout << "Ошибка дублирования дескриптора" << GetLastError() << endl;
		}

		wchar_t child[100] = L"C:\\Users\\st310-06\\Desktop\\shsetakov\\sys\\practt9_cpp\\x64\\Debug\\Child.exe ";
		wchar_t temp[20];
		_itow_s((int)hThread, temp, 10);
		wcscat_s(child, temp);

		if (!CreateProcess(NULL, child, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			cout << "Не удалось запустить дочерний процесс!" << endl;
		}
	}

	wchar_t progs[256];
	wcscpy_s(progs, prog);

	if (!CreateProcess(NULL, progs, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		cout << "Процесс не создан" << endl;
	}

	CloseHandle(hThread);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	openChildProc = 1;
}

PROCESS_INFORMATION openW(wchar_t* prog) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	wchar_t progs[256];
	wcscpy_s(progs, prog);

	if (!CreateProcess(NULL, progs, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		cout << "Процесс не создан" << endl;
	}

	return pi;
}

int main()
{
	setlocale(LC_ALL, "Ru");

	int vibor = 0;

	cout << "1 - Word, 6 - Закрыть Word" << endl;
	cout << "2 - Excel, 7 - Закрыть Word" << endl;
	cout << "3 - Paint, 8 - Закрыть Word" << endl;
	cout << "4 - Notepad, 9 - Закрыть Word" << endl;
	cout << "5 - Закрыть все процессы" << endl;

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
			system("taskkill /F /IM Child.exe >nul 2>&1");

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			return 0;
			break;
		case 6:
			system("powershell -command \"Add-Type '[DllImport(\\\"user32.dll\\\")]public static extern int PostMessage(int hWnd,int Msg,int w,int l);' -Name W -Namespace X; $h=(Get-Process winword).MainWindowHandle|Where{$_ -ne 0}|Select -First 1; [X.W]::PostMessage($h,0x10,0,0)\"");

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			break;
		case 7:
			system("powershell -command \"Add-Type '[DllImport(\\\"user32.dll\\\")]public static extern int PostMessage(int hWnd,int Msg,int w,int l);' -Name W -Namespace X; $h=(Get-Process excel).MainWindowHandle|Where{$_ -ne 0}|Select -First 1; [X.W]::PostMessage($h,0x10,0,0)\"");

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			break;
		case 8:
			system("powershell \"Get-Process mspaint | Select-Object -First 1 | Stop-Process\"");

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			break;
		case 9:
			system("powershell \"Get-Process notepad | Select-Object -First 1 | Stop-Process\"");

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			break;
		default:
			cout << "НЕВЕРНЫЙ ВВОД!!!" << endl;
			break;
		}
	}
}
