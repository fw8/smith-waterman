/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				main.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte �nderung:	03.09.2018
Beschreibung:		Hauptprogramm zu Versuch 1
******************************************************************************/

#include <string>

#include "Fasta.h"
#include "Alignment.h"

using namespace std;


int main()
{
	Fasta fastaA("Data/testsequenz1.fasta");
	Fasta fastaB("Data/testsequenz2.fasta");

	string seqA = fastaA.GetSequence();
	string seqB = fastaB.GetSequence();

	Alignment alignment(seqA, seqB,-1,0,1);
	alignment.PerformAlignment();

	alignment.PrintScoringMatPretty();
	alignment.PrintTracebackMatPretty();

	string resultA = alignment.GetResultA();
	string resultB = alignment.GetResultB();

	alignment.PrintAlignment();

	return 0;
}
