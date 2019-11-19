#include <math.h>
double M5Max(double alpha,double gamma2)
{
	double M5max = sqrt((1 + (1 - alpha)*gamma2) - sqrt(pow((1 + (1 - alpha)*gamma2), 2) - alpha * alpha));
	return M5max;
}