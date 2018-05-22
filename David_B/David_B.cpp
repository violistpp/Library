#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;
#define SIZE 100

const char Darb[] = "Darbuotojai.txt";

struct Darbuotojas
{
	string vardas;
	string pavarde;
	string pass;
	int visit[5]; // Last visit (metai, menuo, diena, valanda, minute);
};

//------------------------------------------- Kintamu sarasas ----------------------------------------
int darb_sk = 0; // darbuotoju skaicius.
Darbuotojas D[SIZE];
int darb; // Darbuotojas prie sistemos.
string var, pav, passw; // Prisijungiancio vard, pav ir slaptazodis.

//------------------------------------------- Funkciju sarasas ---------------------------------------
void Ivedimas(); // Duomenu ivedimas i sistema.
void Prisijungimas(); // Prisijungimas.
void NaujasDarb();
void DarbList(); // Darbuotoju saraso spausdynimas ir redagavimas (darbuotojo pridejimas).
void Save();

int main()
{
	Ivedimas();
	DarbList();
	Prisijungimas();
	NaujasDarb();
	DarbList();
	Save();

	return 0;
}

void Ivedimas()
{
	ifstream fin(Darb);
	//fin >> darb_sk;
	for (int i = 0; !fin.eof(); i++) // !fin.eof()
	{
		fin >> D[i].vardas >> D[i].pavarde >>  D[i].pass
			>> D[i].visit[0]
			>> D[i].visit[1]
			>> D[i].visit[2]
			>> D[i].visit[3]
			>> D[i].visit[4];
		darb_sk = i;
	}
	fin.close();
}

void Prisijungimas()
{
	bool f = false;
	int answer;
	while (true) {
		cout << "Prasome ivesti \nvarda >> ";
		cin >> var;
		cout << "pavarde >> ";
		cin >> pav;
		cout << "slaptazodi >> ";
		cin >> passw;

		for (int i = 0; i < darb_sk; i++)
		{
			if (D[i].vardas == var && D[i].pavarde == pav && D[i].pass == passw) {
				darb = i;
				cout << "Sekmingas Prisijungimas.\n Sveiki atvike, " << D[darb].vardas << "\n\n";
				f = true;

				// Fiksuojamas darbuotojo prisijungimo laikas.
				time_t now = time(0);
				tm *ltm = localtime(&now);

				D[darb].visit[0] = 1900 + ltm->tm_year;
				D[darb].visit[1] = 1 + ltm->tm_mon;
				D[darb].visit[2] = ltm->tm_mday;
				D[darb].visit[3] = ltm->tm_hour;
				D[darb].visit[4] = 1 + ltm->tm_min;
				break;
			}
		}
		if (f)
			break;
		else
		{
			cout << "Blogas ivedimas, bandikite dar karta." << endl;
			cout << "Bandyti dar karta? (1- taip / 0- ne) \n>> ";
			cin >> answer;
			if (answer == 0)
				break;
		}
	}
}

void NaujasDarb()
{
	int ans;
	int k = darb_sk;
	darb_sk++;
	cout << "Naujo darbuotojo vardas: " << endl;
	cin >> D[k].vardas;
	cout << "Pavarde: " << endl;
	cin >> D[k].pavarde;
	cout << "Slaptazodis (6 simb): " << endl;
	cin >> D[k].pass;

	while (true)
	{
		time_t now = time(0);
		tm *ltm = localtime(&now);
		D[k].visit[0] = 1900 + ltm->tm_year;
		D[k].visit[1] = 1 + ltm->tm_mon;
		D[k].visit[2] = ltm->tm_mday;
		D[k].visit[3] = ltm->tm_hour;
		D[k].visit[4] = 1 + ltm->tm_min;

		cout << "\nIvesti duomenys: " << endl;
		cout << D[k].vardas << " " << D[k].pavarde << " " << D[k].pass << endl;
		cout << "Viskas gerai? (1- taip / 0- ne) \n>> ";
		cin >> ans;
		if (ans == 1)
			break;
		else
		{
			bool t = true;
			while (t)
			{
				cout << "Kas pakeist? " << endl
					<< "0. Atsaukti " << endl
					<< "1. Varda " << endl
					<< "2. Pavarde " << endl
					<< "3. Slaptazodi " << endl;
				cout << ">> ";
				cin >> ans;
				switch (ans)
				{
				case 0:
					t = false;
					break;
				case 1:
					cout << "Iveskite pakeitima: " << endl;
					cin >> D[k].vardas;
					t = false;
					break;
				case 2:
					cout << "Iveskite pakeitima: " << endl;
					cin >> D[k].pavarde;
					t = false;
					break;
				case 3:
					cout << "Iveskite pakeitima: " << endl;
					cin >> D[k].pass;
					t = false;
					break;
				default:
					cout << "Tokio pasirinkimo nera. " << endl;
				}
			}
		}
	}
}

void DarbList()
{
	cout << "Darb. vardas:   | Pavarde:           | Paskutinis apsilankymas: " << endl;
	for (int i = 0; i < darb_sk; i++) {
		cout << fixed << left << setw(16) << D[i].vardas << "| "
			<< left << setw(19) << D[i].pavarde << "| "
			<< D[i].visit[0] << "/" << D[i].visit[1] << "/" << D[i].visit[2] << " " << D[i].visit[3] << ":" << D[i].visit[4] << endl;
	}
	cout << "\n\n";
}

void Save()
{
	ofstream fout(Darb);
	for (int i = 0; i < darb_sk; i++)
	{
		fout << D[i].vardas << " " << D[i].pavarde << " " << D[i].pass << " "
			<< D[i].visit[0] << " "
			<< D[i].visit[1] << " "
			<< D[i].visit[2] << " "
			<< D[i].visit[3] << " "
			<< D[i].visit[4] << endl;
	}
	fout.close();
}
