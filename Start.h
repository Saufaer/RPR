#pragma once
#include <string>
#include <fstream>
struct Point
{
	double p;
	double u;
};

struct TwoPoints
{
	Point NL2;
	Point NL1;
};

struct START
{
	double A2;
	double A1;

	double p2;
	double p1;

	double u2;
	double u1;

	double c2;
	double c1;

	double ro2;
	double ro1;

	double gamma2;
	double gamma1;
};

void Write(string str, string file, int i)
{
	ofstream output;
	
	output.open(to_string(i)+"\\"+file,ios_base::app);
	output << str;
	output.close();
}