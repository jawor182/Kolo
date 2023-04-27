// Kolory.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
// github.com/markpal/Kolory
/**/
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>  
#include <fstream>
#include <random>
#include<vector>
#include <cstdlib>
#include<ctime>

using namespace std;
string getHaslo() {
    vector<string> hasla;
    string haslo;
    ifstream plik("hasla.txt");
    if (plik.is_open()) {
        while (getline(plik, haslo)) {
            hasla.push_back(haslo);
        }
        plik.close();
    }
    srand(time(0));
    int losowa_pozycja = rand() % hasla.size();
    return hasla[losowa_pozycja];
}
struct Gracz {
    string imie;
    int kasa = 0;
    int portfel = 0; //kasa z wygranych rund
};



int kolejka = 0;

int Kolo[] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };
// -1 bankrut
// 0 strata kolejki


void textColor(char c = 'W')
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    auto colors = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; //default white gray

    switch (c) {
    case 'Y':   //yellow
        colors = FOREGROUND_RED | FOREGROUND_GREEN;
        break;
    case 'R':
        colors = 12;
        break;
    case 'G':
        colors = FOREGROUND_GREEN;
        break;
    case 'B':
        colors = FOREGROUND_BLUE | FOREGROUND_GREEN;
        break;
    case 'P':
        colors = FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        break;
    default:
        //colors = 22;
        break;
    }

    SetConsoleTextAttribute(hStdOut, colors);

}
struct Gracz gracze[3];
void textPlayers()
{
    int i;
    textColor('O');
    std::cout << "\n";
    for (i = 0; i < 3; i++)
        cout << gracze[i].imie << "\t" << gracze[i].kasa << "\n";
    cout << "\n";
}

int jestSamogloska(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y')
        return 1;
    else
        return 0;

}


int main()
{
    int i;
    vector<string> imiona;
    int ilosc_graczy;
    string haslo = getHaslo();
    string proba;
    char literka;
    int n = haslo.size();
    int maska[100];
    int suma = 0;
    int zgadl = 0;
    int sa_spolgloski = 0;
    int kwota = 0;
    srand(time(NULL));
    string rezultat;

    cout << "Jak nazywa sie 4 zawodnikow \n";
    cin >> ilosc_graczy
    for(int z = 0 ; z < ilosc_graczy;z++){
        
        string imiona[ilosc_graczy];
        cout << "\n" <<  "Podaj imie nr " << z + 1 << ": \n" ;
        cin >> imiona[z];
        string playerName = imiona[z];
        gracze[z].imie = playerName;
        for (int h = 0 ; h < 1;h++){
            cout <<  gracze[z].imie << "\n";
        }
    }
    
    for (i = 0; i < n; i++)
    {
        if (haslo[i] == ' ')
            maska[i] = 0;
        else
            maska[i] = 1;
    }

    textColor('P');
    for (i = 0; i < n; i++)
    {
        if (maska[i] == 1)
            cout << ".";
        else
            cout << haslo[i];
    }
    textColor('Z');
    cout << endl;


    do
    {
        sa_spolgloski = 0;
        kwota = 0;

        for (i = 0; i < n; i++)
            if ((!jestSamogloska(haslo[i])) && (maska[i]))
            {
                sa_spolgloski = 1;
                break;
            }

        if (sa_spolgloski) {
            cout << " -- Spolgloski sa --" << endl;
        }
        cout << "1. aby zgadnac haslo" << endl;
        cout << "2. aby zakrecic kolem" << endl;
       // cout << "3. aby kupic samogloske" << endl;
        int wybor;
        cin >> wybor;

        if (1 == wybor) {
            cout << "Podaj haslo: ";
            cin >> proba;
        
           
            if (proba == haslo) {
                cout << "=========== Zwyciestwo ==============";
                gracze[kolejka].portfel += gracze[kolejka].kasa;
                break;
            }
            else
            {
                kolejka = (kolejka + 1) % 3;
                suma = 1;
                cout << endl << "=================================================" << endl;
                cout << endl << "============================ zle ================" << endl;
            } 
                
            
        }
       /* else if ( 3 == wybor){
            cout << "do wyboru masz: a, e, y, u, i, o: ";
            char wybranaSamogloska ;
            cin >> wybranaSamogloska;
            cout << "wybrales " << wybranaSamogloska << endl;
            for (int i = 0; i < n; i++) {
                if(maska[i] == wybranaSamogloska){
                    cout << "znaleziono samogloske" << endl;
                     }
                else{
                    cout << "Nie ma " << endl;
                    continue;
                }
                }

          
        } */
        cout << gracze[kolejka].imie << " ";

        rezultat = "";
        i = rand() % 15;
        if (Kolo[i] == 0)
            rezultat = "Strata kolejki";
        if (Kolo[i] == -1)
            rezultat = "Bankrut";
        if (rezultat != "")
            cout << "\033[1;31m" << rezultat << "\033[0m" << endl;
        else
        {
            cout << "\033[1;34m" << Kolo[i] << "\033[0m" << endl;
            kwota = Kolo[i];
        }

        // Strata kolejki i bankrut
        if ((Kolo[i] == 0) || (Kolo[i] == -1))
        {
            if (Kolo[i] == -1) // bankrut
                gracze[kolejka].kasa = 0;

            kolejka = (kolejka + 1) % 3;
            suma = 1;
            cout << endl << "=================================================" << endl;
            continue;

        }





        cout << gracze[kolejka].imie << ": Podaj litere" << endl;
        cin >> literka;
        zgadl = 0;

        if (jestSamogloska(literka))
            cout << "samogloska";
        else
            cout << "spolgloska";
        cout << endl;

        for (i = 0; i < n; i++)
        {
            if ((haslo[i] == literka) && (maska[i] == 1)) {
                maska[i] = 0;
                zgadl++;
            }
        }

        if (zgadl)
        {
            cout << "OK";
            gracze[kolejka].kasa += kwota * zgadl;

            cout << endl << gracze[kolejka].imie << "\033[1;32m " << gracze[kolejka].kasa << "\033[0m";


        }
        else {
            cout << "Zle!";
            // strata kolejki
            kolejka = (kolejka + 1) % 3;
            cout << endl << "=================================================" << endl;
            suma = 1;
            continue;
        }




        cout << endl;

        textColor('P');
        for (i = 0; i < n; i++)
        {

            if (maska[i] == 1)
                cout << ".";
            else
                cout << haslo[i];
        }
        textColor('Z');
        cout << endl;

        suma = 0;

        for (i = 0; i < n; i++)
        {
            suma += maska[i];
        }

    } while (suma);
    cout << "BRAWO!";
    exit(0);

    textPlayers();
    Beep(523, 500);
}
