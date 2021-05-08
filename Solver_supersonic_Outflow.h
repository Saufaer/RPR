#pragma once
#include "Points_Outflow.h"
#include "Rule_6_7_8_9.h"
#include "Rule_19.h"
#include <climits>


bool DOSTAT_Outflow_C(START start, Point E_default)
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
        if (u1 + FIi(E_default.p, p1, ro1, gamma1) - E_default.u >= 0)
        {
            DOSTAT = true;
        }
    }
    else
    {
        if (u1 + PSIi(E_default.p, p1, gamma1, gamma2, c1) - E_default.u >= 0)
        {
            DOSTAT = true;
        }
    }
    return DOSTAT;
}

bool Check_CONF_CA(START start, Point El2, Point Es, Point B)
{
    bool res1 = false;
    bool res2 = false;

    if ((Es.p - El2.p < -0.01) && (Es.u - El2.u > 0.01))
    {
        res1 = true;
    }

    if (NEOBHODIM_Outflow(start, B) && DOSTAT_Outflow_C(start, El2))
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

TwoPoints Search_Conf_CA(START &start, Point &E, Point &B, int i)//supersonic
{
    return Search_Conf_A(start, E, B, i);
}

bool Check_CONF_CB(START start, Point El2, Point Es, Point B)
{
    if (fabs(Es.p - El2.p) <= 1 && fabs(Es.u - El2.u) <= 1)
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

bool Check_CONF_CC(START start, Point El2, Point Esl2,  Point Es, Point B)
{
    bool res1 = false;
    bool res2 = false;

    if ((Es.p - El2.p > 0.01) && (Es.u - El2.u < -0.01))
    {
        res1 = true;
    }


    if (NEOBHODIM_Outflow(start, B) && DOSTAT_Outflow_C(start, Esl2))
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

        if (fabs(u - uL1) <= 1) {
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

            if (fabs(u - uL1) <= 1) {
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

bool Check_CONF_CC1(START start, Point El2, Point Esl2, Point E, Point Es, Point B)
{
    // is true for CC12:
    E.u = start.u2;
    E.p = start.p2;
    //E'(p2', u2')
    El2 = Get_from_l2(start.u2, start.p2, Es, B, start);

    bool res1 = false;
    bool res2 = false;
    if ((Es.p - El2.p > 0.01) && (Es.u - El2.u < -0.01))
    {
        res1 = true;
    }

    if (NEOBHODIM_Outflow(start, B) && DOSTAT_Outflow_C(start, El2))
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

TwoPoints Search_Conf_CC1(START &start, Point &E, Point &Es, Point &B, int i)//supersonic
{
    // is true for CC12:
    E.u = start.u2;
    E.p = start.p2;

    // E'(p2',u2')
    Point El2 = Get_from_l2(start.u2, start.p2, E, B, start);

    double p = start.p2;
    double u = L2(p, El2.u, El2.p, start.ro2, start.gamma2, start.c2);// use El2 
    Point pl2{ 0,0 };
    double uL1 = 0;
    bool IsSearch = false;

    TwoPoints TwoPoints{ NULL, NULL };

    while (true)//start down from E(p2,u2) to Es
    {

        p += 0.1;

        if (p >= Es.p) { break; }
        u = L2(p, El2.u, El2.p, start.ro2, start.gamma2, start.c2);//point from L2

        pl2 = Get_from_l2(p, u, Es, B, start);//point from l2
        uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
       // cout << "\n pl2.u = " << pl2.u;
        if (fabs(u - uL1) <= 10 || fabs(pl2.u - uL1) <= 10) {
            IsSearch = true;
            TwoPoints.NL1 = pl2;

            TwoPoints.NL2 = Point{ El2.p,El2.u }; // use El2 for result (p4,u4)
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
    ////////////

    if (!IsSearch)//start up from Es to E(p2,u2)
    {

        p = Es.p;
        u = L2(p, El2.u, El2.p, start.ro2, start.gamma2, start.c2);// use El2 
        while (true)
        {
            p -= 0.1;
            if (p < E.p) { break; } // TO point Es ! 
            u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);//point from L2

            pl2 = Get_from_l2(p, u, Es, B, start);//point from l2

            uL1 = L1(p, start.u1, start.p1, start.ro1, start.gamma1, start.gamma2, start.c1);
            //cout << "\n fabs(u - uL1) = " << fabs(u - uL1);
            if (fabs(u - uL1) <= 10 || fabs(pl2.u - uL1) <= 10) {
                IsSearch = true;
                TwoPoints.NL1 = pl2;
                TwoPoints.NL2 = Point{ El2.p,El2.u }; // use El2 for result (p4,u4)
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

bool Check_CONF_CC2(START start, Point El2, Point E, Point Es, Point B)
{
    // is true for CC12:
    E.u = start.u2;
    E.p = start.p2;

    // E'(p2',u2')
    El2 = Get_from_l2(start.u2, start.p2, Es, B, start);

    bool res1 = false;
    bool res2 = false;
    if ((Es.p - El2.p > 0.01) && (Es.u - El2.u < -0.01))
    {
        res1 = true;
    }

    // E*(p2*,u2*)
    Point E2zv{ NULL };
    double M2 = El2.u / start.c2;
    double ps = El2.p*((1 + muiquadr(start.gamma2))*(pow(M2, 2)) - muiquadr(start.gamma2));
    double us = El2.u - (1 - muiquadr(start.gamma2))*start.c2*(M2 - (1 / M2));
    E2zv = Point{ ps,us };

    if (NEOBHODIM_Outflow(start, B) && DOSTAT_Outflow(start, E2zv))
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

TwoPoints Search_Conf_CC2(START &start, Point &E, Point &Es, Point &B, int i)//supersonic
{
    return Search_Conf_CC1(start, E, Es, B, i);
}

bool Check_RES_Outflow_SuperSonic(Point N_L2, Point N_L1)
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