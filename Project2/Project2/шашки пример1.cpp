//figures.h- ��������� ������ ����������� �����
#ifndef figures_h
#define figures_h
//������� ����� ������
class TFigure
{
protected:
	int theCenterX, theCenterY;//����� ������        

public:
	TFigure(int tCenterX, int tCenterY);
	virtual void Show() = 0;//����������
};
#endif



//figures.cpp-���������� ������ ����������� �����
#include"figures.h"
#include<graphics.h>
TFigure::TFigure(int tCenterX, int tCenterY)
{
	theCenterX = tCenterX;
	theCenterY = tCenterY;
};



//draught.h - ��������� ������ ��������� ����
#ifndef   draught_h
#define   draught_h
#include "figures.h"
//��������� ���������� �������
const cFieldLength = 200;//����� ����
const cSquareNum = 32;//���������� ������ ������ �����
const cDraughtNum = 24;//���������� �����
const cSquareLength = 25;//����� ������
const cDraughtRadius = 23;//������ �����
const cKingRadius = 6;//���������� ������ �����
//��������� ��������������
const cCenterX = 50;
const cCenterY = 50;
enum TPlayer { PBlack, PWhite };
enum TEnter { one, two, three };
enum TDrState { stOnField, stOutField };
enum TDrKing { King, NKing };
enum TDrColor { Black, White };
enum TSqState { Empty, First, Second };
//��������� �������     
enum TEvConst { EvNothing, EvMoveUL, EvMoveDR, EvMoveUR, EvMoveDL, EvEnter, EvQuit, EvNew };

//����� �������
class TEvent
{
public:
	TEvConst What;
};

//����� �����
class TField;
class TDraught :public TFigure
{
	friend class TField;

	TDrState theState;//��������� �����
	TDrColor theColor;//���� �����
	TDrKing theKing;//���� ����� ��� ���

public:
	TDraught(int tCenterX, int tCenterY, TDrState tState, TDrColor tColor);
	virtual void Show();
};

//����� ������
class TSquare :public TFigure
{
	friend class TField;

	TSqState theSqState;//��������� ������

public:
	TSquare(int tCenterX, int tCenterY, TSqState tSqState);
	virtual void Show();
};

//����� ������
class TCursor :public TFigure
{
public:
	TCursor(int tCenterX, int tCenterY);
	virtual void Show();
	float GetCenterX();
	float GetCenterY();
	void Move(int DeltaX, int DeltaY);
};

//����� ����
class TField
{
	TSquare *PSquare[32];
	TDraught *PDraught[24];
	TCursor *PCursor;

public:
	TPlayer thePlayer;//����� ������
	TEnter theEnter;//����������, ����� ��� ���� ������ ������ ������
	TField();
	void Delete();
	void HandleEvent(TEvent *anEvent);
	void Initiate();
	void Start();
	int Enter1();
	int Enter2(int t);
	void Enter3(int t1);
	void UpDate(int d, int s);
	int Find(int X, int Y, int P);
	void Eat(int i1, int i2, int i3);
	~TField();
};

//����� ������������ ����������
class TReality
{
	TField *PTheField;

public:
	TReality();
	void Run();
	~TReality();
};
#endif



// draught.cpp -���������� ������ ��������� ���� 
#include "figures.h"
#include "draught.h"
#include <graphics.h>
#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>

//���������� ������ �����       
TDraught::TDraught(int tCenterX, int tCenterY, TDrState tState,
	TDrColor tColor)
	:TFigure(tCenterX, tCenterY)
{
	theState = tState;
	theColor = tColor;
};

void TDraught::Show()
{
	int real_col;
	if (theColor == Black) { real_col = BLUE; }
	else { real_col = GREEN; }
	setfillstyle(SOLID_FILL, real_col);
	fillellipse(theCenterX, theCenterY, cDraughtRadius, cDraughtRadius);
	if (theKing == King) circle(theCenterX, theCenterY, cKingRadius);
};


