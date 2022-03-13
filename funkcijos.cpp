#include "funkcijos.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <iomanip>


using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::setprecision;
using std::fixed;
using std::sort;

string vardai[16] = { "Martynas", "Jonas", "Vilijamas", "Kristijonas", "Vincas", "Alberas", "Francas" , "Juozas", "Jurgis", "Antanas", "Henrikas", "Balys", "Augustas", "Justinas", "Ernestas", "Hansas" };
string pavardes[16] = { "Dauksa", "Radvanas", "Marcinkevicius", "Kafka", "Kamiu", "Kudirka", "Shekspyras", "Donelaitis", "Mickevicius", "Biliunas", "Vaizgantas", "Radauskas", "Krivickas", "Savickis", "Sruoga", "Katiliskis" };


dat input(int i)
{
	dat temp;
	do {
		cout << "iveskite " << i << " -ojo mokinio varda(ilgis ne daugiau 15 simboliu): " << endl;
		cin >> temp.vardas;
		if (temp.vardas.length() >= 16) cout << "ivestas per ilgas vardas, prasome ivesti trumpesni" << endl;
	} while (temp.vardas.length() >= 16);
	do {
		cout << "iveskite " << i << " -ojo mokinio pavarde(ilgis ne daugiau 15 simboliu): " << endl;
		cin >> temp.pavarde;
		if (temp.pavarde.length() >= 16) cout << "ivesta per ilga pavarde, prasome ivesti trumpesne" << endl;
	} while (temp.pavarde.length() >= 16);
	bool inFail;
	int sk;
	vector<int> pazymiai;
	do {
		int j = 0;
		do {
			cout << "iveskite " << j + 1 << " pazimi" << endl;
			cin >> sk;
			inFail = cin.fail();
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			if (!inFail)
			{
				if (sk > 10 or sk < 0) inFail = true;
				else pazymiai.push_back(sk);
			}
			j++;
		} while (!inFail);
		if (pazymiai.size() == 0) cout << "Negalime skaiciuoti rezultatu su mokiniu kuris neturi pazymiu, prasome vesti vel" << endl;
	} while (pazymiai.size() == 0);

	do {
		cout << "iveskite egzamino rezultata" << endl;
		cin >> temp.egzaminas;
		inFail = cin.fail();
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		if (!inFail) if (temp.egzaminas > 10 or temp.egzaminas < 0) inFail = true;
	} while (inFail);

	int sum = 0;
	for (int j = 0; j < pazymiai.size(); j++) sum += pazymiai[j];
	temp.answer[0] = 0.4 * (sum * 1.0 / pazymiai.size()) + 0.6 * (temp.egzaminas * 1.0);
	sort(pazymiai.begin(), pazymiai.end());
	if (pazymiai.size() % 2 == 0) temp.answer[1] = (pazymiai[pazymiai.size() / 2] + pazymiai[pazymiai.size() / 2 - 1]) * 1.0 / 2 * 0.4 + temp.egzaminas * 1.0 * 0.6;
	else temp.answer[1] = pazymiai[pazymiai.size() / 2] * 1.0 * 0.4 + temp.egzaminas * 1.0 * 0.6;
	pazymiai.clear();
	return temp;
}

dat generavimas()
{
	dat temp;
	int index = (double)rand() / RAND_MAX * 16;
	temp.vardas = vardai[index];
	int index2 = (double)rand() / RAND_MAX * 16;
	temp.pavarde = pavardes[index2];
	int quantity;
	do {
		quantity = (double)rand() / RAND_MAX * 10;
	} while (quantity == 0);
	int sum = 0;
	vector<int> pazymiai;
	for (int i = 0; i < quantity; i++)
	{
		int value = (double)rand() / RAND_MAX * 10;
		pazymiai.push_back(value);
		sum += value;
	}
	int egz = (double)rand() / RAND_MAX * 10;
	temp.egzaminas = egz;
	temp.answer[0] = sum * 1.0 / quantity * 0.4 + temp.egzaminas * 1.0 * 0.6;
	sort(pazymiai.begin(), pazymiai.end());
	if (quantity % 2 == 1) temp.answer[1] = pazymiai[quantity / 2] * 1.0 * 0.4 + temp.egzaminas * 1.0 * 0.6;
	else temp.answer[1] = (pazymiai[quantity / 2] + pazymiai[quantity / 2 - 1]) * 1.0 / 2 * 0.4 + temp.egzaminas * 1.0 * 0.6;
	return temp;
}

dat skaitymas(int n, ifstream &fd)
{
	dat temp;
	int sk, sum = 0;
	fd >> temp.vardas;
	if (fd.eof()) return temp;
	fd >> temp.pavarde;

	vector<int> pazymiai = vector<int>(n);
	for (int i = 0; i < n; i++)
	{
		fd >> sk;
		sum += sk;
		pazymiai[i] = sk;
	}
	fd >> temp.egzaminas;
	temp.answer[0] = sum * 1.0 / n * 0.4 + temp.egzaminas * 1.0 * 0.6;
	sort(pazymiai.begin(), pazymiai.end());
	if (n % 2) temp.answer[1] = temp.egzaminas * 1.0 * 0.6 + pazymiai[n / 2] * 1.0 * 0.4;
	else temp.answer[1] = temp.egzaminas * 1.0 * 0.6 + (pazymiai[n / 2] + pazymiai[n / 2 - 1]) * 1.0 / 2 * 0.4;
	return temp;
}

void rasymas(vector<dat> temp)
{
	cout << left << setw(16) << "Vardas" << left << setw(16) << "Pavarde" << left << setw(18) << "Galutinis (Vid.)" << left << setw(16) << "Galutinis(Med.)" << endl;
	cout << "----------------------------------------------------------------" << endl;
	for (int i = 0; i < temp.size(); i++) cout << left << setw(16) << temp[i].vardas << left << setw(16) << temp[i].pavarde << left << setw(18) << fixed << setprecision(2) << temp[i].answer[0] << left << setw(16) << fixed << setprecision(2) << temp[i].answer[1] << endl;
}
