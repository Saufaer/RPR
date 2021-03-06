#pragma once
#include "Points_Inflow.h"
#include "Rule_33_34_35.h"
#include "Rule_41_42.h"
Point Get_H_from_l1(double p4, double u4, Point C2, Point C1, START start)
{
	double u5 = 0;
	double p5 = 0;

	if ((p4 == C1.p) && (u4 == C1.u))
	{
		p5 = C1.p;
		u5 = C1.u;
	}
	if (C2.p <= p4 && p4 < C1.p && C2.u <= u4 && u4 < C1.u)
	{
		double ro4 = start.ro1;

		double alpha = ALPHA2(start.A1, start.A2);
		double c4quadr = C4QUADR(start.gamma1, ro4, p4);
		double a1 = A1(/*alpha,*/ c4quadr, start.gamma1, u4);
		double delta = DELTA(c4quadr, start.gamma1, alpha, u4);

		u5 = U5_34(u4, a1, delta, start.gamma1, alpha);
		p5 = P5(p4, u4, u5, ro4);
	}

	return Point{ p5, u5 };
}

Point Get_F_from_l1(double p4, double u4, Point C2, Point C1, START start)
{
	double u5 = 0;
	double p5 = 0;

	if ((p4 == C1.p) && (u4 == C1.u))
	{
		p5 = C1.p;
		u5 = C1.u;
	}
	if (C2.p <= p4 && p4 < C1.p && C2.u <= u4 && u4 < C1.u)
	{
		double ro4 = start.ro1;

		double alpha = ALPHA2(start.A1, start.A2);
		double c4quadr = C4QUADR(start.gamma1, ro4, p4);
		double a1 = A1(/*alpha,*/ c4quadr, start.gamma1, u4);
		double delta = DELTA(c4quadr, start.gamma1, alpha, u4);

		u5 = U5_33(u4, a1, delta, start.gamma1, alpha);
		p5 = P5(p4, u4, u5, ro4);
	}

	return Point{ p5, u5 };
}

Point Get_F2_from_l1(Point F, Point C2, START start)
{
	double u5F2 = 0;
	double p5F2 = 0;

	double p4 = C2.p;
	double u4 = C2.u;

	double ro4 = start.ro1;
	double gamma1 = start.gamma1;
	double alpha = ALPHA2(start.A1, start.A2);
	double c4quadr = C4QUADR(gamma1, ro4, p4);
	double a1 = A1(/*alpha,*/ c4quadr, gamma1, u4);
	double delta = DELTA(c4quadr, gamma1, alpha, u4);

	double M5quadr = 0;
	if ((c4quadr - pow(u4, 2)) <= 0)
	{
		M5quadr = M5QUADR_33(gamma1, delta, alpha, a1);
	}
	else
	{
		M5quadr = M5QUADR_34(gamma1, delta, alpha, a1);
	}
	double mu1quadr = muiquadr(start.gamma1);
	p5F2 = F.p*((1 + mu1quadr)*M5quadr - mu1quadr);

	double ro5 = start.ro2;
	double gamma2 = start.gamma2;
	double p5 = F.p;
	double c5 = sqrt(C5QUADR(gamma2, ro5, p5));

	u5F2 = F.u - (1 - mu1quadr)*c5*(sqrt(M5quadr) - (1 / sqrt(M5quadr)));

	return Point{ p5F2, u5F2 };
}

bool Check_Inflow(START start, Point C1)
{
	bool NEOBHODIM = false;
	double u1 = start.u1;
	double p1 = start.p1;

	double ro1 = start.ro1;

	double gamma1 = start.gamma1;
	double gamma2 = start.gamma2;
	double c1 = start.c1;

	//necessary
	if (p1 < C1.p)
	{
		if (u1 + FIi(C1.p, p1, ro1, gamma1) < 0)
		{
			NEOBHODIM = true;
		}
	}
	else
	{
		if (u1 + PSIi(C1.p, p1, gamma1, gamma2, c1) < 0)
		{
			NEOBHODIM = true;
		}
	}
	return NEOBHODIM;
}

