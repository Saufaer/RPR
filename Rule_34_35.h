#pragma once
#include <math.h>
#ifndef RULE_34_35
#define RULE_34_35

double ALPHA2(double A1, double A2)
{
	double alpha = A1 / A2;
	return alpha;
}

double A1(/*double alpha,*/ double c4quadr, double gamma1, double u4)
{
	double a1 = /*alpha **/ c4quadr + gamma1 * pow(u4, 2);
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

double RO5(double ro4,double alpha,double u4,double u5)
{
	double ro5 = ro4 * (alpha*u4) / (u5);
	return ro5;
}

double U5(double u4,double a1,double Delta,double gamma1,double alpha)
{
	double u5 = (a1 - sqrt(Delta)) / ((2 * gamma1 - (gamma1 - 1)*alpha)*u4);
	return u5;
}

double P5(double p4,double u4, double u5, double ro4)
{
	double p5 = p4 + ro4 * u4*(u4 - u5);
	return p5;
}
#endif

