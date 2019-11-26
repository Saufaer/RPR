#pragma once
#include "Curves.h"
#include "Start.h"

Point C1(START start)
{
	double p = start.p1;
	double u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
	while (true)
	{
		if (u < -0.001) { p += 0.1; }
		else { break; }
		u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
	}
	Point c{ p,0 };
	return c;
}

Point C2(START start)
{
	Point c2{ NULL };

	double p = start.p1;
	double u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

	{
		if (u > -start.c1) {//go down from (p1,u1)
			while (true)
			{
				if (u > -start.c1) { p -= 0.01; }
				else { break; }
				u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
			}
		}
		else//go up from (p1,u1)
		{
			while (true)
			{
				if (u < -start.c1) { p += 0.01; }
				else { break; }
				u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
			}
		}
	}
	c2 = Point{ p,u };
	return c2;
}