#include<iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <fstream>
#include "sqlite3.h"

using namespace std;

class Tabela {
private:
	string naziv;
	string* ret;
	vector<vector<string>> baza;
	vector<string> imena; //kolona

public:
	Tabela(vector<string> niz, string naziv, string* ret);
	string getNaziv() const {
		return naziv;
	}
	void pisi() {
		for (int i = 0; i < imena.size(); i++) {
			//cout << imena[i] << endl;
			*ret += imena[i];
			*ret += "\n";
		}
	}

	void select(vector<string> selektor, vector<vector<string>> uslov);
	void delte(vector<vector<string>> uslov);
	void update(vector<vector<string>> izmenjen, vector<vector<string>> uslov);
	void insert(vector<string> kolone, vector<vector<string>> zapisi);
	void saveTxt(ofstream& out);
	void saveSql(sqlite3* db, char* errMsg);

};