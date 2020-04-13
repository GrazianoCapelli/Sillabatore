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

using namespace std;


string pattern[500];	// L'array che contiene i pattern di sillabazione
short pattern_values[500][15];
string pattern_string[500];
string numbers = "0123456789";
int nPatterns = 0;

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

	cout << "\n  " << mparola << "\n----------------------------------------------\n";
	for (int ii = 0; ii < parola.size() + 1; ii++) {
		parola_values[ii] = 0;
		cout << parola_values[ii];
	}
	cout << "\n\n";

	if (nPatterns > 1) {		// Controlla che siano stati caricati i pattern
		for (int i = 0; i < nPatterns; i++) {		// Ripete per ogni pattern caricato
			string sparola = parola;
			int ifound = sparola.rfind(pattern_string[i]);
			while (ifound != string::npos) {		// Finchè trova delle occorrenze
				for (int ii = 0; ii < ifound + 1; ii++) cout << " ";
				cout << pattern_string[i];
				cout << "\n";
				for (int ii = 0; ii < ifound; ii++) cout << " ";
				for (int ii = 0; ii <= pattern_string[i].size(); ii++) {
					cout << pattern_values[i][ii];
					if (parola_values[ii + ifound] < pattern_values[i][ii]) parola_values[ii + ifound] = pattern_values[i][ii];
				}
				cout << "\n";
				// Cerca la prossima occorrenza
				sparola = parola.substr(0,ifound);
				ifound = sparola.rfind(pattern_string[i]);
			}
		}
	}
	cout << "\n\n";
	for (int ii = 0; ii < parola.size() + 1; ii++) cout << parola_values[ii];	// Stampa i valori finali
	cout << "\n----------------------------------------------\n";

	string parolasillabata;
	for (int ii = 1; ii < parola.size()-1; ii++) {		// Stampa la parola con sillabazione
		parolasillabata += parola[ii];
		if (parola_values[ii+1] % 2) parolasillabata += " ";
	}
	cout << "  " << parolasillabata << "\n\n";

}


int main(int argc, char **argv)
{
	if (argc > 0) {
		string parola = argv[1];

		LoadPatterns("../hyph_it_IT.dic");
		//Sillaba(parola);
		Sillaba(parola);
	}

	return 0;
}
