#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int n = 6;
int optPoprz[n], d[n], c[n];
void WczytajGraf(string nazwaPliku, int** g, int r)
{
	fstream plik(nazwaPliku.c_str());
	for (int i = 0; i < r; i++)
		for (int j = 0; j < r; j++)
			plik >> g[i][j];
}
void WyswietlGraf(int** g, int r, int p)
{
	for (int i = 0; i < r; i++)
	{
		cout << "\n";
		for (int j = 0; j < r; j++)
		{
			cout << setw(p) << g[i][j];
		}
	}
}
int** Graf(int r)
{
	int** g = new int* [r];
	for (int i = 0; i < r; i++)
		g[i] = new int[r];
	return g;
}
void droga_RW(int** R)
{
	for (int x = 0; x < n; x++)
		for (int y = 0; y < n; y++)
			if (R[y][x] != 0)
				for (int z = 0; z < n; z++)
					if (R[y][z] == 0 && R[x][z] != 0)
					{
						R[y][z] = R[y][x];
					}
}


int main()
{
	int** g = Graf(n);
	//-------------------------------------------------
	cout << "\n\n alg. zmodyfikowany R-W" << endl;
	WczytajGraf("g1_lab.txt", g, n);
	cout << "\n\n macierz grafu G: " << endl;
	WyswietlGraf(g, n, 3);
	int** r = Graf(n);
	for (int x = 0; x < n; x++) //macierz ruchu
		for (int y = 0; y < n; y++)
			if (g[x][y] == 0) r[x][y] = 0; else r[x][y] = y + 1; //y+1-> num. w tab od 0, wez. A=1
	cout << "\n\n macierz ruchu R: " << endl; WyswietlGraf(r, n, 3);
	droga_RW(r); //szukanie połaczen miedzy wezłami
	cout << "\n\n po wyzn. drogi: " << endl; WyswietlGraf(r, n, 3);
}