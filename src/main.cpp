/**
 * Sillabatore da riga di comando per Linux
 * Creato da G.Capelli il 29/7/2017
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <algorithm>

using namespace std;


string pattern[500];			// L'array che contiene i pattern di sillabazione
short pattern_values[500][15];
string pattern_string[500];
string numbers = "0123456789";
int nPatterns = 0;
bool isVerbose = false;			// Opzione che indica se vizualizzare le regole di sillabazione


// La funzione carica i pattern di sillabazione dal file hyph_it_IT.dic
// e li inserisce nell'array dei Pattern;
void LoadPatterns(string dicfile)
{
	ifstream patternFile(dicfile);
    string singleExpr;
	int lineNumber = -1;
	if (patternFile.is_open()) {
		while (getline(patternFile, singleExpr)) { // Gets a full line from the file
			if (lineNumber >= 0) {	// Scarta la prima riga, che contiene la codifica ISO
				pattern[lineNumber] = singleExpr;

				//cout << singleExpr << " - ";

				unsigned int ii = 0;
				unsigned int iv = 0;

				for (ii = 0; ii < pattern[lineNumber].size(); ii++) {
					if (numbers.find(pattern[lineNumber][ii]) != string::npos) {	// Number found
						pattern_values[lineNumber][iv] = stoi(pattern[lineNumber].substr(ii,1));
					} else {														// Letter found
						iv++;
						pattern_values[lineNumber][iv] = 0;
						pattern_string[lineNumber] += pattern[lineNumber].substr(ii,1);
					}
				}
				//for (ii = 0; ii <= iv; ii++) cout << pattern_values[lineNumber][ii];
				//cout << " - " << pattern_string[lineNumber] << "\n";
			}
			lineNumber++;
		}
		patternFile.close();
	}
	nPatterns = lineNumber;
}


void Sillaba(string mparola)
{
	string parola = "." + mparola + ".";
	short parola_values[parola.size() + 1];

	if (isVerbose) cout << "\n  " << mparola << "\n----------------------------------------------\n";
	for (int ii = 0; ii < parola.size() + 1; ii++) {
		parola_values[ii] = 0;
		if (isVerbose) cout << parola_values[ii];
	}
	if (isVerbose) cout << "\n\n";

	if (nPatterns > 1) {		// Controlla che siano stati caricati i pattern
		for (int i = 0; i < nPatterns; i++) {		// Ripete per ogni pattern caricato
			string sparola = parola;
			int ifound = sparola.rfind(pattern_string[i]);
			while (ifound != string::npos) {		// Finchè trova delle occorrenze
				if (isVerbose) {
					for (int ii = 0; ii < ifound + 1; ii++) cout << " ";
					cout << pattern_string[i] << "\n";
					for (int ii = 0; ii < ifound; ii++) cout << " ";
				}
				for (int ii = 0; ii <= pattern_string[i].size(); ii++) {
					if (isVerbose) cout << pattern_values[i][ii];
					if (parola_values[ii + ifound] < pattern_values[i][ii]) parola_values[ii + ifound] = pattern_values[i][ii];
				}
				if (isVerbose) cout << "\n";
				// Cerca la prossima occorrenza
				sparola = parola.substr(0,ifound);
				ifound = sparola.rfind(pattern_string[i]);
			}
		}
	}
	if (isVerbose) {
		cout << "\n\n";
		for (int ii = 0; ii < parola.size() + 1; ii++) cout << parola_values[ii];	// Stampa i valori finali
		cout << "\n----------------------------------------------\n";
	}
	
	string parolasillabata;
	for (int ii = 1; ii < parola.size()-1; ii++) {		// Stampa la parola con sillabazione
		parolasillabata += parola[ii];
		if (parola_values[ii+1] % 2) parolasillabata += " ";
	}
	if (isVerbose) cout << "  ";
	cout << parolasillabata << "\n";
	if (isVerbose) cout << "\n";

}


static void show_usage(std::string name)
{
	std::cerr 	<< "\nUso: " << name << " [OPZIONI] parola_da_sillabare\n"
				<< "\nIl programma divide in sillabe la parola in ingresso\nutilizzando il file delle regole di LibreOffice hyph_it_IT.dic,\nche deve essere presente nella cartella del file eseguibile.\n"
				<< "E' possibile scaricare il file delle regole al seguente link:\nhttps://raw.githubusercontent.com/LibreOffice/dictionaries/master/it_IT/hyph_it_IT.dic\n\n"
				<< "Opzioni:\n"
				<< "\t-h,--help\t\tVisualizza questo messaggio di aiuto\n"
				<< "\t-v,--verbose\t\tVisualizza tutte le regole applicate\n"
				<< "\t--version\t\tRestituisce il numero di versione del programma\n"
				<< std::endl;
}


int main(int argc, char **argv)
{
	string parola = "";

	if (argc < 2) {
        show_usage(argv[0]);
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {				// Visualizza help
            show_usage(argv[0]);
            return 0;
        } else if ((arg == "-v") || (arg == "--verbose")) {		// Visualizza regole di sillabazione
			isVerbose = true;
		} else if (arg == "--version") {						// Visualizza la versione dell'applicazione
			cerr << "\nSillabatore v1.01 (03/05/2020)\n"
				 << "Copyright © 2019 Graziano Capelli.\n\n"
				 << "Licenza GPLv3+: GNU GPL version 3 o successiva <https://gnu.org/licenses/gpl.html>.\n"
				 << "This is free software: you are free to change and redistribute it.\n"
				 << "There is NO WARRANTY, to the extent permitted by law.\n\n";
			return 0;
		} else if (arg.at(0) != '-') {
			parola = arg;
			// convert string to back to lower case
			std::for_each(parola.begin(), parola.end(), [](char & c) {
				c = ::tolower(c);
			});
		}
    }
	
	if (parola != "") {
		LoadPatterns("./hyph_it_IT.dic");
		Sillaba(parola);
	} else {
		show_usage(argv[0]);
	}

	return 0;
}
