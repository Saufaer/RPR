using namespace std;


#include "Solver_subsonic_Outflow.h"
#include "Solver_subsonic_Inflow.h"
#include "Results.h"
#include <iostream>
#include "windows.h"

void Outflow_subsonic(START  &start, int i)
{
    string res = "";
    Point B(B(start));
    res += "\nB.p = " + to_string(B.p) + "\nB.u = " + to_string(B.u) + "\n";

    Point E(E(start));
    res += "\nE.p = " + to_string(E.p) + "\nE.u = " + to_string(E.u) + "\n";

    Point El2 = Get_from_l2(E.p, E.u, E, B, start);
    res += "\nEl2.p = " + to_string(El2.p) + "\nEl2.u = " + to_string(El2.u) + "\n";

    //Write(res, "Points.txt", i);

    if (Check_CONF_A(start, El2, B)) //subsonic
    {
        TwoPoints NN = Search_Conf_A(start, E, B, i);
        res += GetConfigA(start, NN);
        cout << res;
        Write(res, "Points.txt", i);
    }
    else if (Check_CONF_B(start, El2, B)) //sonic
    {
        Point NL1 = Search_Conf_B(start, El2, B, i);
        res += GetConfigB(start, El2, NL1, E);
        cout << res;
        Write(res, "Points.txt", i);
    }
}

void Outflow_supercsonic(START  &start, int i)
{
    string res = "";
    Point B(B(start));
    res += "\nB.p = " + to_string(B.p) + "\nB.u = " + to_string(B.u) + "\n";

    Point E(E(start));
    res += "\nE.p = " + to_string(E.p) + "\nE.u = " + to_string(E.u) + "\n";

    Point El2 = Get_from_l2(E.p, E.u, E, B, start);
    res += "\nEl2.p = " + to_string(El2.p) + "\nEl2.u = " + to_string(El2.u) + "\n";


    //Point Es = Get_from_l2(E.p, E.u, E, B, start);

    //Write(res, "Points.txt", i);

    //if (Check_CONF_A(start, El2, B)) //subsonic
    //{
    //    TwoPoints NN = Search_Conf_A(start, E, B, i);
    //    res += GetConfigA(start, NN);
    //    cout << res;
    //    Write(res, "Points.txt", i);
    //}
    //else if (Check_CONF_B(start, El2, B)) //sonic
    //{
    //    Point NL1 = Search_Conf_B(start, El2, B, i);
    //    res += GetConfigB(start, El2, NL1, E);
    //    cout << res;
    //    Write(res, "Points.txt", i);
    //}
}



void Inflow_subsonic(START  &start, int i)
{
    string res = "";
    Point C1(C1(start));
    res += "\n\nC1.p = " + to_string(C1.p) + "\nC1.u = " + to_string(C1.u) + "\n";
    Point C2(C2(start));
    res += "\nC2.p = " + to_string(C2.p) + "\nC2.u = " + to_string(C2.u) + "\n";
    Point H(Get_H_from_l1(C2.p, C2.u, C2, C1, start));
    res += "\nH.p = " + to_string(H.p) + "\nH.u = " + to_string(H.u) + "\n";
    //Write(res, "Points.txt", i);

    if (Check_Inflow(start, C1))
    {
        if (Check_CONF_A1(start, H, C1))//It is config A1
        {
            TwoPoints NN = Search_Conf_A1(start, C2, C1, i);
            res += GetConfigA1(start, NN);
            cout << res;
            Write(res, "Points.txt", i);
        }
        else
        {
            Point F(Get_F_from_l1(C2.p, C2.u, C2, C1, start));

            if (Check_CONF_B1(start, F, C1))//It is config B1
            {
                Point NL2 = Search_Conf_B1(start, F, C1, i);
                res += GetConfigB1(start, C2, NL2, F);
                cout << res;
                Write(res, "Points.txt", i);
            }
            else
            {
                Point F2(Get_F2_from_l1(F, C2, start));

                if (Check_CONF_B2(start, F2, C1))//It is config B2
                {
                    Point NL2 = Search_Conf_B2(start, F2, C1, i);
                    res += GetConfigB1(start, C2, NL2, F2);
                    cout << res;
                    Write(res, "Points.txt", i);
                }
            }
        }
    }
}

void Inflow_supersonic(START  &start, int i)
{

}

void Solve_Outflow(START  &start, int i)
{
    double M2 = start.u2 / start.c2;
    if (M2 <= 1)
    {
        Outflow_subsonic(start, i);
    }
    else
    {
        Outflow_supercsonic(start, i);
    }
}

void Solve_Inflow(START  &start, int i)
{
    double M1 = start.u1 / start.c1;
    if (M1 >= -1)
    {
        Inflow_subsonic(start, i);
    }
    else
    {
        Inflow_supersonic(start, i);
    }
}

void Solve(START &start, int i)
{
    start.c2 = sqrtf(start.gamma2*(start.p2 / start.ro2));
    start.c1 = sqrtf(start.gamma1*(start.p1 / start.ro1));

    string c2c1 = "\nc2 = " + to_string(start.c2) + "\n" + "c1 = " + to_string(start.c1) + "\n";
    //Write(c2c1);
    cout << c2c1;
    if (start.u2 > 0 && start.u1 > 0 && start.u2 / start.c2 < 1)
    {
        Solve_Outflow(start, i);
    }
    if (start.u2 < 0 && start.u1 < 0 && start.u1 / start.c1 > -1)
    {
        Solve_Inflow(start, i);
    }
}
