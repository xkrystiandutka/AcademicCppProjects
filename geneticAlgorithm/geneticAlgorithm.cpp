#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;
const int maxpop = 100;
const int maxstring = 24;
typedef bool chromosom[maxstring];
struct Rozwiazanie
{
	bool chromosom[maxstring];
	float x, dopasowanie;
	int rodzic1, rodzic2, pRozciecia, pRozciecia1, pRozciecia2;
};
typedef Rozwiazanie populacja[maxpop];
populacja popStara, popNowa, popTymczasowa;
int rozmPop, dlugChrom, generacja, maxgen, genMax, genMin;
float pKrzyzowanie, pMutacja, sumaDopasowania;
float Avg, Max, Min, Max_a, Min_a, xExtrMin, xExtrMax, xExtrMin_a, xExtrMax_a; //_a -> globalne
float xmax; // maks dla przyjętej długości chromosomu do przeliczania na wart rzecz. xnMin..xnMax
int xnMin = -5, xnMax = 5; //rzeczywisty zakres szukania ekstremum
short typKrzyzowania, typMutacji, typSelekcji, typSukcesji, dod_czyn_los;
int n;
int* tabSumyCzesciowe;
int* tabRuletka;//=new int[n];
void fSort(populacja pop, int p, int k);
float Dekodowanie(bool* chromosom, int dlugosc)
{
	float wartosc = 0, potega = 1;
	for (int j = dlugosc - 1; j >= 0; j--)
	{
		if (chromosom[j]) wartosc = wartosc + potega;
		potega = potega * 2;
	}
	return wartosc;
}
float funkcjaOB(float x)
{
	xmax = powf(2, dlugChrom) - 1; int xmin = 0; //zakres wartości chr. dla przyjętego dlugChrom
	x = ((x / xmax)) * (xnMax - xnMin) + xnMin; //x = ((x - xmin) / (xmax - xmin)) * (xnMax -	xnMin) + xnMin; 
	return (-1 * powf(x, 2) + 25);
}
void parametryAG()
{
	cout << "\npodaj wielkosc populacji: "; cin >> rozmPop;
	cout << "\npodaj dlugosc chromosomu: "; cin >> dlugChrom;
	cout << "\npodaj max liczbe generacji: "; cin >> maxgen;
	cout << "\npodaj prawdopodob. krzyżowania: "; cin >> pKrzyzowanie;
	cout << "\npodaj prawdopodob mutacji: "; cin >> pMutacja;
	typSelekcji = 1;
	typKrzyzowania = 1;
	typMutacji = 1;
}
bool czyAkcja(float p)
{
	float los;
	if (p == 1.0) return true;
	else if (p == 0.0) return false;
	else
	{
		los = (rand() % 100) / 100.0;
		if (los <= p) return true; else return false;
	}
}
void inicjowaniePop(populacja& pop, int rozmPop)
{
	for (int i = 0; i < rozmPop; i++)
	{
		for (int j = 0; j < dlugChrom; j++) pop[i].chromosom[j] = czyAkcja(0.5);
		pop[i].x = Dekodowanie(pop[i].chromosom, dlugChrom);
		pop[i].dopasowanie = funkcjaOB(pop[i].x);
		pop[i].rodzic1 = 0; pop[i].rodzic2 = 0; pop[i].pRozciecia = 0; pop[i].pRozciecia1 = 0;
		pop[i].pRozciecia2 = 0;
	}
}
void statystyki(int rozmPop, float& max, float& avg, float& min, float& sumaDopasowania,
	populacja& pop)
{
	sumaDopasowania = pop[0].dopasowanie;
	min = pop[0].dopasowanie;
	max = pop[0].dopasowanie;
	xExtrMax = pop[0].x;
	xExtrMin = pop[0].x;
	for (int j = 1; j < rozmPop; j++)
	{
		sumaDopasowania += pop[j].dopasowanie;
		if (pop[j].dopasowanie > max) { max = pop[j].dopasowanie; xExtrMax = pop[j].x; }
		if (pop[j].dopasowanie < min) { min = pop[j].dopasowanie; xExtrMin = pop[j].x; }
	}
	avg = sumaDopasowania / rozmPop;
}
void inicjowanieAG()
{
	parametryAG();
	inicjowaniePop(popStara, rozmPop);
	statystyki(rozmPop, Max, Avg, Min, sumaDopasowania, popStara);
}
int wartLos(int wmin, int wmax)
{
	return rand() % (wmax - wmin + 1) + wmin;
}
bool mutacja(bool allel, float pMutacja)
{
	bool czyMutacja = czyAkcja(pMutacja); //czy ma byc mutacja
	if (czyMutacja)
	{
		if (typMutacji == 1) return !allel; //przez negację
		if (typMutacji == 2) return rand() % 2; //losowa 0..1
	}
	else return allel;
}
void krzyzowanie(chromosom& rodzic1, chromosom& rodzic2, chromosom& dziecko1,
	int& dlugChrom, int& punktRoz, int& punktRozc1, int& punktRozc2, float& pKrzyzowanie, float&
	pMutacja)
{ //2 rodzice->1 potomek
	if (czyAkcja(pKrzyzowanie))
	{
		if (typKrzyzowania == 1) punktRoz = wartLos(0, dlugChrom - 2); //indeks.0..dlugChrom - 1, pkt.rozc.nie mogą ost.genem->patrz rozc.nizej
			if (typKrzyzowania == 2)
			{
				punktRozc1 = wartLos(0, dlugChrom - 2); punktRozc2 = wartLos(0, dlugChrom- 2); //punkty rozciecia
				if (punktRozc1 > punktRozc2) {
					int j = punktRozc1; punktRozc1 = punktRozc2;
					punktRozc2 = j;
				} //zamiana aby p.1<p.2
			}
	}
	else
	{
		punktRoz = dlugChrom - 1; punktRozc1 = dlugChrom - 1; punktRozc2 = dlugChrom - 1;
		//indeksow. 0..dlugChrom-1 !!!
	}
	if (typKrzyzowania == 1) //[0..punktRoz] -> rodzic1+mutacja, [punktRoz+1,dlugChrom-1(do konca)]->rodzic2 + mutacja
	{
	for (int j = 0; j <= punktRoz; j++) dziecko1[j] = mutacja(rodzic1[j], pMutacja); //od 0 do 	pkt.rozc.włacznie bez zmian
	if (punktRoz != dlugChrom - 1) //jest rozciecie
	for (int j = punktRoz + 1; j < dlugChrom; j++) dziecko1[j] = mutacja(rodzic2[j],
	pMutacja);
	}
		if (typKrzyzowania == 2) //rozciecia: par1: [0..punktRozc1] par2: [punktRozc1+1, punktRozc2], par1: [punktRozc2 + 1, dlugChrom - 1]
		{
		for (int j = 0; j <= punktRozc1; j++) dziecko1[j] = mutacja(rodzic1[j], pMutacja);
		for (int j = punktRozc1 + 1; j <= punktRozc2; j++) dziecko1[j] = mutacja(rodzic2[j],
		pMutacja);
		for (int j = punktRozc2 + 1; j < dlugChrom; j++) dziecko1[j] = mutacja(rodzic1[j],
		pMutacja);
		}
}
double Zaokraglij(double liczba, int lmd = 2)
{
	liczba = powf(10, lmd) * liczba;
	liczba = liczba + 0.5;
	liczba = floor(liczba);
	liczba = liczba / powf(10, lmd);
	return liczba;
}
int selekcjaRuletka(int rozmPop, float sumaDopasowania, populacja pop)
{
	int j, k, n, s;
	tabSumyCzesciowe = new int[rozmPop];
	for (int i = 0; i < rozmPop; i++) {
		tabSumyCzesciowe[i] = Zaokraglij(popStara[i].dopasowanie * 100 /
			sumaDopasowania, 0); //tab. czestosci
	}
	s = 0;
	for (int i = 0; i < rozmPop; i++) s += tabSumyCzesciowe[i]; //suma częstości
	//cout<<"s="<<s<<endl;
	//for(int i=0;i<rozmPop;i++) cout<<tabSumyCzesciowe[i]<<" "; cout<<endl;
	tabRuletka = new int[s];
	k = 1; n = 0; //k-licznik powtórzeń w tab_rul, n-licznik tabSumyCzesciowe -> częstości zależnej	od wart.dopasowanie
		j = 0; //j-licznik tab_rul (wypelniana wystapieniami reprezent. rozwiązań)
		/*cout<<"\n j="<<j<<" s="<<s<<endl;*/
	while (j < s) //wstawianie numerów przypadków o czestosci >0 tyle razy ile czestosc czyli im większa f.dopas
	{
	if (tabSumyCzesciowe[n] == 0) { n++; } //bez wstawiania reprez. bo częstosc=0
	else {
	for (int i = 1; i <= tabSumyCzesciowe[n]; i++) {
	tabRuletka[j] = k; j++;
	}
	k++; n++;
	}
	}
		//cout<<"\ntab_ruletka: ";for(int j=0;j<s;j++) cout<<" "<<tabRuletka[j];cout<<endl;
		/*cout<<"\n ok14"<<endl;*/
	return s;
}
void generowaniePopulacji()
{
	int i, j, chrom1, chrom2, punktRozciecia, punktRozciecia1, punktRozciecia2, zakresRuletki;
	i = 0; punktRozciecia = 0; punktRozciecia1 = 0; punktRozciecia2 = 0;
	if (typSelekcji == 1) zakresRuletki = selekcjaRuletka(rozmPop, sumaDopasowania, popStara);
	//zakres indeksów ruletki
	if (dod_czyn_los == 2)//do sprawdzenia!!!!!!!!!!!!
	{
		i = floor(0.1 * rozmPop); //10%
		inicjowaniePop(popNowa, i);
		i++;
	}
	do {
		chrom1 = tabRuletka[rand() % zakresRuletki]; chrom2 = tabRuletka[rand() %
			zakresRuletki]; //sel. prop
		krzyzowanie(popStara[chrom1].chromosom, popStara[chrom2].chromosom,
			popNowa[i].chromosom, dlugChrom, punktRozciecia, punktRozciecia1, punktRozciecia2,
			pKrzyzowanie, pMutacja);
		popNowa[i].x = Dekodowanie(popNowa[i].chromosom, dlugChrom);
		popNowa[i].dopasowanie = funkcjaOB(popNowa[i].x);
		popNowa[i].rodzic1 = chrom1;
		popNowa[i].rodzic2 = chrom2;
		popNowa[i].pRozciecia = punktRozciecia; popNowa[i].pRozciecia1 = punktRozciecia1;
		popNowa[i].pRozciecia2 = punktRozciecia2;
		i++;
	} while (i < rozmPop);
	tabSumyCzesciowe = NULL; tabRuletka = NULL;
}
void wypiszChromosom(chromosom chr, int dlugChrom)
{
	for (int i = dlugChrom - 1; i >= 0; i--)
	{
		if (chr[i]) cout << "1"; else cout << "0";
	}
}
void raport(int generacja)
{
	for (int j = 0; j < rozmPop; j++)
	{
		cout << setw(3) << j + 1 << ") "; wypiszChromosom(popStara[j].chromosom,
			dlugChrom);
		cout << " " << fixed << setprecision(3) << setw(8) << ((popStara[j].x / xmax)) * (xnMax
			- xnMin) + xnMin << setw(10) << popStara[j].dopasowanie << " |";
		cout << " " << setw(3) << j + 1 << ") (" << setw(2) << popNowa[j].rodzic1 << "," <<
			setw(2) << popNowa[j].rodzic2 << ") " << popNowa[j].pRozciecia << " " << popNowa[j].pRozciecia1 <<
			" " << popNowa[j].pRozciecia2 << " ";
		wypiszChromosom(popNowa[j].chromosom, dlugChrom); cout << setw(8) <<
			((popNowa[j].x / xmax)) * (xnMax - xnMin) + xnMin << setw(10) << popNowa[j].dopasowanie << endl;
	}
	cout << "------------------------------" << endl;
	cout << " generacja:" << generacja << " max=" << Max << " min=" << Min << " Avg=" << Avg
		<< " sumaDopasowania=" << sumaDopasowania << endl;
	cout << " xextrMax=" << ((xExtrMax / xmax) * (xnMax - xnMin) + xnMin) << endl;
	cout << " xextrMin=" << ((xExtrMin / xmax) * (xnMax - xnMin) + xnMin) << endl;
	cout << "------------------------------" << endl;
}
void fSort(populacja pop, int p, int k)
{
	int i, j, wtemp, pivot;
	i = p; j = k;
	pivot = pop[rand() % (p - k + 1) + p].dopasowanie;
	while (i <= j)
	{
		while (pop[i].dopasowanie < pivot) i++;
		while (pop[j].dopasowanie > pivot) j--;
		if (i <= j)
		{
			wtemp = pop[i].dopasowanie; pop[i].dopasowanie = pop[j].dopasowanie;
			pop[j].dopasowanie = wtemp;
			i++; j--;
		}
	}
	if (i < k) fSort(pop, i, k);
	if (p < j) fSort(pop, p, j);
}
int main()
{
	srand(time(NULL));
	generacja = 0; genMax = 0; genMin = 0;
	inicjowanieAG();
	do {
		generacja++;
		generowaniePopulacji();
		statystyki(rozmPop, Max, Avg, Min, sumaDopasowania, popNowa);
		if (generacja == 1) {
			Max_a = Max; Min_a = Min; genMax = generacja; genMin = generacja;
			xExtrMax_a = xExtrMax; xExtrMin_a = xExtrMin;
		}
		if (Max > Max_a) { Max_a = Max; genMax = generacja; xExtrMax_a = xExtrMax; }
		if (Min < Min_a) { Min_a = Min; genMin = generacja; xExtrMin_a = xExtrMin; }
		for (int i = 0; i < rozmPop; i++) popStara[i] = popNowa[i];
	} while (generacja < maxgen);
	cout << "\n-----------------------------------------------------------------";
	cout << "\n-----------------------------------------------------------------" << endl;
	cout << "\n najlepsze Max: " << Max_a << " osiagniete w generacji: " << genMax << endl;
	cout << " xextrMax=" << ((xExtrMax_a / xmax) * (xnMax - xnMin) + xnMin) << endl;
	cout << "\n koniec algorytmu! ";
	system("Pause");
	cout << "\n\n";
	return 0;
}