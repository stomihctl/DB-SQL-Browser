#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>
#include "Baza.h"
#include "JNI.h"

using namespace std;
JNIEXPORT jstring JNICALL Java_javaa_1native_JNI_dajKomandu
(JNIEnv* env, jobject, jstring str, jchar c, jstring str2, jstring str3) {
	
	char dn = static_cast<char>(c);

	string ret;
	string x;

	const char* nativeString = env->GetStringUTFChars(str, nullptr);
	const char* nativeString2 = env->GetStringUTFChars(str2, nullptr);
	const char* nativeString3 = env->GetStringUTFChars(str3, nullptr);
	x = nativeString;

	string txt = nativeString2;
	string sql = nativeString3;

	string x1;
	string x12;
	string x13;
	string x14;
	string x15;
	string x16;
	string x17;
	string x99;
	Baza* baza = new Baza(txt, sql, &ret);

	string odg;
	//cout << "ucitaj staru bazu d/n ";
	//cin >> odg;
	odg = dn;
	if (odg == "d" || odg == "D") {
		baza->ucitajStaru();
	}

	//while (1) {

		//getline(cin, x);
		x1 = x.substr(0, 12);
		x12 = x.substr(0, 10);
		x13 = x.substr(0, 6);
		x14 = x;
		x15 = x.substr(0, 11);
		x16 = x.substr(0, 6);
		x17 = x.substr(0, 11);
		x99 = x.substr(0, 4);
		if (x1 == "CREATE TABLE") {

			regex ct(R"(CREATE TABLE\s+(\w+)\s*\((.*)\))");
			regex strs(R"((\w+))");

			smatch match;

			if (regex_match(x, match, ct)) {
				string createTab = match[0];
				string ime = match[1];

				string columns = match[2];
				vector<string> cols;
				auto words_begin = sregex_iterator(columns.begin(), columns.end(), strs);
				auto words_end = sregex_iterator();

				for (sregex_iterator i = words_begin; i != words_end; ++i) {
					smatch match = *i;
					string match_str = match.str();
					cols.push_back(match_str);
				}

				Tabela* t = new Tabela(cols, ime, &ret);
				baza->dodaj(t);

			}
			else {
				//cout << "Pogresan unos" << endl;
				ret = "Pogresan unos\n";
			}
		}
		else if (x12 == "DROP TABLE") {

			regex dt(R"(DROP TABLE\s+(\w+))");
			string ime;
			smatch match;

			if (regex_match(x, match, dt)) {
				string dropT = match[0];
				ime = match[1];
			}
			else {
				//cout << "Pogresan unos" << endl;
				ret = "Pogresan unos\n";
			}

			baza->ukloni(ime);
		}
		else if (x13 == "SELECT") {
			regex regex("SELECT (.+?) FROM ([a-zA-Z0-9]+)(?: WHERE (.+))?");
			smatch match;

			if (regex_search(x, match, regex)) {
				string kolone = match.str(1);
				string tabela = match.str(2);
				string uslovi = "?";
				if (match.size() > 3) {
					uslovi = match.str(3);
				}
				baza->select(kolone, tabela, uslovi);
			}
			else {
				//cout << "Los unos formata" << endl;
				ret = "Los unos formata\n";
			}
		}
		else if (x14 == "SHOW TABLES") {
			baza->pisiBazu();
		}
		else if (x15 == "DELETE FROM") {
			regex regex("DELETE FROM ([a-zA-Z0-9]+)(?: WHERE (.+))?");
			smatch match;

			if (regex_search(x, match, regex)) {
				string tabela = match.str(1);
				string uslovi = match.str(2);
				baza->del(tabela, uslovi);
			}
			else {
				//cout << "Los unos DELETE" << endl;
				ret = "Los unos DELETE\n";
			}
		}
		else if (x16 == "UPDATE") {
			regex regex("UPDATE ([a-zA-Z0-9]+) SET (.+) WHERE (.+)");
			smatch match;

			if (regex_search(x, match, regex)) {
				string tabela = match.str(1);
				string izmene = match.str(2);
				string uslovi = match.str(3);
				baza->update(tabela, izmene, uslovi);
			}
			else {
				//cout << "Los unos UPDATE naredbe" << endl;
				ret = "Los unos UPDATE naredbe\n";
			}
		}
		else if (x17 == "INSERT INTO") {
			regex regex(R"((INSERT INTO (\w+)\s*\(([\w\s,]+)\)\s*VALUES\s*((\((?:"[^"]*"\s*,?\s*)+\),?\s*)+)))");

			smatch match;

			if (regex_search(x, match, regex)) {
				string tabela = match.str(2);
				string listaKolona = match.str(3);
				string listaZapisa = match.str(4);
				baza->insert(tabela, listaKolona, listaZapisa);
			}
			else {
				//cout << "Los unos INSERT INTO naredbe" << endl;
				ret = "Los unos INSERT INTO naredbe\n";
			}
		}
		else if (x == "SAVE TXT") {

			baza->saveTxt();
		}
		else if (x == "SAVE SQL") {
			baza->saveSql();
		}

		baza->saveTxt();
		env->ReleaseStringUTFChars(str, nativeString);
		env->ReleaseStringUTFChars(str2, nativeString2);
		env->ReleaseStringUTFChars(str3, nativeString3);

		jstring jret = env->NewStringUTF(ret.c_str());
		return jret;
}

JNIEXPORT jstring JNICALL Java_javaa_1native_JNI_citajTabele
(JNIEnv* env, jobject, jstring str2, jstring str3) {
	string ret;
	string x = "SHOW TABLES";

	const char* nativeString2 = env->GetStringUTFChars(str2, nullptr);
	const char* nativeString3 = env->GetStringUTFChars(str3, nullptr);

	string txt = nativeString2;
	string sql = nativeString3;

	Baza* baza = new Baza(txt, sql, &ret);

	string odg;
	//cout << "ucitaj staru bazu d/n ";
	//cin >> odg;
	odg = 'd';
	if (odg == "d" || odg == "D") {
		baza->ucitajStaru();
	}

	if (x == "SHOW TABLES") {
		baza->pisiBazu();
	}
	else {
		ret = "";
	}

	env->ReleaseStringUTFChars(str2, nativeString2);
	env->ReleaseStringUTFChars(str3, nativeString3);

	jstring jret = env->NewStringUTF(ret.c_str());
	return jret;
}