/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				BaseAlignment.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte �nderung:	03.09.2018
Beschreibung:		Basisklasse zur Berechnung eines Alignments
******************************************************************************/

#include "BaseAlignment.h"

#include <iostream>

using namespace std;


BaseAlignment::BaseAlignment()
{
}
BaseAlignment::~BaseAlignment()
{
}


void BaseAlignment::SetParams(int gapPen, int mismat, int mat)
{
	gapPenalty	= gapPen;
	mismatch	= mismat;
	match		= mat;
}

void BaseAlignment::PrintScoringMat()
{
	cout << "Die Scoring-Matrix lautet: " << endl;
	F.Print();
	cout << endl;
}

void BaseAlignment::PrintScoringMatPretty()
{
	cout << "Die Scoring-Matrix lautet: " << endl;
	cout << "\t";
	for (unsigned int c = 0; c < F.GetNumCols(); c++)
	{
		cout << "\t" << seqA[c];
	}
	cout << "\n";
	for (unsigned int r = 0; r < F.GetNumRows(); r++)
	{
		for (unsigned int c = 0; c < F.GetNumCols(); c++)
		{
			if (c == 0)
			{
				if (r == 0) cout << " ";
				else cout << seqB[r - 1];
			}
			std::cout << "\t" << F.At(r, c);
		}
		cout << "\n";
	}
	cout << "\n";
}

void BaseAlignment::PrintTracebackMat()
{
	cout << "Die Traceback-Matrix lautet: " << endl;
	Z.Print();
	cout << endl;
}

void BaseAlignment::PrintTracebackMatPretty()
{
	cout << "Die Traceback-Matrix lautet: " << endl;
	cout << "\t";
	for (unsigned int c = 0; c < Z.GetNumCols(); c++)
	{
		cout << "\t" << seqA[c];
	}
	cout << "\n";
	for (unsigned int r = 0; r < Z.GetNumRows(); r++)
	{
		for (unsigned int c = 0; c < Z.GetNumCols(); c++)
		{
			if (c == 0)
			{
				if (r == 0) cout << " ";
				else cout << seqB[r - 1];
			}
			std::cout << "\t" << Z.At(r, c);
		}
		cout << "\n";
	}
	cout << "\n";
}


void BaseAlignment::WriteScoringMat()
{
	ofstream o("scoringMat.txt");
	if (o.is_open())
	{
		F.Write(o);
	}
}

string BaseAlignment::GetResultA()
{
	return resultA;
}

string BaseAlignment::GetResultB()
{
	return resultB;
}

void BaseAlignment::PrintAlignment()
{
	string vis;
	for (unsigned int i = 0; i < resultA.length(); i++)
	{
		if (resultA.substr(i, 1) == resultB.substr(i, 1))
			vis.append("|");
		else
			vis.append(" ");
	}
	cout << "Resultierendes Alignment:" << endl;
	cout << resultA << endl << vis << endl << resultB << endl;
	cout << endl;
}
