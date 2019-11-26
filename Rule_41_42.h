#pragma once
#include <math.h>
#include "Curves.h"
double Addict_l1(double p, double p5, double u5, double c5, double gamma1, double ro5)
{
	double u = 0;
	if (p <= p5)
	{
		u = u5 + (2 / (gamma1 - 1))*c5*(pow((p / p5), ((gamma1 - 1) / (2 * gamma1))) - 1);
	}
	else
	{
		u = u5 + (p - p5)*sqrt(((1 - muiquadr(gamma1))*taui(ro5)) / (p + muiquadr(gamma1)*p5));
	}
	return u;
}