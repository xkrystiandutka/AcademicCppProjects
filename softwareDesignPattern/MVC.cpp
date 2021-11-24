#include <iostream> 
#include <string> 
using namespace std; 
class Przedmiot { // Model
 string idPrzedmiotu; 
 string nazwaPrzedmiotu; 
public: 
 string zwrocId() { return idPrzedmiotu; } 
 void ustawId(string id) { this->idPrzedmiotu = id; } 
 string zwrocNazwe() { return nazwaPrzedmiotu; } 
 void ustawNazwe(string nazwa) { this->nazwaPrzedmiotu = nazwa; } 
}; 
class WidokPrzedmiotu // Widok
{ 
public: 
 void wyswietlPrzedmiot(string idP, string nazwaP) 
 { cout << "\n id + nazwa przedmiotu: " << idP << " " << nazwaP << endl; } 
}; 
class KontrolerPrzedmiotu // Kontroler
{ 
Przedmiot model; 
 WidokPrzedmiotu widok; 
public: 
 KontrolerPrzedmiotu(Przedmiot model, WidokPrzedmiotu widok) 
 { 
 this->model = model; 
 this->widok = widok; 
 } 
 void ustawNazwePrzedmiotu(string nazwa) 
 { 
 model.ustawNazwe(nazwa); 
 } 
 string zwrocNazwePrzedmiotu() 
 { 
 return model.zwrocNazwe(); 
 } 
 void ustawIdPrzedmiotu(string id) 
 { 
 model.ustawId(id); 
 } 
 string zwrocIdPrzedmiotu() 
 { 
 return model.zwrocId(); 
 } 
 void aktualizujWidok() 
 { 
 widok.wyswietlPrzedmiot(model.zwrocId(), model.zwrocNazwe()); 
 } 
}; 
static Przedmiot dodajPrzedmiot() { 
 Przedmiot p; 
 p.ustawId("001"); 
 p.ustawNazwe("przedmiot001"); 
 return p; 
} 
int main() 
{ 
 Przedmiot model = dodajPrzedmiot(); // Model zawierający dane
 WidokPrzedmiotu widok; // Widok do wyświetlania danych z Modelu
 KontrolerPrzedmiotu kontroler(model, widok); // kontroler umożliwia współpracę M. i W.
 kontroler.aktualizujWidok(); // Kontroler inicjuje aktualizację Widoku (wyświetlenie danych) 
 kontroler.ustawNazwePrzedmiotu("nowanazwa"); 
//Kontroler reaguje na żądanie przez użytkownika modyfikacji danych w Modelu i zmienia nazwę 
//przedmiotu za pomocą odpowiedniej metody czyli ustawNazwePrzedmiotu() 
 kontroler.aktualizujWidok(); //wyświetlenie zmodyfikowanych danych
}