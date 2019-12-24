
#include "Solver.h"
#include <iostream>
#include <limits>

int main()
{
	typedef std::numeric_limits< double > dbl;
	cout.precision(dbl::max_digits10);

	START start;

	start.A2 = 10;
	start.A1 = 5;
	
	start.p2 = 303975;
	start.p1 = 353975;
	
	start.u2 = 150;
	start.u1 = 170;



	start.ro2 = 1.667;
	start.ro1 = 1.667;

	start.gamma2 = 1.4;
	start.gamma1 = 1.4;

	start.c2 = sqrtf(start.gamma2*(start.p2/ start.ro2));
	start.c1 = sqrtf(start.gamma1*(start.p1 / start.ro1));

	Solve(start);

	return 0;
}

