#include <iostream>
using namespace std;

struct wezel {
	int klucz;
	wezel* lewe;
	wezel* prawe;
}; //pojedynczy węzeł

void insert_BST(int x, wezel*& w)
{
	if (w == NULL)
	{
		w = new wezel; w->klucz = x;
		w->lewe = NULL; w->prawe = NULL;
	}
	else if (x < w->klucz)
		insert_BST(x, w->lewe);
	else insert_BST(x, w->prawe);
}

void built_BST(int n, wezel*& w)
{
	for (int i = 1; i <= n; i++)
	{
		cout << "wpisz wartosc:";
		int x; cin >> x;
		insert_BST(x, w);
	}
}

void wyswietl_drzewo(wezel* w, int h = 0)
{
	if (w != NULL)
	{
		wyswietl_drzewo(w->prawe, h + 1);
		for (int i = 1; i <= h; i++) cout << " ";
		cout << w->klucz << "\n";
		wyswietl_drzewo(w->lewe, h + 1);
	}
	//	else cout << "\n drzewo jest puste!";
}

void wyszukaj(wezel* w, int key)
{
	if (w == NULL)
		cout << NULL << endl;
	else if (w->klucz == key)
		cout << "\n Podany klucz znajduje sie w drzewie: " << w->klucz << endl;
	else if (w->klucz < key)
		wyszukaj(w->prawe, key);
	else
		wyszukaj(w->lewe, key);
}

int minValue(wezel* w) {
	wezel* min = w;
	while (min->lewe != NULL) {
		min = min->lewe;
	}
	return(min->klucz);
}


int main()
{
	wezel* drzewo = NULL; //wskaźnik do drzewa
		int n = 5, x;
		built_BST(n, drzewo);
		wyswietl_drzewo(drzewo);

		cout << "Najmniejsza wartosc : " << minValue(drzewo);
	}
