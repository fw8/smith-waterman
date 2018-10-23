/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Alignment.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte �nderung:	03.09.2018
Beschreibung:		Klasse zur Berechnung eines Alignements
					Template f�r Studierende
******************************************************************************/

#pragma once

#include <string>

#include "BaseAlignment.h"
#include "Matrix.h"


class Alignment : public BaseAlignment
{
public:
	Alignment(std::string sequenceA, std::string sequenceB, int gapPen = -1, int mismat = -1, int mat = 2);
	~Alignment();

	void PerformAlignment();

private:
	int Score(char a, char b);
	void FillMats();
	void CalcCell(int i, int j);
	void TraceBack();

};
