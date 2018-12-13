#include <iostream> 
#include <windows.h>
using namespace std;
enum class Color
{
	BLACK = 0,
	WHITE = 1
};
struct Cell
{
	int x;
	int y;
	Color color;
};
class Desk
{
private:
	HWND m_ConsoleWindow;
	HDC m_hDC;
	int m_width;
	int m_height;
	int m_leftX;
	int m_leftY;
	int m_cellSize;
	Cell** m_cellArray;
public:
	Desk() :
		m_ConsoleWindow(GetConsoleWindow()),
		m_hDC(GetDC(m_ConsoleWindow)),
		m_width(8),
		m_height(8),
		m_leftX(15),
		m_leftY(15),
		m_cellArray(0),
		m_cellSize(50)
	{
		m_cellArray = new Cell*[m_height];
		for (int i = 0; i < m_width; i++)
			m_cellArray[i] = new Cell;

	}
	~Desk()
	{
		for (int i = 0; i < m_width; i++)
			delete[] m_cellArray[i];
		delete[] m_cellArray;
	}

	void showDesk()
	{
		for (int i = 0; i < m_height; i++)
		{
			for (int q = 0; q < m_width; q++)
			{
				if ((q + i) % 2 == 0)
					SelectObject(m_hDC, CreateSolidBrush(RGB(255, 255, 255)));
				else
					SelectObject(m_hDC, CreateSolidBrush(RGB(0, 0, 0)));
				Rectangle(m_hDC, m_leftX + q * m_cellSize, m_leftY + i * m_cellSize, m_leftX + q * m_cellSize + m_cellSize, m_leftY + i * m_cellSize + m_cellSize);
				// написал struct Cell и enum Color для расширяемости, но я их вообще не использовал по сути) 
			}
		}

	}
};
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
// устанавливает цвет текста и подложки в консоли
void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

// устанавливает цвет текста и подложки в консоли 
void SetColor(int text, ConsoleColor/*int*/ background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int main()
{
	SetColor(15, Red);
	Desk hello;
	hello.showDesk();
	system("pause");
}



