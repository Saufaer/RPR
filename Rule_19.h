#pragma once
#include<math.h>
double Addict_l2(double p, double p4, double u4, double c4, double gamma2)
{
	double u = u4 - (2 / (gamma2 - 1))*c4*(pow((p / p4), ((gamma2 - 1) / (2 * gamma2))) - 1);
	return u;
}