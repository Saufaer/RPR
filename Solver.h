using namespace std;


#include "Solver_subsonic_Outflow.h"
#include "Solver_subsonic_Inflow.h"
#include "Solver_supersonic_Outflow.h"
#include "Solver_supersonic_Inflow.h"
#include "Results.h"
#include <iostream>
#include "windows.h"

void Outflow_subsonic(START  &start, int i)
{
    string res = "\n\n OUTFLOW SUBSONIC \n";
    Point B(B(start));
    res += "\nB.p = " + to_string(B.p) + "\nB.u = " + to_string(B.u) + "\n";

    Point E(E(start));
    res += "\nE.p = " + to_string(E.p) + "\nE.u = " + to_string(E.u) + "\n";

    Point El2 = Get_from_l2(E.p, E.u, E, B, start);
    res += "\nEl2.p = " + to_string(El2.p) + "\nEl2.u = " + to_string(El2.u) + "\n";

    //Write(res, "Points.txt", i);
    bool Finish = false;

    if (Check_CONF_A(start, El2, B)) //subsonic
    {
        TwoPoints NN = Search_Conf_A(start, E, B, i);
        if (Check_RES_Outflow(NN.NL2, NN.NL1))
        {
            res += GetConfigA(start, NN);
            cout << res;
            Write(res, "Points.txt", i);
            Finish = true;
        }

    }
    if (!Finish)
    {
        if (Check_CONF_B(start, El2, B)) //sonic
        {
            Point NL1 = Search_Conf_B(start, El2, B, i);
            if (Check_RES_Outflow(E, El2))
            {
                res += GetConfigB(start, El2, NL1, E);
                cout << res;
                Write(res, "Points.txt", i);
                Finish = true;
            }
        }
    }

    if (!Finish)
    { 
        Write(res, "Points.txt", i);
        cout << "\n Possible configuration for Outflow not found, start conditions unconsists, skip solving";
        cout << res;
    }
}

void Outflow_supercsonic(START  &start, int i)
{
    string res = "\n\n OUTFLOW SUPERSONIC \n";

    res += "\np2.p = " + to_string(start.p2) + "\nu2.u = " + to_string(start.u2) + "\n";
    Point B(B(start));
    res += "\nB.p = " + to_string(B.p) + "\nB.u = " + to_string(B.u) + "\n";

    Point E(E(start));
    res += "\nE.p = " + to_string(E.p) + "\nE.u = " + to_string(E.u) + "\n";

    Point El2 = Get_from_l2(E.p, E.u, E, B, start);
    res += "\nEl2.p = " + to_string(El2.p) + "\nEl2.u = " + to_string(El2.u) + "\n";

    Point Es(Es(start));
    res += "\nEs.p = " + to_string(Es.p) + "\nEs.u = " + to_string(Es.u) + "\n";

    Point Esl2 = Get_from_l2(Es.p, Es.u, Es, B, start);
    res += "\nEsl2.p = " + to_string(Esl2.p) + "\nEsl2.u = " + to_string(Esl2.u) + "\n";

    bool Finish = false;
    if (Check_CONF_CA(start,E, El2, Es, B))
    {
        TwoPoints NN = Search_Conf_CA(start, Es, B, i);

        if (Check_RES_Outflow(NN.NL2, NN.NL1))
        {
            res += GetConfigCA(start, NN);
            cout << res;
            Write(res, "Points.txt", i);
            Finish = true;
        }
    }
    if (!Finish)
    {
        if (Check_CONF_CB(start, El2, E, B))
        {
            Point NL1 = Search_Conf_CB(start, El2, B, i);
            if (Check_RES_Outflow(E, El2))
            {
                res += GetConfigCB(start, El2, NL1, E);
                cout << res;
                Write(res, "Points.txt", i);
                Finish = true;
            }

        }
    }
    if (!Finish)
    {
        if (Check_CONF_CC(start, E, Esl2, Es, B))
        {
            TwoPoints NN = Search_Conf_CC(start, E, Es, B, i);
            if (Check_RES_Outflow(NN.NL2, NN.NL1))
            {
                res += GetConfigCC(start, NN);
                cout << res;
                Write(res, "Points.txt", i);
                Finish = true;
            }
        }
    }
    if (!Finish)
    {
        if (Check_CONF_CC1(start, El2, Esl2, E, Es, B))
        {
            TwoPoints NN = Search_Conf_CC1(start, E, Es, B, i);
            if (Check_RES_Outflow(NN.NL2, NN.NL1))
            {
                res += GetConfigCC1(start, NN);
                cout << res;
                Write(res, "Points.txt", i);
                Finish = true;
            }

        }
    }
    if (!Finish)
    {
        if (Check_CONF_CC2(start, El2, E, Es, B))
        {
            TwoPoints NN = Search_Conf_CC2(start, E, Es, B, i);
            if (Check_RES_Outflow(NN.NL2, NN.NL1))
            {
                res += GetConfigCC2(start, NN);
                cout << res;
                Write(res, "Points.txt", i);
                Finish = true;
            }
        }
    }
    if (!Finish) {
        Write(res, "Points.txt", i);
        cout << "\n Possible configuration for Outflow not found, start conditions unconsists, skip solving";
        cout << res;
    }
}



