using namespace std;

#include "Curves.h"
#include <iostream>
struct START
{
	double gamma2 = 1.1;
	double gamma1 = 1.1;

	double p1 = 100000;
	double p2 = 100000;

	double u1 = 200;
	double u2 = 200;

	double c1 = 343;
	double c2 = 343;

	double ro1 = 0.5;
	double ro2 = 0.5;

	double A1 = 100;
	double A2 = 200;
};

struct Point
{
	double p;
	double u;
};

struct TwoPoints
{
	Point NL2;
	Point NL1;
};

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

	double M5max = M5Max(ALPHA(start.A1, start.A2), start.gamma2);
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

Point Get_from_l2(double p5, double u5, Point E, Point B, START start)
{
	double u4 = 0;
	double p4 = 0;

	if ((p5 == B.p) && (u5 == B.u))
	{
		p4 = B.p;
		u4 = 0;
	}
	if (E.p <= p5 && p5 < B.p && B.u < u5 && u5 <= E.u)
	{
		double ro5 = start.ro2;
		double a = A(ALPHA(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, u5);
		double z = Z(ALPHA(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, M5(C5QUADR(start.gamma2, ro5, p5), u5));
		double dzetta = DZETTA(ALPHA(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, M5(C5QUADR(start.gamma2, ro5, p5), u5));
		u4 = U4(a, u5, start.gamma2, z, dzetta);
		p4 = P4(u4, u5, ro5, p5, ALPHA(start.A1, start.A2));
	}
	/*if (p5 == E.p && u5 == E.u)
	{
		double r = sqrt((start.gamma2 + 1)*(2 + (start.gamma2 - 1)*pow(M5Max(ALPHA(start.A1, start.A2), start.gamma2), 2)));

		u4 = (sqrt(C5QUADR(start.gamma2, start.ro2, E.p))*r) / (start.gamma2 + 1);
		p4 = (E.p / (start.gamma2 + 1))*(r / (r - start.gamma2*M5Max(ALPHA(start.A1, start.A2), start.gamma2)));
	}*/
	return Point{ p4, u4 };
}

bool Check_CONF_A(START start, Point El2, Point B)
{
	bool NEOBHODIM = false;

	bool DOSTAT = false;


	double u1 = start.u1;
	double p1 = start.p1;
	double ro1 = start.ro1;
	double gamma1 = start.gamma1;
	double gamma2 = start.gamma2;
	double c1 = start.c1;
	//necessary
	if (p1 < B.p)
	{
		if (u1 + FIi(B.p, p1, ro1, gamma1) >= 0)
		{
			NEOBHODIM = true;
		}
	}
	else
	{
		if (u1 + PSIi(B.p, p1, gamma1, gamma2, c1) >= 0)
		{
			NEOBHODIM = true;
		}
	}
	//sufficient
	if (p1 < El2.p)
	{
		if (u1 + FIi(El2.p, p1, ro1, gamma1) - El2.u <= 0)
		{
			DOSTAT = true;
		}
	}
	else
	{
		if (u1 + PSIi(El2.p, p1, gamma1, gamma2, c1) - El2.u <= 0)
		{
			DOSTAT = true;
		}
	}
	//FINAL
	if (DOSTAT && NEOBHODIM)
	{
		return true;
	}
	else
	{
		return false;
	}
}
TwoPoints Search_Conf_A(START &start, Point &E, Point &B)
{

	double p = start.p2;
	double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
	Point pl2;
	double uL1 = 0;
	bool IsSearch = false;

	TwoPoints TwoPoints{ NULL, NULL };

	while (true)//start down from (p2,u2)
	{
		p += 0.1;
		if (p >= B.p) { break; }
		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//point from L2

		pl2 = Get_from_l2(p, u, E, B, start);//point from l2

		uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

		if (fabs(pl2.u - uL1) <= 0.1) {
			IsSearch = true;
			TwoPoints.NL1 = pl2;
			TwoPoints.NL2 = Point{ p,u };
			break;
		}

	}

	if ((p >= B.p) && (!IsSearch))//start up from (p2,u2)
	{
		p = start.p2;
		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
		while (true)
		{
			p -= 0.1;
			if (p < E.p) { break; }
			u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//point from L2

			pl2 = Get_from_l2(p, u, E, B, start);//point from l2

			uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

			if (fabs(pl2.u - uL1) <= 0.1) {
				IsSearch = true;
				TwoPoints.NL1 = pl2;
				TwoPoints.NL2 = Point{ p,u };
				break;
			}

		}
	}


	/*std::cout << "u5=" << u << "   p5=" << p << std::endl;
	std::cout << "u4=" << pl2.u << "   p4=" << pl2.p << std::endl;
	std::cout << "uL1=" << uL1 << "   pL1=" << p << std::endl;*/

	return TwoPoints;

}

Point Search_Conf_B(START &start, Point &El2, Point &B)
{
	double p4 = El2.p;
	double u4 = El2.u;

	double p = p4;
	double u = u4;

	Point N_B{ NULL };
	double uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

	while (true)
	{

		if (fabs(u - uL1) <= 0.1) { break; }
		p -= 0.1;
		uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
		u = Addict_l2(p, p4, u4, start.c2, start.gamma2);
	}

	N_B = Point{ p,u };

	return N_B;

}

void Solve(START start)
{

	Point B(B(start));
	Point D(D(start));
	Point E(E(start));

	Point El2 = Get_from_l2(E.p, E.u, E, B, start);

	if (Check_CONF_A(start, El2, B))
	{
		TwoPoints NN = Search_Conf_A(start, E, B);

		cout << endl << "CONFIG A" << endl;
		cout << "p4=" << NN.NL1.p << endl;
		cout << "u4=" << NN.NL1.u << endl;
		cout << endl;
		cout << "p3=" << NN.NL1.p << endl;
		cout << "u3=" << NN.NL1.u << endl;
		cout << endl;
		cout << "p5=" << NN.NL2.p << endl;
		cout << "u5=" << NN.NL2.u << endl;
		cout << endl;
		cout << "p1=" << start.p1 << endl;
		cout << "u1=" << start.u1 << endl;
		cout << endl;
		cout << "p2=" << start.p2 << endl;
		cout << "u2=" << start.u2 << endl;
	}
	else
	{
		Point N = Search_Conf_B(start, El2, B);

		cout << endl << "CONFIG B" << endl;
		cout << "p4=" << El2.p << endl;
		cout << "u4=" << El2.u << endl;
		cout << endl;
		cout << "p3=" << N.p << endl;
		cout << "u3=" << N.u << endl;
		cout << endl;
		cout << "p'3=" << N.p << endl;
		cout << "u'3=" << N.u << endl;
		cout << endl;
		cout << "p5=" << E.p << endl;
		cout << "u5=" << E.u << endl;
		cout << endl;
		cout << "p1=" << start.p1 << endl;
		cout << "u1=" << start.u1 << endl;
		cout << endl;
		cout << "p2=" << start.p2 << endl;
		cout << "u2=" << start.u2 << endl;
	}

}
