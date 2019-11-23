using namespace std;

#include "L1_L2.h"
#include <iostream>

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
	double M5max = M5Max(ALPHA(start.A1, start.A2), start.gamma2);
	double p = start.p2;
	double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

	{
		if (u < M5max * start.c2) {
			while (true)
			{
				if (u < M5max * start.c2) { p -= 0.01; }//если E ниже искомого
				else { break; }
				u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
			}
		}
		else
		{
			while (true)
			{
				if (u > M5max * start.c2) { p += 0.01; }//если E выше искомого
				else { break; }
				u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
			}
		}
	}
	Point e{ p,u };
	return e;
}

//Point El2(START start, Point E)
//{
//	Point El2;
//	double u5 = E.u;
//	double p5 = E.p;
//	double ro5 = start.ro2;
//	double a = A(ALPHA(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, u5);
//	double z = Z(ALPHA(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, M5(C5QUADR(start.gamma2, ro5, p5), u5));
//	double dzetta = DZETTA(ALPHA(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, M5(C5QUADR(start.gamma2, ro5, p5), u5));
//	double u4 = U4(a, u5, start.gamma2, z, dzetta);
//	El2.p = P4(u4, u5, ro5, p5, ALPHA(start.A1, start.A2));
//	El2.u = U4(a, u5, start.gamma2, z, dzetta);
//	return El2;
//}

void Solve(START start)
{
	
	Point B(B(start));
	Point D(D(start));
	Point E(E(start));

	Point El2 = l2(E.p, E.u, E, B, start);
	if (Check_L1_l2(start, El2, B))
	{
		NL2_NL1 NN = NL2_Nl2(start, E, B);

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
