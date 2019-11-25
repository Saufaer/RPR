#pragma once
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
	double gamma2 = 1.1;
	double gamma1 = 1.1;

	double p1 = 100000;
	double p2 = 100000;

	double u1 = -60;
	double u2 = -60;

	double c1 = 343;
	double c2 = 343;

	double ro1 = 0.5;
	double ro2 = 0.5;

	double A1 = 100;
	double A2 = 200;
};
