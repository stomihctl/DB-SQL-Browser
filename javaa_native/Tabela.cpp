#include "Tabela.h"

Tabela::Tabela(vector<string> niz, string naziv, string* ret)
{
	this->naziv = naziv;
	imena = niz;
	this->ret = ret;
}

void Tabela::select(vector<string> selektor, vector<vector<string>>uslov)
{
	vector<int> koji;
	//cout << endl << endl << naziv << endl;
	*ret += "\n\n";
	*ret += naziv;
	*ret += "\n";
	if (selektor[0] == "*") {
		for (int i = 0; i < imena.size(); i++) {
			koji.push_back(i);
			//cout << imena[i] << "\t";
			*ret += imena[i];
			*ret += "\t";
		}
		//cout << endl;
		*ret += "\n";
	}
	else {
		for (int i = 0; i < selektor.size(); i++) {
			for (int j = 0; j < imena.size(); j++) {
				if (imena[j] == selektor[i]) {
					koji.push_back(j);
					//cout << imena[j] << "\t";
					*ret += imena[j];
					*ret += "\t";
				}
			}
		}
		//cout << endl;
		*ret += "\n";
	}
	if (uslov[0].size() == 0) {
		for (int i = 0; i < baza.size(); i++) {
			for (int k = 0; k < koji.size(); k++) {
				for (int j = 0; j < baza[i].size(); j++) {
					if (koji[k] == j) {
						//cout << baza[i][j] << "\t";
						*ret += baza[i][j];
						*ret += "\t";
					}
				}
			}
			//cout << endl;
			*ret += "\n";
		}
	}
	else {
		vector<int> kojisu;

		for (int i = 0; i < uslov[0].size(); i++) {
			for (int j = 0; j < imena.size(); j++) {
				if (imena[j] == uslov[0][i]) {
					kojisu.push_back(j);
				}
			}
		}

		vector<int> prolaze;

		for (int i = 0; i < baza.size(); i++) {
			int prolaz = 0;
			for (int j = 0; j < kojisu.size(); j++) {
				if (uslov[1][j] == "=") {
					if (baza[i][kojisu[j]] == uslov[2][j]) {
						prolaz++;
					}
				}
				else if (uslov[1][j] == "<") {
					if (baza[i][kojisu[j]] < uslov[2][j]) {
						prolaz++;
					}
				}
				else if (uslov[1][j] == ">") {
					if (baza[i][kojisu[j]] > uslov[2][j]) {
						prolaz++;
					}
				}
			}
			if (prolaz == kojisu.size()) {
				prolaze.push_back(i);
			}

		}


		for (int i = 0; i < prolaze.size(); i++) {
			for (int k = 0; k < koji.size(); k++) {
				for (int j = 0; j < baza[i].size(); j++) {
					if (koji[k] == j) {
						//cout << baza[prolaze[i]][j] << "\t";
						*ret += baza[prolaze[i]][j];
						*ret += "\t";
					}
				}
			}
			//cout << endl;
			*ret += "\n";
		}

	}
}
void Tabela::delte(vector<vector<string>> uslov)
{
	vector<int> koji;

	for (int i = 0; i < imena.size(); i++) {
		koji.push_back(i);
	}

	vector<vector<string>> bazaTmp;

	vector<int> kojisu;

	for (int i = 0; i < uslov[0].size(); i++) {
		for (int j = 0; j < imena.size(); j++) {
			if (imena[j] == uslov[0][i]) {
				kojisu.push_back(j);
			}
		}
	}

	vector<int> prolaze;

	for (int i = 0; i < baza.size(); i++) {
		int prolaz = 0;
		for (int j = 0; j < kojisu.size(); j++) {
			if (uslov[1][j] == "=") {
				if (baza[i][kojisu[j]] != uslov[2][j]) {
					prolaz++;
				}
			}
			else if (uslov[1][j] == "<") {
				if (baza[i][kojisu[j]] >= uslov[2][j]) {
					prolaz++;
				}
			}
			else if (uslov[1][j] == ">") {
				if (baza[i][kojisu[j]] <= uslov[2][j]) {
					prolaz++;
				}
			}
		}
		if (prolaz == kojisu.size()) {
			prolaze.push_back(i);
		}

	}

	for (int i = 0; i < prolaze.size(); i++) {
		vector<string> tmp;
		for (int k = 0; k < koji.size(); k++) {
			for (int j = 0; j < baza[i].size(); j++) {
				if (koji[k] == j) {
					tmp.push_back(baza[prolaze[i]][j]);
				}
			}
		}
		bazaTmp.push_back(tmp);
	}

	baza.swap(bazaTmp);

}
void Tabela::update(vector<vector<string>> izmenjen, vector<vector<string>> uslov)
{

	vector<int> koji;

	for (int i = 0; i < imena.size(); i++) {
		koji.push_back(i);
	}

	vector<int> kojisu;

	for (int i = 0; i < uslov[0].size(); i++) {
		for (int j = 0; j < imena.size(); j++) {
			if (imena[j] == uslov[0][i]) {
				kojisu.push_back(j);
			}
		}
	}

	vector<int> prolaze;

	for (int i = 0; i < baza.size(); i++) {
		int prolaz = 0;
		for (int j = 0; j < kojisu.size(); j++) {
			if (uslov[1][j] == "=") {
				if (baza[i][kojisu[j]] == uslov[2][j]) {
					prolaz++;
				}
			}
			else if (uslov[1][j] == "<") {
				if (baza[i][kojisu[j]] < uslov[2][j]) {
					prolaz++;
				}
			}
			else if (uslov[1][j] == ">") {
				if (baza[i][kojisu[j]] > uslov[2][j]) {
					prolaz++;
				}
			}
		}
		if (prolaz == kojisu.size()) {
			prolaze.push_back(i);
		}

	}

	//prvu kolonu izmenjen menjamo sa 
	vector<int> izmenjenIndeks;

	for (int i = 0; i < izmenjen[0].size(); i++) {
		int uspeo = 0;
		for (int j = 0; j < imena.size(); j++) {
			if (izmenjen[0][i] == imena[j]) {
				izmenjenIndeks.push_back(j);
				uspeo++;
			}
		}
		if (uspeo == 0) {
			//cout << "Pogresan unos neke kolone pri update-u" << endl;
			*ret += "Pogresan unos neke kolone pri update-u";
			*ret += "\n";
			return;
		}
	}

	for (int i = 0; i < prolaze.size(); i++) {
		for (int k = 0; k < koji.size(); k++) {
			for (int j = 0; j < baza[i].size(); j++) {
				for (int z = 0; z < izmenjenIndeks.size(); z++) {
					if (koji[k] == j && j == izmenjenIndeks[z]) {
						baza[prolaze[i]][j] = izmenjen[2][z];
					}
				}
			}
		}
	}

}
void Tabela::insert(vector<string> kolone, vector<vector<string>> zapisi)
{

	if (kolone.size() > imena.size()) {
		//cout << "Los unos kolona1" << endl;
		*ret += "Los unos kolona1";
		*ret += "\n";
		return;
	}

	for (int i = 0; i < zapisi.size(); i++) {
		if (kolone.size() != zapisi[i].size()) {
			//cout << "Los unos kolona2" << endl;
			*ret += "Los unos kolona2";
			*ret += "\n";
			return;
		}
	}

	vector<int> indeksKolone;

	for (int i = 0; i < kolone.size(); i++) {
		for (int j = 0; j < imena.size(); j++) {
			if (kolone[i] == imena[j]) {
				indeksKolone.push_back(j);
			}
		}
	}

	for (int i = 0; i < zapisi.size(); i++) {
		vector<string> tmp;
		for (int k = 0; k < imena.size(); k++) {
			tmp.push_back("NULL");
		}
		for (int j = 0; j < zapisi[i].size(); j++) {
			tmp[indeksKolone[j]] = zapisi[i][j];
		}
		baza.push_back(tmp);
	}


}
void Tabela::saveTxt(ofstream& out)
{
	out << naziv << "\n";
	out << "-----------------------------\n";
	for (int i = 0; i < imena.size(); i++) {
		out << imena[i] << "\n";
	}
	out << "-----------------------------\n";
	for (int i = 0; i < baza.size(); i++) {
		for (int j = 0; j < baza[i].size(); j++) {
			out << baza[i][j] << "\n";
		}
		if (i != (baza.size() - 1)) {
			out << "-----------------------------\n";
		}
	}
	out << "+++++++++++++++++++++++++++++\n";
}
//////////////////////////sql
void Tabela::saveSql(sqlite3* db, char* errMsg)
{
	string createTable = "CREATE TABLE " + naziv;
	string pom = "(";
	string pom3 = "(";
	for (int i = 0; i < imena.size(); i++) {
		if (i == imena.size() - 1) {
			pom = pom + imena[i] + " CHAR(50) )";
			pom3 = pom3 + imena[i] + " )";
		}
		else {
			pom = pom + imena[i] + " CHAR(50), ";
			pom3 = pom3 + imena[i] + ", ";
		}
	}
	createTable = createTable + pom;
	int rc = sqlite3_exec(db, createTable.c_str(), 0, 0, &errMsg);
	if (rc != SQLITE_OK) {
		cerr << "SQL greska: " << errMsg << endl;
		sqlite3_free(errMsg);
	}

	string insertInto = "INSERT INTO " + naziv + " " + pom3 + " VALUES ";


	for (int i = 0; i < baza.size(); i++) {
		string tmpInsert = insertInto;
		string pom2 = "( ";
		for (int j = 0; j < baza[0].size(); j++) {
			if (j == baza[0].size() - 1) {
				pom2 = pom2 + "'" + baza[i][j] + "')";
			}
			else {
				pom2 = pom2 + "'" + baza[i][j] + "', ";
			}
		}
		tmpInsert = tmpInsert + pom2;
		//cout << tmpInsert << endl;
		rc = sqlite3_exec(db, tmpInsert.c_str(), 0, 0, &errMsg);
		if (rc != SQLITE_OK) {
			cerr << "SQL greska: " << errMsg << endl;
			sqlite3_free(errMsg);
		}
	}


}
//CREATE TABLE TAB1 (A, B, C)
//UPDATE TAB1 SET A = "3" WHERE C = "3"
//UPDATE TAB1 SET C = "3" WHERE C = "3" AND B < "4"
//INSERT INTO TAB1 (A, B, C) VALUES ("3", "2", "3"), ("1", "2", "3"), ("0", "3", "4")