#pragma once
#include <math.h>
#ifndef RULE_33_34_35
#define RULE_33_34_35

double ALPHA2(double A1, double A2)
{
	double alpha = A1 / A2;
	return alpha;
}

double A1( double c4quadr, double gamma1, double u4)
{
	double a1 = c4quadr + gamma1 * pow(u4, 2);
	return a1;
}

double C4QUADR(double gamma1, double ro4, double p4)
{
	double c4quadr = gamma1 * (p4 / ro4);
	return c4quadr;
}

double DELTA(double c4quadr, double gamma1, double alpha, double u4)
{
	double delta = pow((c4quadr - (gamma1 - (gamma1 - 1)*alpha)*pow(u4, 2)), 2) + 2 * (1 - alpha)*(2 * gamma1 - (gamma1 - 1)*alpha)*c4quadr*pow(u4, 2);
	return delta;
}

double RO5(double ro4, double alpha, double u4, double u5)
{
	double ro5 = ro4 * (alpha*u4) / (u5);
	return ro5;
}

double U5_33(double u4, double a1, double Delta, double gamma1, double alpha)
{
	double u5 = (a1 + sqrt(Delta)) / ((2 * gamma1 - (gamma1 - 1)*alpha)*u4);
	return u5;
}

double U5_34(double u4, double a1, double Delta, double gamma1, double alpha)
{
	double u5 = (a1 - sqrt(Delta)) / ((2 * gamma1 - (gamma1 - 1)*alpha)*u4);
	return u5;
}

double P5(double p4, double u4, double u5, double ro4)
{
	double p5 = p4 + ro4 * u4*(u4 - u5);
	return p5;
}

double M5QUADR_33(double gamma1, double delta, double alpha, double a1)
{
	double m5quad = 1 + (((gamma1 + 1)*sqrt(delta) - gamma1 * (1 - alpha)*a1) / ((gamma1 - (gamma1 - 1)*alpha)*a1 - gamma1 * sqrt(delta)));
	return m5quad;
}

double M5QUADR_34(double gamma1, double delta, double alpha, double a1)
{
	double m5quad = 1 - (((gamma1 + 1)*sqrt(delta) - gamma1 * (1 - alpha)*a1) / ((gamma1 - (gamma1 - 1)*alpha)*a1 + gamma1 * sqrt(delta)));
	return m5quad;
}
#endif

