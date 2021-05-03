#pragma once
#include "Points_Inflow.h"
#include "Rule_33_34_35.h"
#include "Rule_41_42.h"

bool Check_CONF_DA(START start, Point H, Point C1, Point C2, Point Cs)
{
    bool res1 = false;
    bool res2 = false;

    if ((Cs.p - C2.p < -0.01) && fabs(Cs.u) - fabs(C2.u) > 0.01)
    {
        res1 = true;
    }

    if (DOSTAT_Inflow(start, H) && NEOBHODIM_Inflow(start, C1))
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

TwoPoints Search_Conf_DA(START &start, Point &C2, Point &C1, int i)
{
    return Search_Conf_A1(start, C2, C1, i);
}

bool Check_CONF_D1(START start, Point H, Point C1, Point C2, Point Cs, Point Csl1 )
{
    bool res1 = false;
    bool res2 = false;

    if ((Cs.p - C2.p > 0.0001) && fabs(Cs.u) - fabs(C2.u) < -0.0001)
    {
        res1 = true;
    }


    if (DOSTAT_Inflow(start, Csl1) && NEOBHODIM_Inflow(start, C1))
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

TwoPoints Search_Conf_D1(START &start, Point &C2, Point &C1, int i)
{
    // is true for CC12:
    E.u = start.u2;
    E.p = start.p2;

    // E'(p2',u2')
    Point El2 = Get_from_l2(start.u2, start.p2, E, B, start);
}