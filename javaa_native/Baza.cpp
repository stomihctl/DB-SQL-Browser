#include "Baza.h"



Baza::Baza(string txt, string sql, string* ret)
{
	this->txt = txt;
	this->sql = sql;
	this->ret = ret;
}

void Baza::dodaj(Tabela* t)
{
	//for (int i = 0; i < niz.size(); i++) {
	for (auto i = niz.begin(); i != niz.end(); i++) {
		if (t->getNaziv() == (*i)->getNaziv()) {
			//cout << "Greska, tabela vec postoji" << endl;
			*ret += "Greska, tabela vec postoji";
			*ret += "\n";
			return;
		}
	}

	niz.push_back(t);

}

void Baza::ukloni(string ime)
{
	for (int i = 0; i < niz.size(); i++) {
		//for (auto i = niz.begin(); i != niz.end(); i++) {
		if (ime == niz[i]->getNaziv()) {
			//cout << "true" << endl;
			*ret += "true";
			*ret += "\n";
			niz.erase(niz.begin() + i);
			//cout << "Tabela uspesno obrisana" << endl;
			*ret += "Tabela uspesno obrisana";
			*ret += "\n";
			return;
		}
	}
	cout << "Tabela nije pronadjena" << endl;
}

void Baza::pisiBazu()
{
	for (int i = 0; i < niz.size(); i++) {
		//cout << "-----------------------" << endl;
		*ret += "-----------------------";
		*ret += "\n";
		//cout << niz[i]->getNaziv() << endl;
		*ret += niz[i]->getNaziv();
		*ret += "\n";
		//cout << "-----------------------" << endl;
		*ret += "-----------------------";
		*ret += "\n";
		niz[i]->pisi();
		//cout << "-----------------------" << endl;
		*ret += "-----------------------";
		*ret += "\n";
	}
}

void Baza::select(string kolone, string tabela, string uslovi)
{
	vector<string> selektor;
	string part;
	istringstream stream(kolone);

	while (getline(stream, part, ',')) {
		size_t first = part.find_first_not_of(' ');
		size_t last = part.find_last_not_of(' ');
		if (first != string::npos && last != string::npos) {
			selektor.push_back(part.substr(first, last - first + 1));
		}
	}

	//uslovi where lista_uslova
	vector<vector<string>> uslov(3);
	if (uslovi != "?") {

		regex p("(\\w+)\\s*(=|>|<)\\s*\"(\\w+)\"");

		auto condition_begin = sregex_iterator(uslovi.begin(), uslovi.end(), p);
		auto condition_end = sregex_iterator();

		for (auto i = condition_begin; i != condition_end; ++i) {
			smatch match = *i;

			string ime = match[1];
			string op = match[2];
			string vred = match[3];

			uslov[0].push_back(ime);
			uslov[1].push_back(op);
			uslov[2].push_back(vred);
		}
	}
	//selektor i uslov
	//cout << "VEL US " << uslov[0].size() << endl;
	//for (int i = 0; i < niz.size(); i++) {
	for (auto i = niz.begin(); i != niz.end(); i++) {
		if ((*i)->getNaziv() == tabela) {
			(*i)->select(selektor, uslov);
			return;
		}
	}
	//cout << "Nepostojeca tabela" << endl;
	*ret += "Nepostojeca tabela";
	*ret += "\n";
}

void Baza::del(string tabela, string uslovi)
{
	vector<vector<string>> uslov(3);

	regex p("(\\w+)\\s*(=|>|<)\\s*\"(\\w+)\"");

	auto condition_begin = sregex_iterator(uslovi.begin(), uslovi.end(), p);
	auto condition_end = sregex_iterator();

	for (auto i = condition_begin; i != condition_end; ++i) {
		smatch match = *i;

		string ime = match[1];
		string op = match[2];
		string vred = match[3];

		uslov[0].push_back(ime);
		uslov[1].push_back(op);
		uslov[2].push_back(vred);
	}

	//for (int i = 0; i < niz.size(); i++) {
	for (auto i = niz.begin(); i != niz.end(); i++) {
		if ((*i)->getNaziv() == tabela) {
			(*i)->delte(uslov);
			return;
		}
	}
	//cout << "Nepostojeca tabela" << endl;
	*ret += "Nepostojeca tabela";
	*ret += "\n";
}

void Baza::update(string tabela, string izmene, string uslovi)
{

	vector<vector<string>> uslov(3);

	regex p("(\\w+)\\s*(=|>|<)\\s*\"(\\w+)\"");

	auto condition_begin = sregex_iterator(uslovi.begin(), uslovi.end(), p);
	auto condition_end = sregex_iterator();

	for (auto i = condition_begin; i != condition_end; ++i) {
		smatch match = *i;

		string ime = match[1];
		string op = match[2];
		string vred = match[3];

		uslov[0].push_back(ime);
		uslov[1].push_back(op);
		uslov[2].push_back(vred);
	}

	//gore uslovi standardno moze se smestiti u funkciju

	vector<vector<string>> izmenjen(3);

	regex q("(\\w+)\\s*(=|>|<)\\s*\"(\\w+)\"");

	auto condition_begin2 = sregex_iterator(izmene.begin(), izmene.end(), q);
	auto condition_end2 = sregex_iterator();

	for (auto i = condition_begin2; i != condition_end2; ++i) {
		smatch match = *i;

		string ime = match[1];
		string op = match[2];
		string vred = match[3];

		izmenjen[0].push_back(ime);
		izmenjen[1].push_back(op);
		izmenjen[2].push_back(vred);
	}

	//gore su izmene koje treba napraviti

	//for (int i = 0; i < niz.size(); i++) {
	for (auto i = niz.begin(); i != niz.end(); i++) {
		if ((*i)->getNaziv() == tabela) {
			(*i)->update(izmenjen, uslov);
			return;
		}
	}
	//cout << "Nepostojeca tabela" << endl;
	*ret += "Nepostojeca tabela";
	*ret += "\n";

}