//���������� ������ ������
TSquare::TSquare(int tCenterX, int tCenterY, TSqState tSqState)
	:TFigure(tCenterX, tCenterY)
{
	theSqState = tSqState;
};

void TSquare::Show()
{
	setfillstyle(SOLID_FILL, WHITE);
	bar(theCenterX - cSquareLength, theCenterY - cSquareLength,
		theCenterX + cSquareLength, theCenterY + cSquareLength);
};

//���������� ������ ������  
TCursor::TCursor(int tCenterX, int tCenterY)
	:TFigure(tCenterX, tCenterY)
{
	;
};

void TCursor::Show()
{
	int poly[6];
	poly[0] = theCenterX;
	poly[1] = theCenterY;
	poly[2] = theCenterX + 10;
	poly[3] = theCenterY;
	poly[4] = theCenterX;
	poly[5] = theCenterY + 10;
	setfillstyle(SOLID_FILL, MAGENTA);
	fillpoly(3, poly);
};

float TCursor::GetCenterX()
{
	return(theCenterX);
}

float TCursor::GetCenterY()
{
	return(theCenterY);
}

void TCursor::Move(int DeltaX, int DeltaY)
{
	if ((theCenterX + DeltaX < 420) && (theCenterX + DeltaX > 20) &&
		(theCenterY + DeltaY < 420) && (theCenterY + DeltaY > 20))
	{
		theCenterX += DeltaX;
		theCenterY += DeltaY;
	}
	Show();
};

//���������� ������ ����
TField::TField()
{
	int i, j, z;
	div_t x, y;

	//��������� ��������� �������� � �������� �������, ����� � ������
	thePlayer = PBlack;
	theEnter = one;
	PCursor = new TCursor(cCenterX, cCenterY);

	//������
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
		{
			x = div(i, 2), y = div(j, 2);
			if (x.rem == 0 && y.rem == 0)
			{
				z = (j + 8 * i) / 2;
				PSquare[z] = new TSquare((i + 1)*cCenterX, (j + 1)*cCenterY, Empty);
			}
			if (x.rem == 1 && y.rem == 1)
			{
				z = (8 * i + j - 1) / 2;
				PSquare[z] = new TSquare((i + 1)*cCenterX, (j + 1)*cCenterY, Empty);
			}
		}
	for (i = 0; i < 12; i++)
	{
		PSquare[i]->theSqState = First;
	}
	for (i = 32; i > 19; i--)
	{
		PSquare[i]->theSqState = Second;
	}

	//�����
	for (i = 0; i < 12; i++)
	{
		PDraught[i] = new TDraught(PSquare[i]->theCenterX,
			PSquare[i]->theCenterY, stOnField, Black);
		PDraught[i]->theKing = NKing;
	}
	for (i = 12; i < 24; i++)
	{
		PDraught[i] = new TDraught(PSquare[i + 8]->theCenterX,
			PSquare[i + 8]->theCenterY, stOnField, White);
		PDraught[i]->theKing = NKing;
	}

	Initiate();
};

//���������� ��� �� ������
void TField::Initiate()
{
	int i, prev_col = getcolor();
	//���������� ������ � �����
	window(61, 5, 80, 25);
	clearviewport();
	gotoxy(1, 1);
	setcolor(WHITE);
	//settextstyle(GOTHIC_FONT,HORIZ_DIR,2);
	//outtextxy(470,15,"DRAUGHTS");
	printf("������� ����:\n\t\t\t\t\t\t\t");
	printf(" ������� ����� �����,\n\t\t\t\t\t\t\t");
	printf("����� �������\n\t\t\t\t\t\t\t");
	printf("� ��� ���������.\n\n\t\t\t\t\t\t\t");
	printf("  ������� ����������:\n\t\t\t\t\t\t\t");
	printf("7 - ����� � �����;\n\t\t\t\t\t\t\t");
	printf("9 - ����� � ������;\n\t\t\t\t\t\t\t");
	printf("1 - ���� � �����;\n\t\t\t\t\t\t\t");
	printf("3 - ���� � ������;\n\t\t\t\t\t\t\t");
	printf("5 - ����;\n\t\t\t\t\t\t\t");
	printf("N - ����� ����;\n\t\t\t\t\t\t\t");
	printf("Q - �����.\n\n\t\t\t\t\t\t\t");
	rectangle(20, 20, 430, 430);
	rectangle(440, 50, 620, 280);
	rectangle(445, 55, 615, 275);
	setcolor(prev_col);
	window(1, 1, 80, 25);
	printf("           12                             12");
	for (i = 0; i < cSquareNum; i++) PSquare[i]->Show();
	for (i = 0; i < cDraughtNum; i++) PDraught[i]->Show();
	PCursor->Show();
};

