#pragma once
#include "Points_Outflow.h"
#include "Rule_6_7_8_9.h"
#include "Rule_19.h"
#include <climits>




bool Check_CONF_CA(START start, Point El2, Point Es, Point B)
{
    if ((Es.p < El2.p) && (Es.u > El2.u))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Check_CONF_CB(START start, Point El2, Point Es, Point B)
{
    if ((Es.p - El2.p) <= 0.0001 && (Es.u - El2.u) <= 0.0001)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Check_CONF_CC(START start, Point El2, Point Es, Point B)
{
    if ((Es.p > El2.p) && (Es.u < El2.u))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Check_CONF_CC1(START start, Point El2, Point Es, Point B)
{
    if (L1(El2.p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1) - El2.u > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Check_CONF_CC2(START start, Point El2, Point Es, Point B)
{
    if (L1(El2.p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1) - El2.u > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
TwoPoints Search_Conf_A(START &start, Point &E, Point &B, int i)//subsonic
{

    double p = start.p2;
    double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
    Point pl2{ 0,0 };
    double uL1 = 0;
    bool IsSearch = false;

    TwoPoints TwoPoints{ NULL, NULL };

    while (true)//start down from (p2,u2) to B
    {

        p += 0.1;
        if (p >= B.p) { break; }
        u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//point from L2

        pl2 = Get_from_l2(p, u, E, B, start);//point from l2
        uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

        if (fabs(pl2.u - uL1) <= 1) {
            IsSearch = true;
            TwoPoints.NL1 = pl2;

            TwoPoints.NL2 = Point{ p,u };
            break;
        }

        /////////// Write lines
        int c = round(p);
        if (((c % 474) == 0) && (pl2.p > 0))
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
            p -= 0.1;
            if (p < E.p) { break; }
            u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//point from L2

            pl2 = Get_from_l2(p, u, E, B, start);//point from l2

            uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

            if (fabs(pl2.u - uL1) <= 1) {
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

Point Search_Conf_B(START &start, Point &El2, Point &B, int i)//sonic
{
    double p4 = El2.p;
    double u4 = El2.u;

    double p = p4;
    double u = u4;

    Point N_B{ NULL };
    double uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);

    while (true)
    {

        if (fabs(u - uL1) <= 5) { break; }
        p -= 1;
        uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
        u = Addict_l2(p, p4, u4, start.c2, start.gamma2);

        /////////// Write lines
        int c = round(p);
        if (((c % 114) == 0))
        {
            Write("L1_1.p = " + to_string(p) + "\n" + "L1_1.u = " + to_string(uL1) + "\n", "L1_1.txt", i);
            Write("l2.p = " + to_string(p) + "\n" + "l2.u = " + to_string(u) + "\n", "l2.txt", i);
        }
        ///////////
    }

    N_B = Point{ p,u };

    return N_B;

}

bool Check_RES_Outflow(Point N_L2, Point N_L1)
{
    double p4 = N_L1.p;
    double u4 = N_L1.u;
    double p5 = N_L2.p;
    double u5 = N_L2.u;

    bool correct = false;
    if ((p4 <= p5) && (u4 >= u5))
    {
        correct = true;
    }
    return correct;
}