void Baza::insert(string tabela, string listaKolona, string listaZapisa)
{

	vector<string> kolone;
	string part;
	istringstream stream(listaKolona);

	while (getline(stream, part, ',')) {
		size_t first = part.find_first_not_of(' ');
		size_t last = part.find_last_not_of(' ');
		if (first != string::npos && last != string::npos) {
			kolone.push_back(part.substr(first, last - first + 1));
		}
	}

	vector<vector<string>> zapisi;
	stringstream ss(listaZapisa);

	char c;
	while (ss >> c) {
		if (c == '(') {
			vector<string> temp;
			string value;
			while (ss >> c && c != ')') {
				if (c == '"') {
					getline(ss, value, '"');
					temp.push_back(value);
				}
			}
			zapisi.push_back(temp);
		}
	}

	//gotovo isecanje
	//kolone i zapisi
	//for (int i = 0; i < niz.size(); i++) {
	for (auto i = niz.begin(); i != niz.end(); i++) {
		if ((*i)->getNaziv() == tabela) {
			(*i)->insert(kolone, zapisi);
			return;
		}
	}
	//cout << "Nepostojeca tabela" << endl;
	*ret += "Nepostojeca tabela";
	*ret += "\n";

}

void Baza::saveTxt()
{
	//ofstream out("C:/Users/PC/Desktop/baza.txt");
	ofstream out(txt);
	if (out.is_open()) {
		for (int i = 0; i < niz.size(); i++) {
			niz[i]->saveTxt(out);
		}
	}
	else {
		//cout << "fajl nije otvoren" << endl;
		*ret += "fajl nije otvoren";
		*ret += "\n";
	}
	out.close();
}

void Baza::ucitajStaru()
{

	//ifstream in("C:/Users/PC/Desktop/baza.txt");
	ifstream in(txt);
	string s;
	string ime;
	int brojac = 0;
	int duz = 0;
	bool pocetakDuzi = false;
	int velDuzi = 0;
	vector<string> cols;
	bool kupiClanove = false;
	Tabela* tmp = NULL;
	vector<string> clanoviZapisa;
	vector<vector<string>> zapisi;
	while (getline(in, s)) {
		brojac++;
		duz++;
		if (brojac == 1) {
			ime = s;
		}
		if (brojac == 2 && s == "-----------------------------") {
			duz = 0;
			pocetakDuzi = true;
		}
		if (duz > 0 && pocetakDuzi == true && s == "-----------------------------") {
			pocetakDuzi = false;
			velDuzi = duz - 1;
			Tabela* t = new Tabela(cols, ime, ret);
			this->dodaj(t);
			tmp = t;
			kupiClanove = true;
			duz = 0;
		}
		if (pocetakDuzi == true && duz > 0) {
			cols.push_back(s);
		}
		//kupimo clanove
		if (duz > 0 && kupiClanove == true && duz < (velDuzi + 1)) {
			clanoviZapisa.push_back(s);
		}
		if (kupiClanove == true && duz == (velDuzi + 1)) {
			duz = 0;
			zapisi.push_back(clanoviZapisa);
			clanoviZapisa.clear();
		}
		if (s == "+++++++++++++++++++++++++++++") {
			tmp->insert(cols, zapisi);
			brojac = 0;
			duz = 0;
			pocetakDuzi = false;
			velDuzi = 0;
			cols.clear();
			kupiClanove = false;
			tmp = NULL;
			clanoviZapisa.clear();
			//zapisi
			for (int i = 0; i < zapisi.size(); i++) {
				zapisi[i].clear();
			}
			zapisi.clear();
		}

	}
	/*cout << ime << endl;
	cout << brojac << endl;
	cout << velDuzi << endl;
	tmp->pisi();*/
}
////////////////sql
void Baza::saveSql()
{

	//if (remove("C:/Users/PC/Desktop/baza.db") == 0) {
	if (remove(sql.c_str()) == 0) {
		//cout << "Stara baza uspesno obrisana" << std::endl;
		*ret += "Stara baza uspesno obrisana";
		*ret += "\n";
	}
	else {
		//cout << "Greska pri brisanju stare baze" << std::endl;
		*ret += "Greska pri brisanju stare baze";
		*ret += "\n";
	}

	sqlite3* db;
	char* errMsg = 0;
	//int rc = sqlite3_open("C:/Users/PC/Desktop/baza.db", &db);
	int rc = sqlite3_open(sql.c_str(), &db);
	if (rc) {
		//cout << "Baza nije uspesno otvorena" << endl;
		*ret += "Baza nije uspesno otvorena";
		*ret += "\n";
	}
	for (int i = 0; i < niz.size(); i++) {
		niz[i]->saveSql(db, errMsg);
	}
	sqlite3_close(db);
}