//������� �� ������� �����������
int temp, temp1;
void TField::HandleEvent(TEvent *anEvent)
{
	switch (anEvent->What)
	{
		int s, d;
	case EvEnter: if (theEnter == one) temp = Enter1();
				  else if (theEnter == two) temp1 = Enter2(temp);
				  else if (theEnter == three) Enter3(temp1);
		PCursor->Show();
		anEvent->What = EvNothing; break;
	case EvMoveUR:s = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 1);
		d = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 2);
		PCursor->Move(50, -50);
		UpDate(d, s);
		anEvent->What = EvNothing; break;
	case EvMoveDL:s = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 1);
		d = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 2);
		PCursor->Move(-50, 50);
		UpDate(d, s);
		anEvent->What = EvNothing; break;
	case EvMoveUL:s = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 1);
		d = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 2);
		PCursor->Move(-50, -50);
		UpDate(d, s);
		anEvent->What = EvNothing; break;
	case EvMoveDR:s = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 1);
		d = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 2);
		PCursor->Move(50, 50);
		UpDate(d, s);
		anEvent->What = EvNothing; break;
	case EvNew:int g = 0, b = 0;
		for (int i = 0; i < cDraughtNum; i++)
		{
			if ((PDraught[i]->theColor == Black)
				&& (PDraught[i]->theState == stOnField))b++;
			if ((PDraught[i]->theColor == White)
				&& (PDraught[i]->theState == stOnField))g++;
		}
		if (g > b) {
			window(55, 20, 80, 25); printf("������� ��������!!!");
			window(55, 22, 80, 25);
			printf(" ������� ����� �������...");
		}
		if (g < b) {
			window(55, 20, 80, 25); printf("����� ��������!!!");
			window(55, 22, 80, 25);
			printf(" ������� ����� �������...");
		}
		if (g == b) {
			window(55, 20, 80, 25); printf("�����!!!");
			window(55, 22, 80, 25);
			printf(" ������� ����� �������...");
		}
		getch();
		Delete();
		TField();
		break;
	};
};

//����������� ����, ��� ���� ������������
void TField::UpDate(int d, int s)
{
	PSquare[s]->Show();
	if (PDraught[d]->theState == stOnField)PDraught[d]->Show();
	PCursor->Show();
};

//���������� ������� �����������
void TField::Start()
{
	TEvent theEvent;
	theEvent.What = EvNothing;
	do
	{
		if (kbhit())
		{
			char ch = getch(); strupr(&ch);
			switch (ch)
			{
			case 'N': theEvent.What = EvNew; break;
			case 'Q': theEvent.What = EvQuit; break;
			case '9': theEvent.What = EvMoveUR; break;
			case '7': theEvent.What = EvMoveUL; break;
			case '3': theEvent.What = EvMoveDR; break;
			case '1': theEvent.What = EvMoveDL; break;
			case '5': theEvent.What = EvEnter; break;
			};
		}
		HandleEvent(&theEvent);
	} while (theEvent.What != EvQuit);
};

