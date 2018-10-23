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

void Alignment::CalcCell(int r, int c)
{
	int f1,f2,f3,f;
	char z='x';

//cout << r << "," << c << endl;

	// Erst die zwei Spezialfaelle abhandel (Rand)...
	if ((r == 0) || (c == 0)) {
		f = 0;

	} else { // Dann den normalen Rekursionsschritt durch Rückgriff auf schon berechnete Zellen

		// Achtung! seqA[c-1] weil die Matrix bei (0,0) eine Spalte/Zeile mehr hat, die Sequenz aber nicht.
		f1 = F.At(r-1,c-1) + Score(seqA[c-1],seqB[r-1]); // Match/Missmatch
		f2 = F.At(r-1,c) + gapPenalty; // Loeschung (vertikale Bewegung)
		f3 = F.At(r,c-1) + gapPenalty;  // Einfuegung (horizontale Bewegung)

		// Maximum der drei (vier) Varianten ermitteln
		f = max((max(max(f1,f2),f3)),0);

		// Zeiger entsprechend dem gefundenen Maximum setzten

		if (f==f2) {z='U';}
		if (f==f3) {z='L';}
		if (f==f1) {z='D';} // nach hinten damit D bei Gleichstand gewinnt!

		//cout << "f1,2,3 = (" << f1 << "),(" << f2 << "),(" << f3 << ")" << endl;
		//cout << "f=" << f << " -> " << z << endl << endl;

		//F.SetValue(r,c,-1);
		//PrintScoringMatPretty();

	}

	F.SetValue(r,c,f);
	Z.SetValue(r,c,z);
}

void Alignment::FillMats()
{
	// Zeilen und Spaltenweise die Zellen berechnen (iterativ!)
	for (int r = 0; r < F.GetNumRows(); r++) {
		for (int c = 0; c < F.GetNumCols(); c++) {
			CalcCell(r,c);
			// cout << "berechne " << r << "," << c << " "
		}
	}

}

void Alignment::TraceBack()
{
	size_t r,c;
	char z,charA,charB;

  F.MaxPos(r,c);

	// cout << "max pos: " << r << ", " << c << " = " << F.At(r,c) << endl;

	while (F.At(r,c) != 0) {

		z = Z.At(r,c);

		if (z == 'L') {
			charA = seqA[c-1]; charB = '-';
			c--;
		} else if (z == 'U') {
			charA = '-'; charB = seqB[r-1];
			r--;
		} else if (z == 'D') { // Eigentlich einzige moegliche Variante!?
			charA = seqA[c-1]; charB = seqB[r-1];
			r--; c--;
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
