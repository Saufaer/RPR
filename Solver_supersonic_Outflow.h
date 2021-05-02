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
