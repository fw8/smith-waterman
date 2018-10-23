/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				BaseAlignment.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte �nderung:	03.09.2018
Beschreibung:		Basisklasse zur Berechnung eines Alignments
******************************************************************************/

#pragma once

#include <string>

#include "Matrix.h"


class BaseAlignment
{
public:
	BaseAlignment();
	~BaseAlignment();

	// Setzen der Parameter f�r "gap penalty", "mismatch" und "match"
	void SetParams(int gapPen, int mismat, int mat);

	// Ausgabe des Scoring-Matrix auf der Kommandozeile
	void PrintScoringMat();
	void PrintScoringMatPretty();

	// Ausgabe des Traceback-Matrix auf der Kommandozeile
	void PrintTracebackMat();
	void PrintTracebackMatPretty();

	// Ausgabe der Scoring-Matrix in die Datei "scoringMat.txt"
	void WriteScoringMat();

	// R�ckgabe der resultierenden Sequenz A
	std::string GetResultA();

	// R�ckgabe der resultierenden Sequenz B
	std::string GetResultB();

	// Ausgabe des resultierenden Alignments auf der Kommandozeile
	void PrintAlignment();

protected:
	Matrix<int>  F;
	Matrix<char> Z;
	int gapPenalty;
	int mismatch;
	int match;
	std::string seqA;
	std::string seqB;
	std::string resultA;
	std::string resultB;
};
