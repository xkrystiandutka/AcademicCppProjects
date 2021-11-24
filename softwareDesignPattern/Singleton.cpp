#include <iostream> 
using namespace std; 
class Singleton 
{ 
 static Singleton* instancja; //przechowuje jedyny możliwy obiekt
 static int liczbaObiektow; //dodatkowa zmienna, nie związana z samym wzorcem
 Singleton() {liczbaObiektow++;} //prywatny konstruktor uruchamiany przez met. Instancja()
public: 
 static Singleton* Instancja() //static-> wywoływanie bez obiektu
 { 
 cout << "\n proba utworzenia nowego obiektu..."; 
 if (instancja == NULL) //pusty wskaźnik do obiektu -> tworzenie obiektu
 { 
 cout << "\n wywolanie konstruktora..."; 
 instancja = new Singleton(); 
 } 
 else cout << "\n nowy obiekt nie zostal utworzony..."; 
 return instancja; 
 } 
 void ilosc() 
 { 
 cout << "\n Liczba obiektow = " << liczbaObiektow; 
 } 
}; 
Singleton* Singleton::instancja; 
int Singleton::liczbaObiektow; 
int main() 
{ 
 Singleton* s1 = Singleton::Instancja(); s1->ilosc(); //ok
 Singleton* s2 = Singleton::Instancja(); s2->ilosc(); //nowy się nie utworzy
 if (s1 == s2) //porównanie adresów, równość oznacza dwa wskaźniki na ten sam obiekt
 { 
 cout<<"\n ta sama instancja obiektów"; 
 } 
 else cout<<"\n dwa różne obiekty"; 
 //Singleton* s = new Singleton(); //nie można wywołać (konstruktor jest private) 
 cout << "\n\n"; 
} 