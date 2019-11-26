
#include "Solver.h"
#include <iostream>
#include <limits>

int main()
{
	typedef std::numeric_limits< double > dbl;
	cout.precision(dbl::max_digits10);

	START start;

	start.gamma2 = 1.1;
	start.gamma1 = 1.1;

	start.p1 = 100000;
	start.p2 = 140000;

	start.u1 = 70;
	start.u2 = 70;

	start.c1 = 343;
	start.c2 = 343;

	start.ro1 = 0.5;
	start.ro2 = 0.5;

	start.A1 = 100;
	start.A2 = 200;

	Solve(start);

	return 0;
}

