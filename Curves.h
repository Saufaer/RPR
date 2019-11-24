#include <math.h>
#include "Rule_6_7_8.h"
#include "Rule_15.h"
#include "Rule_19.h"
#include <iostream>
#ifndef Curves

//Curves (12,13)
double muiquadr(double gammai)
{
	return((gammai - 1) / (gammai + 1));
}

double taui(double roi)
{
	return (1 / roi);
}

double PSIi(double p, double pi, double gammai, double gamma2, double ci)
{
	return (2 / (gamma2 - 1))*ci*(pow((p / pi), ((gammai - 1) / (2 * gammai))) - 1);
}

double FIi(double p, double pi, double roi, double gammai)
{
	return (p - pi)*sqrt((1 - muiquadr(gammai)*muiquadr(gammai))*taui(roi) / (p + muiquadr(gammai)*muiquadr(gammai)*pi));
};

double L1(double p, double u1, double p1, double ro1, double gamma1, double gamma2, double c1)
{
	double u = 0;
	if (p >= p1) { u = u1 + FIi(p, p1, ro1, gamma1); }
	if (p <= p1) { u = u1 + PSIi(p, p1, gamma1, gamma2, c1); }
	return u;

};
double L2(double p, double u2, double p2, double ro2, double gamma2, double c2)
{
	double u = 0;
	if (p >= p2) { u = u2 - FIi(p, p2, ro2, gamma2); }
	if (p <= p2) { u = u2 - PSIi(p, p2, gamma2, gamma2, c2); }
	return u;
};

#endif 