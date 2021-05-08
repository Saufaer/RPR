#pragma once
#include "Points_Inflow.h"
#include "Rule_33_34_35.h"
#include "Rule_41_42.h"

bool Check_CONF_DA(START start, Point C1, Point C2, Point Cs, Point Hs)
{
    bool res1 = false;
    bool res2 = false;

    if ((Cs.p - C2.p < -0.01) && fabs(Cs.u) - fabs(C2.u) > 0.01)
    {
        res1 = true;
    }

    if (DOSTAT_Inflow(start, Hs) && NEOBHODIM_Inflow(start, C1))
    {
        res2 = true;
    }
    if (res1 && res2)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

TwoPoints Search_Conf_DA(START &start, Point &Cs, Point &C1, int i)
{
    double p = start.p1;
    double u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
    Point pl1{ NULL };
    double uL2 = 0;
    bool IsSearch = false;

    TwoPoints TwoPoints{ NULL, NULL };

    while (true)//start down from (p1,u1) to Cs
    {
        p -= 1;
        if (p <= Cs.p) { break; }
        u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);//point from L1

        //pl1 = Get_H_from_l1(p, u, C2, C1, start);//point from l1

        pl1 = Get_from_l1(p, u, start);//point from l1

        uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

        if (fabs(u - uL2) <= 10) {
            IsSearch = true;
            TwoPoints.NL1 = pl1;
            TwoPoints.NL2 = Point{ p,u };
            break;
        }

        /////////// Write lines
        int c = round(p);
        if (((c % 747) == 0))
        {
            Write("L1_1.p = " + to_string(p) + "\n" + "L1_1.u = " + to_string(u) + "\n", "L1_1.txt", i);
            Write("cl1_1.p = " + to_string(pl1.p) + "\n" + "cl1_1.u = " + to_string(pl1.u) + "\n", "cl1_1.txt", i);
            Write("L2_1.p = " + to_string(p) + "\n" + "L2_1.u = " + to_string(uL2) + "\n", "L2_1.txt", i);
        }
        ///////////

    }

    if ((p <= Cs.p) && (!IsSearch))//start up from (p1,u1) to C1
    {
        p = start.p1;
        u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
        while (true)
        {
            p += 1;
            if (p >= C1.p) { break; }
            u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);//point from L1

            //pl1 = Get_H_from_l1(p, u, C2, C1, start);//point from l1
            pl1 = Get_from_l1(p, u, start);//point from l1

            uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

            if (fabs(u - uL2) <= 10 || fabs(pl1.u - uL2) <= 10) {
                IsSearch = true;
                TwoPoints.NL1 = pl1;
                TwoPoints.NL2 = Point{ p,u };
                break;
            }
            /////////// Write lines
            int c = round(p);
            if (((c % 747) == 0))
            {
                Write("L1_2.p = " + to_string(p) + "\n" + "L1_2.u = " + to_string(u) + "\n", "L1_2.txt", i);
                Write("cl1_2.p = " + to_string(pl1.p) + "\n" + "cl1_2.u = " + to_string(pl1.u) + "\n", "cl1_2.txt", i);
                Write("L2_2.p = " + to_string(p) + "\n" + "L2_2.u = " + to_string(uL2) + "\n", "L2_2.txt", i);
            }
            ///////////
        }
    }

    return TwoPoints;
    
}

