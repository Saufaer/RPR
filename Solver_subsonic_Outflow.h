#pragma once
#include "Points_Outflow.h"
#include "Rule_6_7_8_9.h"
#include "Rule_19.h"
#include <climits>

bool NEOBHODIM_Outflow(START start, Point B)
{
   bool NEOBHODIM = false;


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
       else {
           cout << "\n Is not Outflow, start conditions unconsists, skip solving";
       }
   }
   else if (u1 + PSIi(B.p, p1, gamma1, gamma2, c1) >= 0)
   {
       NEOBHODIM = true;
   }
   else {
       cout << "\n Is not Outflow, start conditions unconsists, skip solving";
   }
   return NEOBHODIM;
}

bool DOSTAT_Outflow(START start, Point E_default)
{
    bool NEOBHODIM = false;

    bool DOSTAT = false;


    double u1 = start.u1;
    double p1 = start.p1;
    double ro1 = start.ro1;
    double gamma1 = start.gamma1;
    double gamma2 = start.gamma2;
    double c1 = start.c1;
    //DOSTAT
    if (p1 < E_default.p)
    {
        if (u1 + FIi(E_default.p, p1, ro1, gamma1) - E_default.u <= 0)
        {
            DOSTAT = true;
        }
    }
    else
    {
        if (u1 + PSIi(E_default.p, p1, gamma1, gamma2, c1) - E_default.u <= 0)
        {
            DOSTAT = true;
        }
    }
    return DOSTAT;
}

