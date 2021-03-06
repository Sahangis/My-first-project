#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::to_string;
using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::setprecision;
using std::fixed;
using std::sort;

struct dat {
	string vardas, pavarde;
	vector<int> pazymiai;
	int egzaminas;
	double answer;
};

dat generavimas(int quantity);
dat input(int i);
dat skaitymas(int n, ifstream& fd);
void outputas(string& output, dat a, bool kurimas);
bool FileExists(string filename);
void rasymas(vector<dat> temp);
void rasymas_s(vector<dat> temp, const string RF);
void isskyrimas(vector<dat>& poor, vector<dat>& cool, vector<dat> all);
void isskyrimas2(vector<dat>& poor, vector<dat> &all);