bool Check_CONF_D1(START start, Point C1, Point C2, Point Cs, Point C2s)
{
    bool res1 = false;
    bool res2 = false;

    if ((Cs.p - C2.p > 0.0001) && fabs(Cs.u) - fabs(C2.u) < -0.0001)
    {
        res1 = true;
    }


    if (DOSTAT_Inflow(start, C2s) && NEOBHODIM_Inflow(start, C1))
    {
        res2 = true;
    }

    if (res1 && res2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

TwoPoints Search_Conf_D1(START &start, Point &C2, Point &C1, Point &Cs,  Point C2s, int i)
{
    C2.p = start.p1;
    C2.u = start.u1;

    // C*'(p4*,u4*) = C2s


    double p = Cs.p;
    double u = L1(p, C2s.u, C2s.p, start.ro1, start.gamma1, start.gamma2, start.c1);// use C2s
    Point pl1{ NULL };
    double uL2 = 0;
    bool IsSearch = false;

    TwoPoints TwoPoints{ NULL, NULL };

    while (true)//start down from Cs to C2(p1,u1)
    {
        p -= 0.5;
        if (p <= C2.p) { break; }
        u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);//point from L1

        //pl1 = Get_H_from_l1(p, u, C2, C1, start);//point from l1

        pl1 = Get_from_l1(p, u, start);//point from l1

        uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

        if (fabs(u - uL2) <= 10 || fabs(pl1.u - uL2) <= 10) {
            IsSearch = true;
            TwoPoints.NL1 = pl1;
            TwoPoints.NL2 = Point{ C2s.p,C2s.u };
            break;
        }

        /////////// Write lines
        int c = round(p);
        if (((c % 747) == 0))
        {
            Write("L1_1.p = " + to_string(p) + "\n" + "L1_1.u = " + to_string(u) + "\n", "L1_1.txt", i);
            Write("cl1_1.p = " + to_string(pl1.p) + "\n" + "cl1_1.u = " + to_string(pl1.u) + "\n", "cl1_1.txt", i);
            Write("L2_1.p = " + to_string(p) + "\n" + "L2_1.u = " + to_string(uL2) + "\n", "L2_1.txt", i);
        }
        ///////////

    }

    if ((p <= Cs.p) && (!IsSearch))//start up from C2(p1,u1) to Cs
    {
        p = C2.p;
        u = L1(p, C2s.u, C2s.p, start.ro1, start.gamma1, start.gamma2, start.c1);// use C2s
        while (true)
        {
            p += 1;
            if (p >= C1.p) { break; }
            u = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);//point from L1

            //pl1 = Get_H_from_l1(p, u, C2, C1, start);//point from l1
            pl1 = Get_from_l1(p, u, start);//point from l1

            uL2 = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

            if (fabs(u - uL2) <= 10) {
                IsSearch = true;
                TwoPoints.NL1 = pl1;
                TwoPoints.NL2 = Point{ C2s.p,C2s.u };
                break;
            }
            /////////// Write lines
            int c = round(p);
            if (((c % 747) == 0))
            {
                Write("L1_2.p = " + to_string(p) + "\n" + "L1_2.u = " + to_string(u) + "\n", "L1_2.txt", i);
                Write("cl1_2.p = " + to_string(pl1.p) + "\n" + "cl1_2.u = " + to_string(pl1.u) + "\n", "cl1_2.txt", i);
                Write("L2_2.p = " + to_string(p) + "\n" + "L2_2.u = " + to_string(uL2) + "\n", "L2_2.txt", i);
            }
            ///////////
        }
    }

    return TwoPoints;
}

bool Check_CONF_D2(START start, Point C1, Point C2, Point Cs, Point C2s)
{
    bool res1 = false;
    bool res2 = false;

    if ((Cs.p - C2.p > 0.0001) && fabs(Cs.u) - fabs(C2.u) < -0.0001)
    {
        res1 = true;
    }

    Point C2sCR{ NULL };
    double M1 = start.u1 / start.c1;
    double ps = C2s.p*((1 + muiquadr(start.gamma1))*(pow(M1, 2)) - muiquadr(start.gamma1));
    double us = C2s.u - (1 - muiquadr(start.gamma1))*start.c1*(M1 - (1 / M1));
    C2sCR = Point{ ps,us };

    if (DOSTAT_Inflow(start, C2sCR) && NEOBHODIM_Inflow(start, C1))
    {
        res2 = true;
    }

    if (res1 && res2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

TwoPoints Search_Conf_D2(START &start, Point &C2, Point &C1, Point &Cs, Point C2s, int i)
{
    return  Search_Conf_D1(start, C2, C1, Cs, C2s, i);
}

bool Check_RES_Inflow_SuperSonic(START start, Point N_L2, Point N_L1)
{
    double p4 = N_L1.p;
    double u4 = N_L1.u;
    double p5 = N_L2.p;
    double u5 = N_L2.u;

    bool correct = false;
    if ((p4 > 0) && (p5 > 0))
    {
        correct = true;
    }
    return correct;

}