//����� ����� �� �����������
int TField::Find(int X, int Y, int P)
{
	int i, m;
	//���� �=1, �� ���� ����� ������
	if (P == 1)
		for (i = 0; i < cSquareNum; i++)
		{
			if ((X == PSquare[i]->theCenterX) && (Y == PSquare[i]->theCenterY))
			{
				m = i; break;
			}
		}
	//���� �=2, �� ���� ����� �����
	if (P == 2)
	{
		for (i = 0; i < cDraughtNum; i++)
		{
			if ((X == PDraught[i]->theCenterX) && (Y == PDraught[i]->theCenterY)
				&& (PDraught[i]->theState == stOnField))
			{
				m = i; break;
			}
		}
	}
	return m;
};

//"��������"
void TField::Eat(int i1, int i2, int i3)
{
	int m;
	//����� ������, �� ������� ����� ��������� �����
	int t = Find(PDraught[i1]->theCenterX, PDraught[i1]->theCenterY, 1);
	PSquare[t]->theSqState = Empty;
	PSquare[t]->Show();
	//���������� ��������� �����
	PDraught[i1]->theCenterX = PSquare[i2]->theCenterX;
	PDraught[i1]->theCenterY = PSquare[i2]->theCenterY;
	PDraught[i1]->Show();
	//������, �� ������� ���� ��������� �����
	if (PDraught[i1]->theColor == Black)PSquare[i2]->theSqState = First;
	if (PDraught[i1]->theColor == White)PSquare[i2]->theSqState = Second;
	//����� ��������� �����
	m = Find(PSquare[i3]->theCenterX, PSquare[i3]->theCenterY, 2);
	PDraught[m]->theState = stOutField;
	PSquare[i3]->Show();
	PSquare[i3]->theSqState = Empty;
	//�������� �� ����� ����
	int b = 0, g = 0;
	for (int i = 0; i < cDraughtNum; i++)
	{
		if ((PDraught[i]->theColor == Black)
			&& (PDraught[i]->theState == stOnField))b++;
		if ((PDraught[i]->theColor == White)
			&& (PDraught[i]->theState == stOnField))g++;
	}
	if (g == 0) {
		window(55, 20, 80, 25); printf("����� ����!!!");
		window(55, 22, 80, 25);
		printf("�������� �����!!!"); window(1, 1, 80, 25);
	}
	if (b == 0) {
		window(55, 20, 80, 25); printf("����� ����!!!");
		window(55, 22, 80, 25);
		printf("�������� �������!!!"); window(1, 1, 80, 25);
	}
	//������� ������� ���������� ����� �����������
	gotoxy(1, 1);
	cout << "           " << b << "                             " << g << "   ";
};

//������� �� ������ �����
int TField::Enter1()
{
	int l = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 1);
	//�������� ����� ������� ������ 
	if (((PSquare[l]->theSqState == First) && (thePlayer == PBlack))
		|| ((PSquare[l]->theSqState == Second) && (thePlayer == PWhite)))
	{
		theEnter = two;
	}
	else if (((PSquare[l]->theSqState == First) && (thePlayer != PBlack))
		|| ((PSquare[l]->theSqState == Second) && (thePlayer != PWhite)))
	{
		window(57, 20, 80, 25); printf("��� ������� ������!");
		window(57, 22, 80, 25); printf("������� ����� �������..."); getch();
		window(57, 20, 80, 25); printf("                     ");
		window(57, 22, 80, 25); printf("                        "); window(1, 1, 80, 25);
	}
	else {
		window(57, 20, 80, 25); printf("�������� �����!");
		window(57, 22, 80, 25); printf("������� ����� �������..."); getch();
		window(57, 20, 80, 25); printf("                     ");
		window(57, 22, 80, 25); printf("                        "); window(1, 1, 80, 25);
	}
	return l;
};

//������� �� ������ �����
int TField::Enter2(int t)
{
	int m, i;
	int l = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 1);
	if (l == t)
	{
		m = Find(PSquare[l]->theCenterX, PSquare[l]->theCenterY, 2);
		theEnter = three;
	}
	else { theEnter = one; }
	return m;
};