bool Check_CONF_A1(START start, Point H, Point C1)
{
	bool NEOBHODIM = false;

	bool DOSTAT = false;


	double u1 = start.u1;
	double p1 = start.p1;
	double u2 = start.u2;
	double p2 = start.p2;
	double ro1 = start.ro1;
	double ro2 = start.ro2;
	double gamma1 = start.gamma1;
	double gamma2 = start.gamma2;
	double c1 = start.c1;
	double c2 = start.c2;
	//necessary - neobh
	if (p1 < C1.p)
	{
		if (u1 + FIi(C1.p, p1, ro1, gamma1) < 0)
		{
			NEOBHODIM = true;
		}
	}
	else
	{
		if (u1 + PSIi(C1.p, p1, gamma1, gamma2, c1) < 0)
		{
			NEOBHODIM = true;
		}
	}
	//sufficient - dostat
	if (p2 < H.p)
	{
		if (u2 - FIi(H.p, p2, ro2, gamma2) - H.u < 0)
		{
			DOSTAT = true;
		}
	}
	else
	{
		if (u2 - PSIi(H.p, p2, gamma2, gamma2, c2) - H.u < 0)
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

bool Check_CONF_B1(START start, Point F, Point C1)
{
	bool NEOBHODIM = false;

	bool DOSTAT = false;


	double u1 = start.u1;
	double p1 = start.p1;
	double u2 = start.u2;
	double p2 = start.p2;
	double ro1 = start.ro1;
	double ro2 = start.ro2;
	double gamma1 = start.gamma1;
	double gamma2 = start.gamma2;
	double c1 = start.c1;
	double c2 = start.c2;
	//necessary
	if (p1 < C1.p)
	{
		if (u1 + FIi(C1.p, p1, ro1, gamma1) < 0)
		{
			NEOBHODIM = true;
		}
	}
	else
	{
		if (u1 + PSIi(C1.p, p1, gamma1, gamma2, c1) < 0)
		{
			NEOBHODIM = true;
		}
	}
	//sufficient
	if (p2 < F.p)
	{
		if (u2 - FIi(F.p, p2, ro2, gamma2) - F.u > 0)
		{
			DOSTAT = true;
		}
	}
	else
	{
		if (u2 - PSIi(F.p, p2, gamma2, gamma2, c2) - F.u > 0)
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

bool Check_CONF_B2(START start, Point F2, Point C1)
{
	bool NEOBHODIM = false;

	bool DOSTAT = false;


	double u1 = start.u1;
	double p1 = start.p1;
	double u2 = start.u2;
	double p2 = start.p2;
	double ro1 = start.ro1;
	double ro2 = start.ro2;
	double gamma1 = start.gamma1;
	double gamma2 = start.gamma2;
	double c1 = start.c1;
	double c2 = start.c2;
	//necessary
	if (p1 < C1.p)
	{
		if (u1 + FIi(C1.p, p1, ro1, gamma1) < 0)
		{
			NEOBHODIM = true;
		}
	}
	else
	{
		if (u1 + PSIi(C1.p, p1, gamma1, gamma2, c1) < 0)
		{
			NEOBHODIM = true;
		}
	}
	//sufficient
	if (p2 < F2.p)
	{
		if (u2 - FIi(F2.p, p2, ro2, gamma2) - F2.u > 0)
		{
			DOSTAT = true;
		}
	}
	else
	{
		if (u2 - PSIi(F2.p, p2, gamma2, gamma2, c2) - F2.u > 0)
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

TwoPoints Search_Conf_A1(START &start, Point &C2, Point &C1)
{

	double p = start.p1;
	double u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
	Point pl1{ NULL };
	double uL2 = 0;
	bool IsSearch = false;

	TwoPoints TwoPoints{ NULL, NULL };

	while (true)//start down from (p1,u1)
	{
		p -= 0.1;
		if (p <= C2.p) { break; }
		u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);//point from L1

		pl1 = Get_H_from_l1(p, u, C2, C1, start);//point from l1

		uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

		if (fabs(pl1.u - uL2) <= 0.1) {
			IsSearch = true;
			TwoPoints.NL1 = pl1;
			TwoPoints.NL2 = Point{ p,u };
			break;
		}

	}

	if ((p <= C2.p) && (!IsSearch))//start up from (p1,u1)
	{
		p = start.p1;
		u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
		while (true)
		{
			p += 0.1;
			if (p >= C1.p) { break; }
			u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);//point from L1

			pl1 = Get_H_from_l1(p, u, C2, C1, start);//point from l1

			uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

			if (fabs(pl1.u - uL2) <= 0.1) {
				IsSearch = true;
				TwoPoints.NL1 = pl1;
				TwoPoints.NL2 = Point{ p,u };
				break;
			}

		}
	}

	//std::cout << "u4=" << u << "   p4=" << p << std::endl;
	//std::cout << "u5=" << pl1.u << "   p5=" << pl1.p << std::endl;
	//std::cout << "uL2=" << uL2 << "   pL2=" << p << std::endl;

	return TwoPoints;

}

Point Search_Conf_B1(START &start, Point &F, Point &B)
{
	double p5 = F.p;
	double u5 = F.u;

	double ro5 = start.ro1;

	double p = p5;
	double u = u5;

	Point N_B{ NULL };
	double uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

	while (true)
	{

		if (fabs(u - uL2) <= 0.1) { break; }
		p += 0.1;
		uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
		u = Addict_l1(p, p5, u5, start.c1, start.gamma1, ro5);
	}

	N_B = Point{ p,u };

	return N_B;

}

Point Search_Conf_B2(START &start, Point &F2, Point &B)
{

	double p5 = F2.p;
	double u5 = F2.u;

	double ro5 = start.ro1;

	double p = p5;
	double u = u5;

	Point N_B{ NULL };
	double uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

	while (true)
	{
		if (fabs(u - uL2) <= 0.1) { break; }
		p += 0.1;
		uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
		u = Addict_l1(p, p5, u5, start.c1, start.gamma1, ro5);
	}

	N_B = Point{ p,u };

	return N_B;

}

bool Check_RES_Inflow_A(Point N_L2, Point N_L1)
{
	double p4 = N_L2.p;
	double u4 = N_L2.u;
	double p5 = N_L1.p;
	double u5 = N_L1.u;

	bool correct = false;
	if ((p5 > p4) && (u5 > u4) && (abs(u5) < abs(u4)))
	{
		correct = true;
	}
	return correct;
}

bool Check_RES_Inflow_B(Point N_L2, Point N_L1)
{
	double p4 = N_L2.p;
	double u4 = N_L2.u;
	double p5 = N_L1.p;
	double u5 = N_L1.u;

	bool correct = false;
	if ((p5 < p4) && (u5 < u4) && (abs(u5) > abs(u4)))
	{
		correct = true;
	}
	return correct;
}
