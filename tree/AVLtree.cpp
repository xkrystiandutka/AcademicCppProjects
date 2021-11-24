#include <iostream>
using namespace std;

struct wezelAVL {
	int klucz; int h;
	wezelAVL* lewe; wezelAVL* prawe; wezelAVL* rodzic;
}; //pojedynczy węzeł
wezelAVL* drzewoAVL = NULL; //wskaźnik do drzewa (globalny lub lokalny)

int h = 0;
int wysokosc(wezelAVL* w)
{
	if (w != NULL)
	{
		int x = wysokosc(w->lewe);
		int y = wysokosc(w->prawe);
		if (x > y) h = x + 1; else h = y + 1;
	}
	else h = 0;
	return h;
}

wezelAVL* obrotLewo(wezelAVL* w)
{
	wezelAVL* wzr = w->prawe;
	wzr->rodzic = w->rodzic;
	w->rodzic = wzr;
	w->prawe = wzr->lewe;
	if (wzr->lewe != NULL) wzr->lewe->rodzic = wzr;
	wzr->lewe = w;
	w->h = max(wysokosc(w->lewe), wysokosc(w->prawe)) + 1;
	wzr->h = max(wysokosc(wzr->lewe), wysokosc(wzr->prawe)) + 1;
	return wzr;
}

wezelAVL* obrotPrawo(wezelAVL* w)
{
	wezelAVL* wzr = w->lewe;
	wzr->rodzic = w->rodzic;
	w->rodzic = wzr;
	w->lewe = wzr->prawe;
	if (wzr->prawe != NULL) wzr->prawe->rodzic = wzr;
	wzr->prawe = w;
	w->h = max(wysokosc(w->lewe), wysokosc(w->prawe)) + 1;
	wzr->h = max(wysokosc(wzr->lewe), wysokosc(wzr->prawe)) + 1;
	return wzr;
}

void balans_AVL(wezelAVL*& w)
{
	int balans = wysokosc(w->lewe) - wysokosc(w->prawe);
	if (balans == 2) // lewe poddrzewo sprawdzanego węzła cięższe
	{
		int balansL = wysokosc(w->lewe->lewe) - wysokosc(w->lewe->prawe);
		if (balansL == -1) { w->lewe = obrotLewo(w->lewe); w = obrotPrawo(w); }
		else w = obrotPrawo(w); // bez dodatkowego obrotu
	}
	else if (balans == -2) // prawe poddrzewo sprawdzanego węzła cięższe
	{
		int balansP = wysokosc(w->prawe->lewe) - wysokosc(w->prawe->prawe);
		if (balansP == 1) { w->prawe = obrotPrawo(w->prawe); w = obrotLewo(w); }
		else w = obrotLewo(w); // bez dodatkowego obrotu
	}
	w->h = max(wysokosc(w->lewe), wysokosc(w->prawe)) + 1; //aktualizacja wysokości
}

wezelAVL* insert_AVL(int x, wezelAVL*& w)
{
	if (w == NULL)
	{
		w = new wezelAVL;
		w->klucz = x;
		w->lewe = NULL;
		w->prawe = NULL;
		w->rodzic = NULL;
		w->h = 0;
	}
	else if (x < w->klucz) { w->lewe = insert_AVL(x, w->lewe); w->lewe->rodzic = w; }
	else { w->prawe = insert_AVL(x, w->prawe); w->prawe->rodzic = w; }
	balans_AVL(w);
	w->h = max(wysokosc(w->lewe), wysokosc(w->prawe)) + 1;
	return w;
}

void wyswietl_drzewo(wezelAVL* w, int h = 0)
{
	if (w != NULL)
	{
		wyswietl_drzewo(w->prawe, h + 1);
		for (int i = 1; i <= h; i++) cout << " ";
		cout << w->klucz << "\n";
		wyswietl_drzewo(w->lewe, h + 1);
	}
}

void built_AVL(int n, wezelAVL*& w)
{
	for (int i = 1; i <= n; i++)
	{
		cout << "wpisz wartosc: "; int x; cin >> x;
		insert_AVL(x, w);
		wyswietl_drzewo(w);
	}
}

void wyszukaj(wezelAVL*& w, int key) {
	if (w == NULL)
		cout << NULL << endl;
	else if (w->klucz == key)
		cout << "\n Podany klucz znajduje sie w drzewie AVL: " << w->klucz << endl;
	else if (w->klucz < key)
		wyszukaj(w->prawe, key);
	else
		wyszukaj(w->lewe, key);

}


int main()
{
	
	built_AVL(5, drzewoAVL);
	int x;
	cout << "Podaj szukany klucz:";
	cin >> x;
	wyszukaj(drzewoAVL, x);
	//	wyswietl_drzewo(drzewoAVL); //wywołanie funkcji


}
