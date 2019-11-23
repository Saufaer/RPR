#include <math.h>
#ifndef RULES_678



//–ешени€ (5,6,7)
void OutStreamU4U5(double A1, double A2, double gamma2, double u5, double ro5, double p5)
{

	double alpha = A1 / A2;

	double c5quadr = gamma2 * (p5 / ro5);

	double a = alpha * c5quadr + gamma2 * pow(u5, 2);

	double M5 = u5 / sqrt(c5quadr);

	double z = c5quadr * (1 - M5 * M5 - sqrt((1 - alpha) * (1 + alpha + 2 * gamma2 * M5* M5)));

	double dzetta = c5quadr * (1 - M5 * M5 + sqrt((1 - alpha) * (1 + alpha + 2 * gamma2 * M5* M5)));

	///
	double p_SH = p5;

	double u4plus = (a + sqrt(z * dzetta)) / ((gamma2 + 1) * u5);
	double u4minus = (a - sqrt(z * dzetta)) / ((gamma2 + 1) * u5);

	double p4plus = p5 - ((ro5 * u5) / alpha)*(u4plus - u5);
	double p4minus = p5 - ((ro5 * u5) / alpha)*(u4minus - u5);

	double ro4plus = ro5 * (u5) / (alpha * u4plus);
	double ro4minus = ro5 * (u5) / (alpha * u4minus);
};

double ALPHA(double A1, double A2)
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


//соотношение 7
double RO4(double u4, double u5, double ro5, double p5, double alpha)
{
	double ro4 = ro5 * (u5) / (alpha * u4);
	return ro4;
}
////////////////////////

//соотношение 6
double P4(double u4, double u5, double ro5, double p5, double alpha)
{
	double p4 = p5 - ((ro5 * u5) / alpha)*(u4 - u5);
	return p4;
}
//соотношение 8
double U4(double a, double u5, double gamma2, double z, double dzetta)
{
	double u4 = (a - sqrt(z*dzetta)) / ((gamma2 + 1)*u5);
	return u4;
}
double M4QUARD(double gamma2, double z, double dzetta, double a)
{
	double M4quadr = 1 - ((gamma2 + 1)* sqrt(z*dzetta)) / (a + gamma2 * sqrt(z*dzetta));
	return M4quadr;
}
////////////////////////////////
#endif