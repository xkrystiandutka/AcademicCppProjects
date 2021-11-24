#include<iostream>
#include <random>
#include <iomanip>
using namespace std;

random_device rd;
uniform_int_distribution<> ud(0, 99);

void sort_szybkie(int t[], int p, int k)
{
    int i, j, wtemp, pivot;
    i = p; j = k;
    pivot =t[(p + k) / 2]; // tutaj należy dopisać formułę wyliczającą wartość pivota
    while (i <= j)
    {
        cout << "pivot= " << pivot<<endl;
      
       while (t[i] < pivot) i++;
       while (t[j] > pivot) j--;
        if (i <= j)
        {
          

            wtemp = t[i]; t[i] = t[j]; t[j] = wtemp;
            i++; j--;
            for (int i = p; i < k+1; i++)
            {
                cout << t[i] << " ";
                
            }   
          
            cout << endl;
        }
    }
    if (p < j) sort_szybkie(t, p, j); //sortowanie lewej podtablicy
    if (i < k) sort_szybkie(t, i, k); //sortowanie prawej podtablicy
}


int main()
{ 
    
    cout << "Elementy przed sortowaniem:"<<endl;
        int tab[9];
    for (int i = 0; i < 9; i++)
    {      
            int los = ud(rd);
            tab[i] = los;
            cout << "[" << tab[i] << "]";
     
    }

    cout << "\n\nElementy po sortowaniem rosnaco:" << endl;
    sort_szybkie(tab,0, 8);
    for (int i = 0; i < 9; i++)
    {
        cout << "[" << tab[i] << "]";
    }
      
    return 0;
}