//������� �� ������ ����� (����� ������ ��������)
void TField::Enter3(int t1)
{
	//����� ������, �� ������� ���������
	int l = Find(PCursor->GetCenterX(), PCursor->GetCenterY(), 1);
	//��� ������ ���� ������
	if (PSquare[l]->theSqState == Empty)
	{
		//���� ����������� ����� �����
		if (PDraught[t1]->theKing == King)
		{
			//����� ������, �� ������� ����� �����
			int t = Find(PDraught[t1]->theCenterX, PDraught[t1]->theCenterY, 1);
			//������������� ��� ������ ����� ������ � �������,  
			//�� ������� ��� ���������  
			int N = abs(PSquare[t]->theCenterX - PSquare[l]->theCenterX) / 2 / cSquareLength;
			int DeltaX = (PSquare[l]->theCenterX - PSquare[t]->theCenterX) / N;
			int DeltaY = (PSquare[l]->theCenterY - PSquare[t]->theCenterY) / N;
			int sum = 0, num;
			for (int i = 1; i < N; i++)
			{
				int sq = Find(PSquare[t]->theCenterX + DeltaX * i,
					PSquare[t]->theCenterY + DeltaY * i, 1);
				if (PSquare[sq]->theSqState != Empty) { sum++; num = sq; }
			}
			//����������� ���������� ����� �� ���� �����  
			if (sum > 1) {
				window(57, 20, 80, 25); printf("������������ ���!");
				window(57, 22, 80, 25); printf("������� ����� �������..."); getch();
				window(57, 20, 80, 25); printf("                     ");
				window(57, 22, 80, 25); printf("                                ");
				window(1, 1, 80, 25);
			}
			if (sum == 1)
			{
				if ((PDraught[t1]->theColor == Black) && (PSquare[num]->theSqState == Second))
					Eat(t1, l, num);
				if ((PDraught[t1]->theColor == White) && (PSquare[num]->theSqState == First))
					Eat(t1, l, num);
				if (thePlayer == PBlack)thePlayer = PWhite;
				else thePlayer = PBlack;
			}
			if (sum == 0)
			{
				PSquare[t]->theSqState = Empty;
				PDraught[t1]->theCenterX = PSquare[l]->theCenterX;
				PDraught[t1]->theCenterY = PSquare[l]->theCenterY;
				PSquare[t]->Show();
				if (PDraught[t1]->theColor == Black)PSquare[l]->theSqState = First;
				if (PDraught[t1]->theColor == White)PSquare[l]->theSqState = Second;
				if (thePlayer == PBlack)thePlayer = PWhite;
				else thePlayer = PBlack;
			}
		}
		//����� � �� �����
		else if (PDraught[t1]->theKing == NKing)
		{
			//������ ���  
			if (((PDraught[t1]->theColor == Black)
				&& (PSquare[l]->theCenterX - PDraught[t1]->theCenterX ==
					abs(PSquare[l]->theCenterY - PDraught[t1]->theCenterY))
				&& (PSquare[l]->theCenterX - PDraught[t1]->theCenterX == 2 * cSquareLength))
				|| ((PDraught[t1]->theColor == White)
					&& (-PSquare[l]->theCenterX + PDraught[t1]->theCenterX ==
						abs(PSquare[l]->theCenterY - PDraught[t1]->theCenterY))
					&& (abs(-PSquare[l]->theCenterX + PDraught[t1]->theCenterX) == 2 * cSquareLength)))
			{
				//����� ������, �� ������� ����  
				int t = Find(PDraught[t1]->theCenterX, PDraught[t1]->theCenterY, 1);
				PSquare[t]->theSqState = Empty;
				PDraught[t1]->theCenterX = PSquare[l]->theCenterX;
				PDraught[t1]->theCenterY = PSquare[l]->theCenterY;
				PSquare[t]->Show();
				if (PDraught[t1]->theColor == Black)PSquare[l]->theSqState = First;
				if (PDraught[t1]->theColor == White)PSquare[l]->theSqState = Second;
				//������ ������
				if (thePlayer == PBlack)thePlayer = PWhite;
				else thePlayer = PBlack;
			}
			//��������  
			else if ((abs(PSquare[l]->theCenterX - PDraught[t1]->theCenterX) == abs(PSquare[l]->theCenterY - PDraught[t1]->theCenterY))
				&& (abs(PSquare[l]->theCenterX - PDraught[t1]->theCenterX) == 4 * cSquareLength))
			{
				//����� ������, �� ������� ���� 
				int w = Find((PSquare[l]->theCenterX + PDraught[t1]->theCenterX) / 2, (PSquare[l]->theCenterY + PDraught[t1]->theCenterY) / 2, 1);
				if (PSquare[w]->theSqState != Empty)
				{
					if ((PDraught[t1]->theColor == Black) && (PSquare[w]->theSqState == Second))
						Eat(t1, l, w);
					if ((PDraught[t1]->theColor == White) && (PSquare[w]->theSqState == First))
						Eat(t1, l, w);
					if (thePlayer == PBlack)thePlayer = PWhite;
					else thePlayer = PBlack;
				}
				//���� ����� ������ �����   
				else {
					window(57, 20, 80, 25); printf("������������ ���!");
					window(57, 22, 80, 25); printf("������� ����� �������..."); getch();
					window(57, 20, 80, 25); printf("                     ");
					window(57, 22, 80, 25); printf("                        ");
					window(1, 1, 80, 25);
				}
			}
			//�� ��������, �� ���   
			else {
				window(57, 20, 80, 25); printf("������������ ���!");
				window(57, 22, 80, 25); printf("������� ����� �������..."); getch();
				window(57, 20, 80, 25); printf("                     ");
				window(57, 22, 80, 25); printf("                        "); window(1, 1, 80, 25);
			}
			//�� ����� �� ����� �� ��������������� �������
			if ((PDraught[t1]->theColor == Black) && ((l == 31) || (l == 30) || (l == 29)
				|| (l == 28)))
				PDraught[t1]->theKing = King;
			if ((PDraught[t1]->theColor == White) && ((l == 0) || (l == 1) || (l == 2)
				|| (l == 3)))
				PDraught[t1]->theKing = King;
		}
		theEnter = one;
		PDraught[t1]->Show();
	}
	//������ ��������� ��������
	else {
		window(57, 20, 80, 25); printf("��� ������ ��������!");
		window(57, 22, 80, 25); printf("������� ����� �������..."); getch();
		window(57, 20, 80, 25); printf("                     ");
		window(57, 22, 80, 25); printf("                        ");
		window(1, 1, 80, 25);
		theEnter = one;
	}
};

