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

using std::cout;
using std::cin;
using namespace std;
using namespace chrono;

int liczba; //podana liczba (nwm czy liczba bedzie taka, czy nie bedzie w formacie string, zobaczymy)
bool wynik; //czy jest pierwsza czy nie



//  <====================================>
//	WYKORZYSTANE W FUNKCJACH GLOWNYCH FUNKCJE PROGRAMU
//  <====================================>

void Naglowek()
{
	system("cls"); //zamiast system cls bedzie funckja czyszczenia z biblioteki ncurses
	cout << "					  Architektura komputerow 2\n";
	cout << "       Aplikacja sprawdzajaca czy podana liczba jest liczba pierwsza\n";
	cout << "\n         Autorzy: Wojciech Ziebicki [241 141] & Artur Soltys [251 xxx]\n\n\n";
}
void MenuGlowne()
{
	Naglowek();

	cout << "	M E N U    G L O W N E\n\n";
	cout << "   1. Wyszukiwanie liczby pierwszej\n";
	cout << "   2. Wczytanie wszystkich wynikow\n";
	cout << "   0. Wyjscie z aplikacji\n";
}

void ZapiszWynikiDoPliku(int liczba, bool wyniczek)
{
	if (wyniczek)
	{
		try {
			fstream plik; // nazwa pliku do ktorego podajemy kolejne czasy dodawan

			plik.open("LiczbyPierwsze.txt", ios::out | ios::app);
			if (plik.good() == true)
			{
				plik << liczba << "\n";
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
				plik << liczba << "\n";
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

string SzukajPierwszosci(int liczba)
{
	//algorytm szukaj pierwszosci z polaczeniem arduino
	string temp;

	stringstream ss;
	ss << liczba;
	string str = ss.str();

	temp = "Liczba " + str;
	if (wynik)
	{
		temp += " jest liczba pierwsza";
		return temp;
	}
	temp += " nie jest liczba pierwsza";
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
			Naglowek();
			WczytajLiczbe();

			cout << "Rozpoczynam sprawdzanie pierwszosci podanej liczby: " << liczba << endl;

			string wynik = SzukajPierwszosci(liczba);
			cout << wynik;

		cout << "\n\nCzy chcesz powtorzyc szukanie liczby? \n 1 - powtorz\n 0 - wyjdz" << endl;
		cin >> x;
		}
	} while (x == 1); //tu sie konczy doWhile
}

void WczytajWyniki()
{

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
