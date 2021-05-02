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

TwoPoints Search_Conf_CA(START &start, Point &E, Point &B, int i)//supersonic
{
    return Search_Conf_A(start, E, B, i);
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

Point Search_Conf_CB(START &start, Point &El2, Point &B, int i)//supersonic
{
    return Search_Conf_B(start, El2, B, i);
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

TwoPoints Search_Conf_CC(START &start, Point &E, Point &Es, Point &B, int i)//supersonic
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

    if (!IsSearch)//start up from (p2,u2) to Es
    {

        p = start.p2;
        u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
        while (true)
        {
            p -= 0.1;
            if (p < Es.p) { break; } // TO point Es ! 
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
