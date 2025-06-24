#include "Tabela.h"


using namespace std;

class Baza {
private:
	vector<Tabela*> niz;
	//novo
	string txt;
	string sql;
	string* ret;
public:
	Baza(string txt, string sql, string* ret);

	void dodaj(Tabela* t);
	void ukloni(string ime);
	void pisiBazu();
	void select(string kolone, string tabela, string uslovi);
	void del(string tabela, string uslovi);
	void update(string tabela, string izmene, string uslovi);
	void insert(string tabela, string listaKolona, string listaZapisa);
	void saveTxt();
	void ucitajStaru();
	void saveSql();

};
