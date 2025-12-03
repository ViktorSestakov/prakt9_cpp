#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Ru");

	char vvod;
	HANDLE hThread = (HANDLE)(ULONG_PTR)_atoi64(argv[1]);

	while (true) {
		cout << "p - поставить таймер на паузу!" << endl;
		cout << "r - включить таймер обратно!" << endl;

		cout << "Введите букву: ";

		cin >> vvod;

		if (vvod == 'p' || vvod == 'P') {
			DWORD suspendCount = SuspendThread(hThread);
		}
		else if (vvod == 'r' || vvod == 'R') {
			DWORD suspendCount = ResumeThread(hThread);
		}

		system("cls");
	}
}