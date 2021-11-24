#include <iostream> 
#include <string> 
using namespace std; 
class Pakiet abstract //słowo abstract nie jest wymagane gdy min. jedna metoda jest czysto wirtualna
{ 
protected: 
 string nazwa_pakietu = "Podstawowy"; 
public: 
 virtual string info() 
 { 
 cout << "\n"; 
 return nazwa_pakietu; 
 } 
 virtual double cena() abstract ; //virtual double cena() = 0; //oba zapisy ok
}; 
// definicja klas pakietów podstawowych 
class PakietMini : public Pakiet 
{ 
public: 
 PakietMini() 
 { 
 nazwa_pakietu = "Mini"; 
 } 
 double cena() override //override -> nadpisanie dziedziczonej/implementowanej metody 
 { 
 return 39; 
 } 
}; 
class PakietMidi : public Pakiet 
{ 
public: 
 PakietMidi() 
 { 
 nazwa_pakietu = "Midi"; 
 } 
 double cena() override 
 { 
 return 59; 
 } 
}; 
// abstrakcyjny dekorator 
class Dekorator abstract : public Pakiet 
{ 
public: 
 virtual string info() abstract; //virtual string info() override = 0; 
}; 
//definicja dodatków 
class Internet : public Dekorator 
{ 
 Pakiet* pakiet_rozszerzany; 
public: 
 Internet(Pakiet* typ_pakietu) //argumentem może być np. PakietMini, PakietMidi, Telefon)
 { 
 pakiet_rozszerzany = typ_pakietu; 
 } 
 string info() override 
 { 
 return pakiet_rozszerzany->info() + " + Internet"; 
 } 
 double cena() override 
 { 
 //cout << "\n typ rozsz: " << typeid(*pakiet_rozszerzany).name()<<endl; 
 if (typeid(*pakiet_rozszerzany) == typeid(PakietMini)) 
 { 
 return pakiet_rozszerzany->cena() + 30; 
 } 
 else if (typeid(*pakiet_rozszerzany) == typeid(PakietMidi)) 
 { 
 return pakiet_rozszerzany->cena() + 25; 
 } 
 return 0; //gdy pakietem rozszerzanym nie jest Mini lub Midi
 } 
}; 
class Telefon : public Dekorator 
{ 
 Pakiet* pakiet_rozszerzany; 
public: 
 Telefon(Pakiet* typ_pakietu) //argumentem może być np. PakietMini, PakietMidi, Internet)
 { 
 pakiet_rozszerzany = typ_pakietu; 
 } 
 string info() override 
 { 
 return pakiet_rozszerzany->info() + " + Telefon"; 
 } 
 double cena() override 
 { 
 //cout << "\n typ rozsz: " << typeid(*pakiet_rozszerzany).name() << endl; 
if (typeid(*pakiet_rozszerzany) == typeid(Internet)) return 
pakiet_rozszerzany->cena() + 40; 
 else return pakiet_rozszerzany->cena() + 50; 
 } 
}; 
int main() 
{ 
 Pakiet* p1 = new PakietMini(); 
 Pakiet* p2 = new PakietMidi(); 
 cout<<"\n podstawowe wersje: "; 
 cout << p1->info()<<" "<<p1->cena(); 
 cout << p2->info()<<" "<<p2->cena(); 
 // wersja podstawowa z internetem 
 p1 = new Internet(p1); //dekorowanie 
 p2 = new Internet(p2); //obiekt dekorowany jest argumentem konstruktora klasy dekorującej
 cout<<"\n z internetem:"; 
 cout<<p1->info()<<" "<<p1->cena(); 
 cout<<p2->info()<<" "<<p2->cena(); 
 // z telefonem 
 Pakiet* p3 = new PakietMini(); 
 Pakiet* p4 = new PakietMidi(); 
 Pakiet* p5 = new Telefon(p3); 
 Pakiet* p6 = new Telefon(p4); 
 cout <<"\n z telefonem:"; 
 cout << p5->info() << " " << p5->cena(); 
 cout << p6->info() << " " << p6->cena(); 
 cout <<"\n z internetem i dodanym telefonem:"; 
 p1 = new Telefon(p1); //dodatkowo telefon do mini+internet 
 p2 = new Telefon(p2); //dodatkowo telefon do midi+intenet 
 cout << p1->info() << " " << p1->cena(); 
 cout << p2->info() << " " << p2->cena(); 
 //pakiet z dodatkami:
 cout<<"\n pakiet z internetem oraz telefonem:"; 
 Pakiet* p7 = new Telefon(new Internet(new PakietMidi())); 
 cout<<p7->info()<<" "<<p7->cena(); 
 cout << "\n\n"; 
} 
