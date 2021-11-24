#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;

const int n = 12;
char lab[n][n];
int tabRuchow[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
int xStart, yStart, xKoniec, yKoniec;
bool czyKoniec = false;

void loadLabyrinth() {
	ifstream plik;
	plik.open("path.txt");
	if (!plik) {
		cerr << "\n nie udalo sie otworzyc pliku...";
		system("pause");
	}
	else {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				plik >> lab[i][j];
				if (lab[i][j] == '0') lab[i][j] = static_cast<char>(219);
				else lab[i][j] = ' ';
			}
	}
	plik.close();
}

void drawLabyrinth()
{
	system("cls");
	cout << "\n"; cout << "  ";
	for (int j = 0; j < n; j++) cout << j % 10;
	for (int i = 0; i < n; i++)
	{
		cout << "\n"; cout << i % 10 << " ";
		for (int j = 0; j < n; j++)
		{
			cout << lab[i][j];
		}
	}
}

void gotoxy(int x, int y) {
	COORD c;
	c.X = y;
	c.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void lookForWayOut(int w, int k) {
	int j = 0;
	int x, y;
	do {
		j++;
		x = w + tabRuchow[j - 1][0];
		y = k + tabRuchow[j - 1][1];
		if (x >= 0 && x < n && y >= 0 && y < n && (lab[x][y] == ' ' || lab[x][y] == 'k')) {
			lab[x][y] = 'o';
			gotoxy(x + 2, y + 2);
			cout << 'o';
			Sleep(500);
			if (x == xKoniec && y == yKoniec)
				czyKoniec = true;
			else {
				lookForWayOut(x, y);
			}
		}
	} while (czyKoniec == false && j < 4);
}

/*
szukaj_wyjścia(x,y)
powtarzaj
zwiększ nr_próby_ruchu
ustaw nowe współrzędne położenia ( kolejny możliwy ruch )
jeżeli ( wybrane_pole leży na planszy i (jest puste lub jest wyjściem) )
przejdź na wybrane_pole
jeżeli (współrzędne pola są równe współrzędnym wyjścia)
wyszukano drogę do wyjścia
w przeciwnym przypadku
szukaj_wyjścia(x,y)
dopóki(nie_wyszukano_wyjścia oraz nr_próby_ruchu < 4)
koniec
*/

int main()
{
	loadLabyrinth();
	drawLabyrinth();
	cout << "\n\n Podaj wspolrzedne x startu (0-11): "; cin >> xStart;
	cout << "\n\n Podaj wspolrzedne y startu (0-11): "; cin >> yStart;
	lab[xStart][yStart] = 's';
	{ gotoxy(xStart + 2, yStart + 2); cout << 's'; };
	{ gotoxy(18, 0); };
	cout << "\n\n Podaj wspolrzedne x wyjscia z labiryntu (0-11): "; cin >> xKoniec;
	cout << "\n\n Podaj wspolrzedne y wyjscia z labiryntu (0-11): "; cin >> yKoniec;
	lab[xKoniec][yKoniec] = 'k';
	{gotoxy(xKoniec + 2, yKoniec + 2); cout << 'k'; };
	gotoxy(23, 0); system("pause");
	lookForWayOut(xStart, yStart);
	gotoxy(25, 0);
	if (czyKoniec) {
		gotoxy(23, 0);
		cout << "\n\n wyznaczono droge przejscia! ";
	}
	else {
		gotoxy(20, 0);
		cout << "\n\n brak drogi!!!";
	}
	cout << "\n\n";
}

