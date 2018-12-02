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
		m_cellArray(nullptr),
		m_cellSize(30)
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
					SelectObject(m_hDC, CreateSolidBrush(RGB(77, 75, 34)));
				else
					SelectObject(m_hDC, CreateSolidBrush(RGB(81, 13, 22)));
				Rectangle(m_hDC, m_leftX + q * m_cellSize, m_leftY + i * m_cellSize, m_leftX + q * m_cellSize + m_cellSize, m_leftY + i * m_cellSize + m_cellSize);
				// написал struct Cell и enum Color для расширяемости, но я их вообще не использовал по сути) 
			}
		}

	}
};
int main()
{
	Desk hello;
	hello.showDesk();
	system("pause");
}