Point Get_from_l2(double p5, double u5, Point E, Point B, START start)
{
	double u4 = 0;
	double p4 = 0;

	if ((p5 == B.p) && (u5 == B.u))
	{
		p4 = B.p;
		u4 = 0;
      // cout << "\n\n FIRST p4" << p4;
	}
	
    if (fabs(p5 - E.p) <= 1 && fabs(u5 - E.u) <= 1)
    {

        double r = sqrt((start.gamma2 + 1)*(2 + (start.gamma2 - 1)*pow(M5Max(ALPHA1(start.A1, start.A2), start.gamma2), 2)));

        u4 = (sqrt(C5QUADR(start.gamma2, start.ro2, E.p))*r) / (start.gamma2 + 1);
        p4 = (E.p / (start.gamma2 + 1))*(r / (r - start.gamma2*M5Max(ALPHA1(start.A1, start.A2), start.gamma2)));
       // cout << "\n\n THIRD p4" << p4;
    }
    else
	//if (E.p <= p5 && p5 < B.p && B.u < u5 && u5 <= E.u)
	{
       
		double ro5 = start.ro2;

		double a = A(ALPHA1(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, u5);
		double z = Z(ALPHA1(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, M5(C5QUADR(start.gamma2, ro5, p5), u5));
		double dzetta = DZETTA(ALPHA1(start.A1, start.A2), C5QUADR(start.gamma2, ro5, p5), start.gamma2, M5(C5QUADR(start.gamma2, ro5, p5), u5));
        
        if (z >= 0)
        {
            u4 = U4_8(a, u5, start.gamma2, z, dzetta);
        }
        else
        {
            u4 = U4_9(a, u5, start.gamma2, z, dzetta);
        }
		
		p4 = P4(u4, u5, ro5, p5, ALPHA1(start.A1, start.A2));
      //  cout << "\n\n SECOND p4" << p4 <<" \n u4" << u4 << " \n a" << a << " \n z" << z << " \n dzetta" << dzetta;
	}
    
	return Point{ p4, u4 };
}

bool Check_CONF_A(START start, Point El2, Point B)
{
    bool res1 = false;
    bool res2 = false;

    //if (fabs(L1(El2.p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1) - El2.u) <= 0.0001)
    //{
    //    res1 = true;
    //}

    
    if (NEOBHODIM_Outflow(start, B) && DOSTAT_Outflow(start, El2))
    {
        return true;
    }
    else
    {
        return false;
    }


    //if (res1 && res2)
    //{
    //    return true;
    //}
    //else
    //{
    //    return false;
    //}
}
bool Check_CONF_B(START start, Point El2, Point B)
{
    return true;
    //if (L1(El2.p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1) - El2.u > 0)
    //{
    //    return true;
    //}
    //else
    //{
    //    return false;
    //}
}


TwoPoints Search_Conf_A(START &start, Point &E, Point &B,int i)//subsonic
{

	double p = start.p2;
	double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
    Point pl2{0,0};
	double uL1 = 0;
	bool IsSearch = false;

	TwoPoints TwoPoints{ NULL, NULL };

	while (true)//start down from (p2,u2) to B
	{
        
		p += 0.5;
		if (p >= B.p) { break; }
		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//point from L2

		pl2 = Get_from_l2(p, u, E, B, start);//point from l2
        //cout << "\n pl2.p=" << pl2.p;
		uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

		if (fabs(u - uL1) <= 10 || fabs(pl2.u - uL1) <= 10) {
			IsSearch = true;
			TwoPoints.NL1 = pl2;
			
			TwoPoints.NL2 = Point{ p,u };
			break;
		}

        /////////// Write lines
		int c = round(p);
		if (((c%474) == 0) && (pl2.p>0))
		{
			Write("L1_1.p = " + to_string(p) + "\n" + "L1_1.u = " + to_string(uL1) + "\n", "L1_1.txt", i);
			Write("pl2_1.p = " + to_string(pl2.p) + "\n" + "pl2_1.u = " + to_string(pl2.u) + "\n", "pl2_1.txt", i);
            Write("L2_1.p = " + to_string(p) + "\n" + "L2_1.u = " + to_string(u) + "\n", "L2_1.txt", i);
		}
	}
    if (IsSearch)
    {
        Write("L1_1.p = " + to_string(p) + "\n" + "L1_1.u = " + to_string(uL1) + "\n", "L1_1.txt", i);
        Write("pl2_1.p = " + to_string(pl2.p) + "\n" + "pl2_1.u = " + to_string(pl2.u) + "\n", "pl2_1.txt", i);
        Write("L2_1.p = " + to_string(p) + "\n" + "L2_1.u = " + to_string(u) + "\n", "L2_1.txt", i);
    }
    //////////

	if (!IsSearch)//start up from (p2,u2) to E
	{
        
		p = start.p2;
		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
		while (true)
		{
			p -= 0.5;
			if (p < E.p) { break; }
			u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//point from L2

			pl2 = Get_from_l2(p, u, E, B, start);//point from l2
            //cout << "\n pl2.p="<<pl2.p;


			uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

			if (fabs(u - uL1) <= 10 || fabs(pl2.u - uL1) <= 10) {
				IsSearch = true;
				TwoPoints.NL1 = pl2;
				TwoPoints.NL2 = Point{ p,u };
				break;
			}

            /////////// Write lines
			int c = round(p);
			if (((c % 474) == 0) && (pl2.p > 0))
			{
				Write("L1_2.p = " + to_string(p) + "\n" + "L1_2.u = " + to_string(uL1) + "\n", "L1_2.txt", i);
				Write("pl2_2.p = " + to_string(pl2.p) + "\n" + "pl2_2.u = " + to_string(pl2.u) + "\n", "pl2_2.txt", i);
				Write("L2_2.p = " + to_string(p) + "\n" + "L2_2.u = " + to_string(u) + "\n", "L2_2.txt", i);
			}
            
		}
        if (IsSearch)
        {
            Write("L1_2.p = " + to_string(p) + "\n" + "L1_2.u = " + to_string(uL1) + "\n", "L1_2.txt", i);
            Write("pl2_2.p = " + to_string(pl2.p) + "\n" + "pl2_2.u = " + to_string(pl2.u) + "\n", "pl2_2.txt", i);
            Write("L2_2.p = " + to_string(p) + "\n" + "L2_2.u = " + to_string(u) + "\n", "L2_2.txt", i);
        }
        ///////////
	}


	return TwoPoints;

}

Point Search_Conf_B(START &start, Point &El2, Point &B,int i)//sonic
{
	double p4 = El2.p;
	double u4 = El2.u;

	//double p = p4;
	//double u = u4;

   //  double p = start.p2;

    double p = B.p;
    double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

	Point N_B{ NULL };
	double uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

	while (true)
	{

		if (fabs(u - uL1) <= 5) { break; }
        if (p <= 0) { break; }
		p -= 0.5;
		uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
		u = Addict_l2(p, p4, u4, start.c2, start.gamma2);

        /////////// Write lines
        int c = round(p);
        if (((c % 474) == 0))
        {
            Write("L1_1.p = " + to_string(p) + "\n" + "L1_1.u = " + to_string(uL1) + "\n", "L1_1.txt", i);
            Write("l2.p = " + to_string(p) + "\n" + "l2.u = " + to_string(u) + "\n", "l2.txt", i);
        }
        ///////////
	}

	N_B = Point{ p,u };

	return N_B;

}

bool Check_RES_Outflow(Point N_L2,Point N_L1)
{
	double p4 = N_L1.p;
	double u4 = N_L1.u;
	double p5 = N_L2.p;
	double u5 = N_L2.u;

	bool correct = false;
	if ((p4 <= p5) && (u4 >= u5) && (p4 > 0) && (p5 > 0))
	{
		correct = true;
	}
	return correct;
}