void Inflow_subsonic(START  &start, int i)
{
    string res = "\n\n INFLOW SUBSONIC \n";
    Point C1(C1(start));
    res += "\nC1.p = " + to_string(C1.p) + "\nC1.u = " + to_string(C1.u) + "\n";
    Point C2(C2(start));
    res += "\nC2.p = " + to_string(C2.p) + "\nC2.u = " + to_string(C2.u) + "\n";
    //Point H(Get_H_from_l1(C2.p, C2.u, C2, C1, start));
    Point H(Get_from_l1(C2.p, C2.u, start));
    res += "\nH.p = " + to_string(H.p) + "\nH.u = " + to_string(H.u) + "\n";
    Point F(Get_F_from_l1(C2.p, C2.u, C2, C1, start));
    res += "\nF.p = " + to_string(F.p) + "\nF.u = " + to_string(F.u) + "\n";
    Point F2(Get_F2_from_l1(F, C2, start));
    res += "\nF2.p = " + to_string(F2.p) + "\nF2.u = " + to_string(F2.u) + "\n";
    //Write(res, "Points.txt", i);
    bool Finish = false;
    if (Check_CONF_A1(start, H, C1))//It is config A1
    {
        TwoPoints NN = Search_Conf_A1(start, C2, C1, i);
        if (Check_RES_Inflow(start, NN.NL2, NN.NL1))
        {
            res += GetConfigA1(start, NN);
            cout << res;
            Write(res, "Points.txt", i);
            Finish = true;
        }
    }
    if (!Finish)
    {
        if (Check_CONF_B1(start, F, C1))//It is config B1
        {
            Point NL2 = Search_Conf_B1(start, F, C1, i);
            if (Check_RES_Inflow_B(C2, F))
            {
                res += GetConfigB1(start, C2, NL2, F);
                cout << res;
                Write(res, "Points.txt", i);
                Finish = true;
            }
        }
    }
    if (!Finish)
    {
        if (Check_CONF_B2(start, F2, C1))//It is config B2
        {
            Point NL2 = Search_Conf_B2(start, F2, C1, i);
            if (Check_RES_Inflow_B(C2, F2))
            {
                res += GetConfigB2(start, C2, NL2, F2);
                cout << res;
                Write(res, "Points.txt", i);
                Finish = true;
            }
        }
    }
    if (!Finish)
    {
        Write(res, "Points.txt", i);
        cout << "\n Possible configuration for Inflow not found, start conditions unconsists, skip solving";
        cout << res;
    }
}

void Inflow_supersonic(START  &start, int i)
{
    string res = "\n\n INFLOW SUPERSONIC \n";
    Point C1(C1(start));
    res += "\nC1.p = " + to_string(C1.p) + "\nC1.u = " + to_string(C1.u) + "\n";
    Point C2(C2(start));
    res += "\nC2.p = " + to_string(C2.p) + "\nC2.u = " + to_string(C2.u) + "\n";
    Point Cs(Cs(start));
    res += "\nCs.p = " + to_string(Cs.p) + "\nCs.u = " + to_string(Cs.u) + "\n";
    Point Hs(Get_from_l1(Cs.p,Cs.u,start));
    res += "\nHs.p = " + to_string(Hs.p) + "\nHs.u = " + to_string(Hs.u) + "\n";
    Point C2s(Get_from_l1(start.p1, start.u1, start));
    res += "\nC2s.p = " + to_string(C2s.p) + "\nC2s.u = " + to_string(C2s.u) + "\n";

    bool Finish = false;
    if (Check_CONF_DA(start, C1, C2, Cs, Hs))
    {
        TwoPoints NN = Search_Conf_DA(start, Cs, C1, i);
        if (Check_RES_Inflow_SuperSonic(start, NN.NL2, NN.NL1))
        {
            res += GetConfigDA(start, NN);
            cout << res;
            Write(res, "Points.txt", i);
            Finish = true;
        }
    }
    if (!Finish) 
    {
        if (Check_CONF_D1(start, C1, C2, Cs, C2s))
        {
            TwoPoints NN = Search_Conf_D1(start, C2, C1, Cs, C2s, i);
            if (Check_RES_Inflow_SuperSonic(start, NN.NL2, NN.NL1))
            {
            res += GetConfigD1(start, NN);
            cout << res;
            Write(res, "Points.txt", i);
            Finish = true;
            }
        }
    }
    if (!Finish)
    {
        if (Check_CONF_D2(start, C1, C2, Cs, C2s))
        {
            TwoPoints NN = Search_Conf_D2(start, C2, C1, Cs, C2s, i);
            if (Check_RES_Inflow_SuperSonic(start, NN.NL2, NN.NL1))
            {
                res += GetConfigD2(start, NN);
                cout << res;
                Write(res, "Points.txt", i);
                Finish = true;
            }
        }
    }
    if (!Finish)
    {
        Write(res, "Points.txt", i);
        cout << "\n Possible configuration for Inflow not found, start conditions unconsists, skip solving";
        cout << res;
    }


}

void Solve_Outflow(START  &start, int i)
{
    double M2 = start.u2 / start.c2;
    cout << "M2 = " << M2;
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
    cout << "M1 = "<< M1;
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

    string c2c1 = "\n\nc2 = " + to_string(start.c2) + "\n" + "c1 = " + to_string(start.c1) + "\n";
    //Write(c2c1);
    cout << c2c1;
    if (start.u2 >= 0 && start.u1 >= 0)
    {
        Solve_Outflow(start, i);
    }
    if (start.u2 < 0 && start.u1 < 0)
    {
        Solve_Inflow(start, i);
    }
}
