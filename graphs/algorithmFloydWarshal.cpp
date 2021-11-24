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
void floyd_warshall(int** g, int** r, int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (g[i][k] + g[k][j] < g[i][j])//jeżeli nie ma poł.->g=10000 wiec nie spełni nierowności
				{
					g[i][j] = g[i][k] + g[k][j]; //jeżeli nierow. prawdziwa nowy koszt poł. = sumie kosztów
					r[i][j] = r[k][j];
				}
			}
}
int minR(int v[], int c[])
{
	int nMin = 0;
	int vMin = 10000;
	for (int i = 0; i < n; i++)

	{
		if (v[i] < vMin && c[i] == 0)
		{
			nMin = i; vMin = v[i];
		}
	}
	return nMin;
}
void dijkstra(int** G, int n, int s)
{
	int v, u;
	for (v = 0; v < n; v++)
	{
		c[v] = 0; //tab. spr. węzłów, 0=niespr, 1=sprawdzony
		d[v] = G[s][v]; //wektor kosztów najkrótszych ścieżek od s do v
		optPoprz[v] = -1; //wektor poprzedników węzłow v, potrzebny do odtworzenia drogi
	}
	for (int i = 0; i < n; i++)
	{
		u = minR(d, c); //wybór wierzchołka o najmn. wadze krawędzi spośród niespr. (r[v]=1)
		c[u] = 1; //wierzchołek wyłączony z dostępnych, nie będzie już spr.
		for (v = 0; v < n; v++) //dla każdego węzła
		{
			if (c[v] == 0) //jeżeli nie był jeszcze spr., nie ma opt. najkr. drogi
			{
				if (d[u] + G[u][v] < d[v]) //szukanie krótszej drogi
				{
					d[v] = d[u] + G[u][v];
					optPoprz[v] = u; //zapis poprzednika w najkrótszej ścieżce
				}
			}
		}
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
	//---------------------------------------------------
	cout << "\n\n alg. Floyda-Warshalla - wyzn. drogi opt. pod wzgl. kosztow" << endl;
	int** k = Graf(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			k[i][j] = 10000;
	//koszty krawedzi:
	k[0][3] = 12;
	k[0][2] = 16;
	k[1][0] = 8;
	k[1][2] = 28;
	k[1][4] = 35;
	k[2][4] = 5;
	k[3][1] = 22;
	k[3][5] = 18;
	k[4][5] = 40;
	k[5][1] = 10;

	WyswietlGraf(k, n, 6); cout << "\n";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (k[i][j] != 10000) r[i][j] = i;
			else r[i][j] = -1;
	floyd_warshall(k, r, n);
	cout << "\n tab kosztow po alg. F-W \n"; WyswietlGraf(k, n, 6);
	cout << "\n\n macierz polaczen po alg. F-W \n"; WyswietlGraf(r, n, 3); cout << "\n\n";
}