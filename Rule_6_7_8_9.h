#include <math.h>
#ifndef RULE_6789
#define RULE_6789

double ALPHA1(double A1, double A2)
{
	double alpha = A1 / A2;
	return alpha;
}

double A(double alpha, double c5quadr, double gamma2, double u5)
{
	double a = alpha * c5quadr + gamma2 * pow(u5, 2);
	return a;
}

double C5QUADR(double gamma2, double ro5, double p5)
{
	double c5quadr = gamma2 * (p5 / ro5);
	return c5quadr;
}

double Z(double alpha, double c5quadr, double gamma2, double M5)
{
	double z = c5quadr * (1 - M5 * M5 - sqrt((1 - alpha) * (1 + alpha + 2 * gamma2 * M5* M5)));
	return z;
}

double DZETTA(double alpha, double c5quadr, double gamma2, double M5)
{
	double dzetta = c5quadr * (1 - M5 * M5 + sqrt((1 - alpha) * (1 + alpha + 2 * gamma2 * M5* M5)));
	return dzetta;
}

double M5(double c5quadr, double u5)
{
	double M5 = u5 / sqrt(c5quadr);
	return M5;
}


//expression 7
double RO4(double u4, double u5, double ro5, double p5, double alpha)
{
	double ro4 = ro5 * (u5) / (alpha * u4);
	return ro4;
}

//expression 6
double P4(double u4, double u5, double ro5, double p5, double alpha)
{
	double p4 = p5 - ((ro5 * u5) / alpha)*(u4 - u5);
	return p4;
}
//expression 8
double U4_8(double a, double u5, double gamma2, double z, double dzetta)
{
	double u4 = (a - sqrt(fabs(z*dzetta))) / ((gamma2 + 1)*u5);
	return u4;
}
double M4QUARD_8(double gamma2, double z, double dzetta, double a)
{
	double M4quadr = 1 - ((gamma2 + 1)* sqrt(z*dzetta)) / (a + gamma2 * sqrt(z*dzetta));
	return M4quadr;
}

double U4_9(double a, double u5, double gamma2, double z, double dzetta)
{
    double u4 = (a + sqrt(fabs(z*dzetta))) / ((gamma2 + 1)*u5);
    return u4;
}
double M4QUARD_9(double gamma2, double z, double dzetta, double a)
{
    double M4quadr = 1 + ((gamma2 + 1)* sqrt(z*dzetta)) / (a + gamma2 * sqrt(z*dzetta));
    return M4quadr;
}
#endif