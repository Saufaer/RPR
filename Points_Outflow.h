#pragma once
#include "Curves.h"
#include "Start.h"
#include "Rule_15.h"
#include "Rule_6_7_8.h"

Point B(START start)
{
	double p = start.p2;
	double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
	while (true)
	{
		if (u > 0.001) { p += 0.1; }
		else { break; }
		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
	}
	Point b{ p,0 };
	return b;
}

Point D(START start)
{
	double p = start.p2;
	double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
	while (true)
	{
		if (u <= start.c2) { p -= 0.1; }
		else { break; }
		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
	}
	Point d{ p,u };
	return d;
}

Point E(START start)
{
	Point e{ NULL };

	double M5max = M5Max(ALPHA1(start.A1, start.A2), start.gamma2);
	double p = start.p2;
	double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

	{
		if (u < M5max * start.c2) {//go up from (p2,u2)
			while (true)
			{
				if (u < M5max * start.c2) { p -= 0.01; }
				else { break; }
				u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
			}
		}
		else//go down from (p2,u2)
		{
			while (true)
			{
				if (u > M5max * start.c2) { p += 0.01; }
				else { break; }
				u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
			}
		}
	}
	e = Point{ p,u };
	return e;
}

