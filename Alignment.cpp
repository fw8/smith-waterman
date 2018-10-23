/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:		Alignment.cpp
Autoren:	Sascha Seifert, Max Barchet, Joachim Storz, Carlotta Rödling
Letzte Änderung:23.10.2018
Beschreibung:	Klasse zur Berechnung eines Alignements
******************************************************************************/

#include "Alignment.h"
#include <algorithm>    // std::max

using namespace std;


Alignment::Alignment(string sequenceA, string sequenceB, int gapPen, int mismat, int mat)
{
	seqA = sequenceA;
	seqB = sequenceB;
	gapPenalty	= gapPen;
	mismatch	= mismat;
	match		= mat;
	F.SetSize(seqB.size()+1, seqA.size()+1);
	Z.SetSize(seqB.size()+1, seqA.size()+1);
}

Alignment::~Alignment()
{
}

int Alignment::Score(char a, char b)
{
	// cout << "compare " << a << " with " << b << endl;
	if (a == b) {
		return (match);
	} else {
		return (mismatch);
	}
}

void Alignment::CalcCell(int i, int j)
{
	int f1,f2,f3,f;
	char z='x';

//cout << i << "," << j << endl;

	// Erst die zwei Spezialfaelle abhandel (Rand)...
	if ((i == 0) || (j == 0)) {
		f = 0;

	} else { // Dann den normalen Rekursionsschritt durch Rückgriff auf schon berechnete Zellen

		// Achtung! seqA[i-1] ist das i-te Element der Zeichenkette seqA (weil seqA[1] das erste ist!)
		// Die Matrix hat bei (0,0) eine Zeile/Spalte mehr!
		f1 = F.At(i-1,j-1) + Score(seqA[j-1],seqB[i-1]); // Match/Missmatch
		f2 = F.At(i-1,j) + gapPenalty; // Loeschung
		f3 = F.At(i,j-1) + gapPenalty;  // Einfuegung

		// Maximum der drei (vier) Varianten ermitteln
		f = max((max(max(f1,f2),f3)),0);

		// Zeiger entsprechend dem gefundenen Maximum setzten

		if (f==f2) {z='L';}
		if (f==f3) {z='U';}
		if (f==f1) {z='D';} // nach hinten damit D bei Gleichstand gewinnt!

		//cout << "f1,2,3 = (" << f1 << "),(" << f2 << "),(" << f3 << ")" << endl;
		//cout << "m=" << m << " -> " << d << endl << endl;

		//F.SetValue(i,j,-1);
		//PrintScoringMatPretty();

	}

	F.SetValue(i,j,f);
	Z.SetValue(i,j,z);
}

void Alignment::FillMats()
{
	// Zeilen und Spaltenweise die Zellen berechnen (iterativ!)
	for (int i = 0; i < (seqB.size()+1); i++) {
		for (int j = 0; j < (seqA.size()+1); j++) {
			CalcCell(i,j);
			// cout << "berechne " << i << "," << j << " "
		}
	}

}

void Alignment::TraceBack()
{
	size_t i,j;
	char z,charA,charB;

  F.MaxPos(i,j);

	// cout << "max pos: " << i << ", " << j << " = " << F.At(i,j) << endl;

	while (F.At(i,j) != 0) {

		z = Z.At(i,j);

		if (z == 'L') {
			charA = seqA[j-1]; charB = '-';
			j--;
		} else if (z == 'U') {
			charA = '-'; charB = seqB[i-1];
			i--;
		} else if (z == 'D') { // Eigentlich einzige moegliche Variante!?
			charA = seqA[j-1]; charB = seqB[i-1];
			j--; i--;
		} else {
			// ende
			break;
		}

		resultA = charA + resultA;
		resultB = charB + resultB;
	}


}

void Alignment::PerformAlignment()
{
	FillMats();
	TraceBack();
}