//�������� ���������� ��� New � ������
void TField::Delete()
{
	int i;
	for (i = 0; i < 32; i++)
	{
		delete PSquare[i];
	}
	for (i = 0; i < 24; i++)
	{
		delete PDraught[i];
	}
	delete PCursor;
};

TField::~TField()
{
	Delete();
};

//���������� ������ ������������ ����������
TReality::TReality()
{
	//���������� ����������� ����� ��� �������  
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "c:\\Borlandc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		cerr << "Graphics error"; exit(1);
	}
	setcolor(BLACK);
	//������� ��������� ������������ �����  
	PTheField = new TField;
};

void TReality::Run()
{
	PTheField->Start();
};

TReality::~TReality()
{
	delete PTheField;
	closegraph();
};



//main.cpp-�������� ��������� 
#include "game.h"
int main()
{
	TReality theReality;//������������� �����
	theReality.Run(); //�������� ��������
	return(0);
};



//������ "����������� ����� ��� ���� � �����".
//������� ��� ������������ ������������
//int TField::Eat(int i1, int i2, int i3)
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include"draught.h"

void OutputNumberTest(int Number)
{
	cout << "------- ���� � " << Number << endl;
}

//������������ ��������� �����������
//� ���������� ����������
void OutputResults(//��������� ��������
	int CenterX1, int CenterY1, //���������� ��������� �����
	TSqState Sq1,//��������� ������, �� ������� �������
	TSqState Sq2,//��������� ������ � ������� �����
	TSqState Sq3,//��������� ������ � ������� �������
	TDrState Dr,//��������� �����, ������� �������
	int theCenterX1, int theCenterY1, TSqState theSq1, TSqState theSq2, TSqState theSq3, TDrState theDr)//����������
{
	cout << "���������� �����:" << endl;
	cout << "���������� ����� �������:" << endl;
	if ((CenterX1 != theCenterX1) || (CenterY1 != theCenterY1))
		cout << "������ !";
	cout << " ���� " << theCenterX << "; ��������� " << CenterX << endl;
	cout << " ���� " << theCenterY << "; ��������� " << CenterY << endl;
	cout << "��������� ������, �� ������� �������:" << endl;
	if (Sq1 != theSq1)
		cout << "������ !";
	cout << " ���� " << theSq1 << "; ��������� " << Sq1 << endl;
	cout << "C�������� ������, � ������� �����:" << endl;
	if (Sq2 != theSq2)
		cout << "������ !";
	cout << " ���� " << theSq2 << "; ��������� " << Sq2 << endl;
	cout << "C�������� ������ � ������� �������:" << endl;
	if (Sq3 != theSq3)
		cout << "������ !";
	cout << " ���� " << theSq3 << "; ��������� " << Sq3 << endl;
	cout << "C�������� �����, ������� �������:" << endl;
	if (Dr != theDr)
		cout << "������ !";
	cout << " ���� " << theDr << "; ��������� " << Dr << endl;
}
//������������ ���������� ���������� �����
void Testing//��������� ���������� � ��������� ������ � �����
(int CenterX1, int CenterY1, TSqState Sq3,//�����, ������� ���
	TSqState Sq1,//����a,�� ������� ����
	TSqState Sq2, TDrState Dr,//����a,������ ����
	i1, i2, i3)
{
	Tfield *theField;
	TheField = new Tfield;
	//����� ������� ������ � �������
	cout << "������ ������:" << endl;
	cout << "���������� �����,���. �����:"
		<< PDraught[i1]->theCenterX << "," << PDraught[i1]->CenterY << endl;
	cout << "��������� ������,�� ���. ������:" << Psquare[i2] - theSqState << endl;
	cout << "C�������� ������,� ������� ������:" << Psquare[i3]->theSqState << endl;
	int m = Find(PDraught[i1] - theCenterX, PDraught[i1]->theCenterY, 1);
	cout << "C�������� ������,� ������� ������:" << Psquare[m]->theSqState << endl;
	m = Find(Psquare[i3] - theCenterX, Psquare[i3]->theCenterY, 2);
	cout << "C�������� �����,������� ������:" << PDraught[m]->theState << endl;
	Eat(i, i2, i3);
	OutputResults(int CenterX1, int CenterY1, TSqState Sq3, TSqState Sq1,
		TSqState Sq2, TDrState Dr, PDraught[i1]->theCenterX, PDraught[i1]->CenterY, Psquare[i2] - theSqState, Psquare[i3]->theSqState, Psquare[m]->theSqState, PDraught[m]->theState);
	Delete theField;
}
//�������� ��������� ��������
int main()
{ //���������
	cout << "������������ ������������" << endl;
	cout <<
		"void TField::Eat(int i1, int i1, int i3)" << endl << endl;
	// ���������� ����������� ����� ��� �������
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\Langs\\bc\\bgi");
	//���������� ������
	//���� 1
	OutputNumberTest(1);
	Testing(250, 150, Empty, First, Empty, stOutField, 11, 18, 14);
	getch();
	//���� 2
	OutputNumberTest(2);
	Testing(250, 150, Empty, Second, Empty, stOutField, 11, 18, 14);
	getch();
	closegraph();
	return 0;
}