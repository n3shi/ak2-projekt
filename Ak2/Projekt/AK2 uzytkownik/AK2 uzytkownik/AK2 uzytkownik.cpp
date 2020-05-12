// AK2 uzytkownik.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <chrono>
#include <sstream>
#include <vector>
#include <deque>
#include <stack>
#include <list>
#include <stdlib.h>
#include "SerialPort.h"


using std::cout;
using std::cin;
using namespace std;
using namespace chrono;

int liczba; //podana liczba (nwm czy liczba bedzie taka, czy nie bedzie w formacie string, zobaczymy)
bool wynik; //czy jest pierwsza czy nie
string czasWykonania; //jak szybko udalo sie wyslac liczbe do Arduino, policzyc w arduino i odebrac wynik
bool canSave = false;

//
//
// MIERZENIE CZASU
//
//

class Czas {
public:
	high_resolution_clock::time_point czasPoczatkowy;
	high_resolution_clock::time_point czasKoncowy;

	void czasStart();
	void czasStop();
	long czasWykonania();
};

void Czas::czasStart() // rozpoczecie mierzenia czasu
{
	czasPoczatkowy = high_resolution_clock::now();
}

void Czas::czasStop() // zakonczenie mierzenia czasu
{
	czasKoncowy = high_resolution_clock::now();
}

long Czas::czasWykonania() // zwraca czas pomiedzy funkcjami czasPoczatkowy i czas Koncowy
{

	return duration_cast<milliseconds>(Czas::czasKoncowy - Czas::czasPoczatkowy).count();

}



//  <====================================>
//	WYKORZYSTANE W FUNKCJACH GLOWNYCH FUNKCJE PROGRAMU
//  <====================================>

void Naglowek()
{
	system("cls"); //zamiast system cls bedzie funckja czyszczenia z biblioteki ncurses
	cout << "					  Architektura komputerow 2\n";
	cout << "       Aplikacja sprawdzajaca czy podana liczba jest liczba pierwsza\n";
	cout << "\n         Autorzy: Wojciech Ziebicki [241 141] & Artur Soltys [248854]\n\n\n";
}
void MenuGlowne()
{
	Naglowek();

	cout << "	M E N U    G L O W N E\n\n";
	cout << "   1. Wyszukiwanie liczby pierwszej\n";
	cout << "   2. Wczytanie wszystkich wynikow\n";
	cout << "   0. Wyjscie z aplikacji\n";
}
void MenuWynikow()
{
	Naglowek();

	cout << "	M E N U   W Y N I K O W\n\n";
	cout << "   1. Znalezione liczby pierwsze\n";
	cout << "   2. Znalezione liczby nie pierwsze\n";
	cout << "   0. Wyjscie z aplikacji\n";
}

void ZapiszWynikiDoPliku(int liczba, bool wyniczek, string czas)
{
	if (canSave)
	{

		if (wyniczek)
		{
			try {
				fstream plik; // nazwa pliku do ktorego podajemy kolejne czasy dodawan

				plik.open("LiczbyPierwsze.txt", ios::out | ios::app);
				if (plik.good() == true)
				{
					plik << "\n" << liczba << " jest liczba pierwsza. Czas obliczen: " << czas;
					plik.close();
				}
				plik.close();
				cout << "Wynik zostal zapisany poprawnie";
			}
			catch (exception e) {
				cout << "Wynik nie zostal zapisany poprawnie";
			}
		}
		else
		{
			try {
				fstream plik; // nazwa pliku do ktorego podajemy kolejne czasy dodawan

				plik.open("LiczbyNiepierwsze.txt", ios::out | ios::app);
				if (plik.good() == true)
				{
					plik << "\n" << liczba << " nie jest liczba pierwsza. Czas obliczen: " << czas;
					plik.close();
				}
				plik.close();
				cout << "Wynik zostal zapisany poprawnie";
			}
			catch (exception e) {
				cout << "Wynik nie zostal zapisany poprawnie";
			}
		}
	}
	else cout << "\n Nie zapisano wyniku (brak wyniku)";
}

int algorytmPierwszosci(string liczba)
{
	int i = 0;
	char output[MAX_DATA_LENGTH];
	char commport1[] = "\\\\.\\COM2";
	char commport2[] = "\\\\.\\COM3";
	char commport3[] = "\\\\.\\COM1";
	char commport4[] = "\\\\.\\COM4";
	char* port = commport1;
	char* tab[] = { commport1, commport2, commport3, commport4 };

	char incoming[MAX_DATA_LENGTH];



	for (int i = 0; i < 4; i++)
	{
		SerialPort arduino(tab[i]);
		canSave = false;
		if (arduino.isConnected())
		{
			cout << "Polaczono sie na porcie: " << tab[i] << "\n\n";

			while (arduino.isConnected()) //wykonuj dopoki arduino jest podlaczone
			{
				string data; //to co wysylamy do arduino
				data = liczba;
				char* charArray = new char[data.size() + 1];
				copy(data.begin(), data.end(), charArray);
				charArray[data.size()] = '\n';

				cout << "Pytanie do arduino: czy liczba " + liczba +
					" jest liczba pierwsza?\n(odpowiedz od arduino bedzie taka: 1 - tak    0 - nie)" << endl;
				arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
				arduino.readSerialPort(output, MAX_DATA_LENGTH);


				delete[] charArray;
				int tempx = atoi(output);
				canSave = true;
				cout << "Odpowiedz arduino: ";
				//cout << output;
				cout << tempx << endl;

				return tempx;
			}

			break;
		}
		else
		{
			cout << "Nie udalo sie polaczyc na porcie: " << tab[i] << "\n\n";
		}
	}
}

