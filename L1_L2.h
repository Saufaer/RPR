#include <math.h>
#include "Rules_6_7_8.h"
#include "Rules_15.h"
#include "Rules_19.h"
#include <iostream>
#ifndef L1_L2

struct Point
{
	double p;
	double u;
};
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
//Кривые (12,13)
double muiquadr(double gammai)
{
	return((gammai - 1) / (gammai + 1));
}

double taui(double roi)
{
	return (1 / roi);
}

double PSIi(double p, double pi, double gammai, double gamma2, double ci)
{
	return (2 / (gamma2 - 1))*ci*(pow((p / pi), ((gammai - 1) / (2 * gammai))) - 1);
}

double FIi(double p, double pi, double roi, double gammai)
{
	return (p - pi)*sqrt((1 - muiquadr(gammai)*muiquadr(gammai))*taui(roi) / (p + muiquadr(gammai)*muiquadr(gammai)*pi));
};

double L1(double p, double u1, double p1, double ro1, double gamma1, double gamma2, double c1)
{
	double u = 0;
	if (p >= p1) { u = u1 + FIi(p, p1, ro1, gamma1); }
	if (p <= p1) { u = u1 + PSIi(p, p1, gamma1, gamma2, c1); }
	return u;

};
double L2(double p, double u2, double p2, double ro2, double gamma2, double c2)
{
	double u = 0;
	if (p >= p2) { u = u2 - FIi(p, p2, ro2, gamma2); }
	if (p <= p2) { u = u2 - PSIi(p, p2, gamma2, gamma2, c2); }
	return u;
};

Point l2(double p5,double u5,Point E,Point B, START start)
{
	double u4=0;
	double p4=0;

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


struct NL2_NL1
{
	Point NL2;
	Point NL1;
};
Point Search_Conf_B(START start, Point El2, Point B)
{
	double p4 = El2.p;
	double u4 = El2.u;

	double p = p4;
	double u = u4;

	double uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

	while (true)
	{
		//if (p <= 0) { break; }
		if (fabs(u - uL1) <= 0.1) { break; }
		p -= 0.1;
		uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
		u = Addict_l2(p, p4, u4, start.c2, start.gamma2);
	}
	/*std::cout << "uL1=" << uL1 << "   pL1=" << p << std::endl;
	std::cout << "u4=" << u << "   p4=" << p << std::endl;*/


	Point N_B{ Point{p,u} };

	return N_B;

}


NL2_NL1 NL2_Nl2(START start,Point E,Point B)
{
	
	double p = start.p2;
	double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
	Point pl2;
	double uL1 = 0;
	bool IsSearch = false;

	NL2_NL1 TwoPoints{ NULL, NULL };

	while (true)//идём вниз по кривой из (p2,u2)
	{
		p += 0.1;
		if (p >= B.p) { break; }
		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//точка на L2

		pl2 = l2(p, u, E, B, start);//точка на l2
		
		 uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
		
		 if (fabs(pl2.u - uL1) <= 0.1) {
			 IsSearch = true;
			 TwoPoints.NL1 = pl2;
			 TwoPoints.NL2 = Point{ p,u };
			 break;
		 }
		
	}

	if ((p >= B.p)&&(!IsSearch))//если не смоги найти ниже НУ, то идём вверх по кривой из (p2,u2)
	{
		p = start.p2;
		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
		while (true)
		{
			p -= 0.1;
			if (p < E.p) { break; }
			u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//точка на L2

			pl2 = l2(p, u, E, B, start);//точка на l2

			uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

			if (fabs(pl2.u - uL1) <= 0.1) {
				IsSearch = true;
				TwoPoints.NL1 = pl2;
				TwoPoints.NL2 = Point{ p,u };
				break;
			}

		}
	}
	if  ((p <= E.p)&&(!IsSearch))//идём вверх по кривой из (p4,u4)
	{
		Point P_confB = Search_Conf_B(start, l2(E.p, E.u, E, B, start) , B);

	}

	/*std::cout << "u5=" << u << "   p5=" << p << std::endl;
	std::cout << "u4=" << pl2.u << "   p4=" << pl2.p << std::endl;
	std::cout << "uL1=" << uL1 << "   pL1=" << p << std::endl;*/

	return TwoPoints;

}



bool Check_L1_l2(START start, Point El2, Point B)
{
	bool NEOBHODIM = false;

	bool DOSTAT = false;


	double u1 = start.u1;
	double p1 = start.p1;
	double ro1 = start.ro1;
	double gamma1 = start.gamma1;
	double gamma2 = start.gamma2;
	double c1 = start.c1;

	//NEOBHODIM
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

	//DOSTAT
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

#endif 