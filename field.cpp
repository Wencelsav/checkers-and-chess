#include <iostream>
#include <windows.h>

using namespace std;

int main(void)
{
	int a[8][8];
	//ввод матрицы
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			a[i][j] = 0;
			int n = i + j;
			if (n % 2 == 0) {
				SetConsoleTextAttribute(console, BACKGROUND_BLUE); //печатаем зеленым
				cout << a[i][j];
				SetConsoleTextAttribute(console, BACKGROUND_GREEN); //печатаем белым
			}
			cout << a[i][j];
		}
		
	}
	system("pause");
	return 0;
}