string SzukajPierwszosci(int liczba)
{
	string temp;

	stringstream ss;
	ss << liczba;
	string str = ss.str();

	//przekomentuj TO POD SPODEM JESLI CHCESZ SPRAWDZIC CZY DZIALA RESZA BEZ LAZCENIA SIE Z ARDUINO
	//int tempLiczba = 0;
	int tempLiczba = algorytmPierwszosci(str);


	temp = "Liczba " + str;
	if (tempLiczba == 1)
	{
		temp += " jest liczba pierwsza \n";
		wynik = true;
	}
	else if (tempLiczba == 0)
	{
		temp += " nie jest liczba pierwsza\n";
		wynik = false;
	}
	else temp = "Odczytano cos innego \n";
	return temp;
}

void WczytajLiczbe()
{
	cout << "Czy chcesz podac wlasna liczbe, czy wybrac losowa?\n 1 - wlasna \n 2 - losowa\n";
	cin >> liczba;
	if (liczba == 1)
	{
		cout << "Podaj wartosc liczby" << endl;
		cin >> liczba;

		cout << endl << endl;
	}
	else if (liczba == 2)
	{
		liczba = rand();
	}
	if (liczba < 0) liczba = liczba * -1; //na wszelki wypadek robimy tylko na dodatnich
}



//  <====================================>
//	GLOWNE FUNKCJE PROGRAMU
//  <====================================>

void ZnajdzLPierw()
{

	int x = 1;
	do {
		if (x == 1)
		{
			Czas time;
			Naglowek();
			WczytajLiczbe();

			cout << "Rozpoczynam sprawdzanie pierwszosci podanej liczby: " << liczba << endl;


			time.czasStart();
			string odpowiedz = SzukajPierwszosci(liczba);
			time.czasStop();

			czasWykonania = to_string(time.czasWykonania() * 0.001);
			czasWykonania += " s";
			cout << odpowiedz;

			ZapiszWynikiDoPliku(liczba, wynik, czasWykonania);

			cout << "\n\nCzy chcesz powtorzyc szukanie liczby? \n 1 - powtorz\n 0 - wyjdz" << endl;
			cin >> x;
		}
	} while (x == 1); //tu sie konczy doWhile
}


void Wyniki(string nazwa)
{
	fstream uchwyt; //obiekt typu fstream (uchwyt do pliku)

	uchwyt.open(nazwa); //otwieramy plik: plik.txt (plik - nazwa pliku, txt - rozszerzenie)
	string linia;

	if (uchwyt.good())
		while (!uchwyt.eof())
		{
			getline(uchwyt, linia); //pobierz linijkę
			cout << linia << endl; //wypisz na ekranie
		}
	uchwyt.close(); //zamykamy plik
}

void WczytajWyniki()
{
	int x = 1;
	do {
		if (x == 1)
		{
			MenuWynikow();
			string nazwaPliku;
			int temp = 0;
			cout << "\n\nKtore wyniki wyswietlic?" << endl;
			cin >> temp;
			if (temp == 1)
			{
				cout << "\n\nWyswietlam znalezione liczby pierwsze:\n\n";
				nazwaPliku = "liczbyPierwsze.txt";
				Wyniki(nazwaPliku);

			}
			else if (temp == 2)
			{
				cout << "\n\nWyswietlam znalezione liczby nie pierwsze:\n\n";
				nazwaPliku = "liczbyNiepierwsze.txt";
				Wyniki(nazwaPliku);
			}
			else cout << "\n\nPodano niepoprawna wartosc";

			cout << "\n\nCzy chcesz powtorzyc wyswietlanie? \n 1 - powtorz\n 0 - wyjdz" << endl;
			cin >> x;
		}
	} while (x == 1); //tu sie konczy doWhile
}




int main()
{
	int as;
	do {

		system("CLS");
		MenuGlowne();

		as = _getch();
		switch (as)
		{
		case '1': ZnajdzLPierw(); break;
		case '2': WczytajWyniki(); break;
		case '0': return 0; break;
		}
	} while (as != '.');

	return 0;
	cout << "Hello World!\n";
}
