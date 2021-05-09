#pragma once
using namespace std;


#include "Solver_subsonic_Outflow.h"
#include "Solver_subsonic_Inflow.h"
#include "Solver_supersonic_Outflow.h"
#include "Solver_supersonic_Inflow.h"
#include <iostream>


/////////////////////////////////////////////////////////////////////////////////////////        OutFlow subsonic

string GetNumberFromA(START start, TwoPoints NN)//OutFlow A
{
    string res = "";
    if (NN.NL2.p >= start.p2 && NN.NL1.p >= start.p1)//p5 > p2 && p4 >= p1
    {
        res = "number 1: S<-BTS->";
    }
    if (NN.NL2.p >= start.p2 && NN.NL1.p < start.p1)//p5 > p2 && p4 < p1
    {
        res = "number 2: S<-BTR->";
    }
    if (NN.NL2.p < start.p2 && NN.NL1.p < start.p1)//p5 < p2 && p4 < p1
    {
        res = "number 3: R<-BTR->";
    }
    if (NN.NL2.p < start.p2 && NN.NL1.p >= start.p1)//p5 < p2 && p4 >= p1
    {
        res = "number 4: R<-BTS->";
    }
    return res;
}
string GetConfigA(START start, TwoPoints NN)//OutFlow A
{
    string res = "";

    res += "\n CONFIG A " + GetNumberFromA(start, NN) + "\n";
    res += "\n";
    res += "NL1_4.p4 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_4.u4 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL2_5.p5 = " + to_string(NN.NL2.p) + "\n";
    res += "NL2_5.u5 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow(NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromB(START start, Point El2, Point NL1, Point E)//OutFlow B
{
    string res = "";
    if (E.p >= start.p2 && NL1.p >= start.p1)//p5 > p2 && p3 >= p1
    {
        res = "number 1: S<-BR<-TS->";
    }
    if (E.p >= start.p2 && NL1.p < start.p1)//p5 > p2 && p3 < p1
    {
        res = "number 2: S<-BR<-TR->";
    }
    if (E.p < start.p2 && NL1.p < start.p1)//p5 < p2 && p3 < p1
    {
        res = "number 3: R<-BR<-TR->";
    }
    if (E.p < start.p2 && NL1.p >= start.p1)//p5 < p2 && p3 >= p1
    {
        res = "number 4: R<-BR<-TS->";
    }
    return res;
}

string GetConfigB(START start,Point El2, Point NL1, Point E)//OutFlow B
{
    string res = "";

    res += "\n CONFIG B " + GetNumberFromB(start,  El2,  NL1,  E) + "\n";
    res += "\n";
    res += "El2_4.p4 = " + to_string(El2.p) + "\n";
    res += "El2_4.u4 = " + to_string(El2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NL1.u) + "\n";
    res += "\n";
    res += "NL1.p'3 = " + to_string(NL1.p) + "\n";
    res += "NL1.u'3 = " + to_string(NL1.u) + "\n";
    res += "\n";
    res += "E_5.p5 = " + to_string(E.p) + "\n";
    res += "E_5.u5 = " + to_string(E.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow(E, El2));
    return res;
}

////////////// OUTFLOW Supersonic

string GetNumberFromCA(START start, TwoPoints NN)//OutFlow CA
{
    string res = "";
    if (NN.NL2.p >= start.p2 && NN.NL1.p >= start.p1)//p5 >= p2 && p4 >= p1
    {
        res = "number 1: S<-BTS->";
    }
    if (NN.NL2.p >= start.p2 && NN.NL1.p < start.p1)//p5 >= p2 && p4 < p1
    {
        res = "number 2: S<-BTR->";
    }
    return res;
}
string GetConfigCA(START start, TwoPoints NN)//OutFlow CA
{
    string res = "";

    res += "\n CONFIG CA " + GetNumberFromCA(start, NN) + "\n";
    res += "\n";
    res += "NL1_4.p4 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_4.u4 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL2_5.p5 = " + to_string(NN.NL2.p) + "\n";
    res += "NL2_5.u5 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow_SuperSonic(NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromCB(START start, Point El2, Point NL1, Point E)//OutFlow CB
{
    string res = "";
    if (E.p >= start.p2 && NL1.p >= start.p1)//p5 >= p2 && p3 >= p1
    {
        res = "number 1: F<-BR<-TS->";
    }
    if (E.p >= start.p2 && NL1.p < start.p1)//p5 >= p2 && p3 < p1
    {
        res = "number 2: F<-BR<-TR->";
    }
    return res;
}

string GetConfigCB(START start, Point El2, Point NL1, Point E)//OutFlow CB
{
    string res = "";

    res += "\n CONFIG CB " + GetNumberFromCB(start, El2, NL1, E) + "\n";
    res += "\n";
    res += "El2_4.p4 = " + to_string(El2.p) + "\n";
    res += "El2_4.u4 = " + to_string(El2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NL1.u) + "\n";
    res += "\n";
    res += "NL1.p'3 = " + to_string(NL1.p) + "\n";
    res += "NL1.u'3 = " + to_string(NL1.u) + "\n";
    res += "\n";
    res += "E_5.p5 = " + to_string(E.p) + "\n";
    res += "E_5.u5 = " + to_string(E.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow_SuperSonic(E, El2));
    return res;
}

string GetNumberFromCC(START start, TwoPoints NN)//OutFlow CC
{
    string res = "";
    if (NN.NL2.p >= start.p2 && NN.NL1.p >= start.p1)//p5 >= p2 && p4 >= p1
    {
        res = "number 1: S<-BTS->";
    }
    if (NN.NL2.p >= start.p2 && NN.NL1.p < start.p1)//p5 >= p2 && p4 < p1
    {
        res = "number 2: S<-BTR->";
    }
    return res;
}
string GetConfigCC(START start, TwoPoints NN)//OutFlow CC
{
    string res = "";

    res += "\n CONFIG CC " + GetNumberFromCC(start, NN) + "\n";
    res += "\n";
    res += "NL1_4.p4 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_4.u4 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL2_5.p5 = " + to_string(NN.NL2.p) + "\n";
    res += "NL2_5.u5 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow_SuperSonic(NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromCC1(START start, TwoPoints NN)//OutFlow CC1
{
    string res = "";
    if (NN.NL1.p <= NN.NL2.p && NN.NL1.p >= start.p1)//p3 <= p4 && p3 >= p1
    {
        res = "number 1: BR<-TS->";
    }
    if (NN.NL1.p <= NN.NL2.p && NN.NL1.p < start.p1)//p3 <= p4 && p3 < p1
    {
        res = "number 2: BR<-TR->";
    }
    return res;
}
string GetConfigCC1(START start, TwoPoints NN)//OutFlow CC1
{
    string res = "";

    res += "\n CONFIG CC1 " + GetNumberFromCC1(start, NN) + "\n";
    res += "\n";
    res += "NL1_4.p4 = " + to_string(NN.NL2.p) + "\n";
    res += "NL1_4.u4 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3' = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3' = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow_SuperSonic(NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromCC2(START start, TwoPoints NN)//OutFlow CC2
{
    string res = "";
    if (NN.NL1.p >= NN.NL2.p && NN.NL1.p >= start.p1)//p3 >= p4 && p3 >= p1
    {
        res = "number 1: BS<-TS->";
    }
    if (NN.NL1.p >= NN.NL2.p && NN.NL1.p < start.p1)//p3 >= p4 && p3 < p1
    {
        res = "number 2: BS<-TR->";
    }
    return res;
}
string GetConfigCC2(START start, TwoPoints NN)//OutFlow CC2
{
    string res = "";

    res += "\n CONFIG CC2 " + GetNumberFromCC2(start, NN) + "\n";
    res += "\n";
    res += "NL1_4.p4 = " + to_string(NN.NL2.p) + "\n";
    res += "NL1_4.u4 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3' = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3' = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow_SuperSonic(NN.NL2, NN.NL1));
    return res;
}
/////////////////////////////////////////////////////////////////////////////////////////        InFlow subsonic

string GetNumberFromA1(START start, TwoPoints NN)//InFlow A1
{
    string res = "";
    if (NN.NL1.p >= start.p2 && NN.NL2.p < start.p1)//p5 >= p2 && p4 < p1
    {
        res = "number 1: S<-TBR->";
    }
    if (NN.NL1.p < start.p2 && NN.NL2.p < start.p1)//p5 < p2 && p4 < p1
    {
        res = "number 2: R<-TBR->";
    }
    if (NN.NL1.p < start.p2 && NN.NL2.p >= start.p1)//p5 < p2 && p4 >= p1
    {
        res = "number 3: R<-TBS->";
    }
    if (NN.NL1.p >= start.p2 && NN.NL2.p >= start.p1)//p5 >= p2 && p4 >= p1
    {
        res = "number 4: S<-TBS->";
    }
    return res;
}

string GetConfigA1(START start, TwoPoints NN)//InFlow A1
{
    string res = "";
    res += "\n CONFIG A1 " + GetNumberFromA1(start, NN) + "\n";
    res += "\n";
    res += "NL2_4.p4 = " + to_string(NN.NL2.p) + "\n";
    res += "NL2_4.u4 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_5.p5 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_5.u5 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow(start, NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromB1(START start, Point NL2, Point F)//InFlow B1
{
    string res = "";
    if (NL2.p >= start.p2 && NL2.p < F.p)//p3 >= p2 && p3 < p5
    {
        res = "number 1: S<-TR->BR->";
    }
    if (NL2.p < start.p2 && NL2.p < F.p)//p3 < p2 && p3 < p5
    {
        res = "number 2: R<-TR->BR->";
    }
    if (NL2.p >= start.p2 && NL2.p >= F.p)//p3 >= p2 && p3 >= p5
    {
        res = "number 3: S<-TS->BR->";
    }
    if (NL2.p < start.p2 && NL2.p >= F.p)//p3 < p2 && p3 >= p5
    {
        res = "number 4: R<-TS->BR->";
    }

    return res;
}

string GetConfigB1(START start, Point C2, Point NL2, Point F)//InFlow B1
{
    string res = "";

    res += "\n CONFIG B1 " + GetNumberFromB1(start, NL2, F) + "\n";
    res += "\n";
    res += "C2_4.p4 = " + to_string(C2.p) + "\n";
    res += "C2_4.u4 = " + to_string(C2.u) + "\n";
    res += "\n";
    res += "NL2_3.p3 = " + to_string(NL2.p) + "\n";
    res += "NL2_3.u3 = " + to_string(NL2.u) + "\n";
    res += "\n";
    res += "NL2_31.p'3 = " + to_string(NL2.p) + "\n";
    res += "NL2_31.u'3 = " + to_string(NL2.u) + "\n";
    res += "\n";
    res += "F_5.p5 = " + to_string(F.p) + "\n";
    res += "F_5.u5 = " + to_string(F.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow_B(C2, F));
    return res;
}

string GetNumberFromB2(START start, Point NL2, Point F2)//InFlow B2
{
    string res = "";
    if (NL2.p >= start.p2 && NL2.p < F2.p)//p3 >= p2 && p3 < p5
    {
        res = "number 1: S<-TR->BR->";
    }
    if (NL2.p < start.p2 && NL2.p < F2.p)//p3 < p2 && p3 < p5
    {
        res = "number 2: R<-TR->BR->";
    }
    if (NL2.p >= start.p2 && NL2.p >= F2.p)//p3 >= p2 && p3 >= p5
    {
        res = "number 3: S<-TS->BR->";
    }
    if (NL2.p < start.p2 && NL2.p >= F2.p)//p3 < p2 && p3 >= p5
    {
        res = "number 4: R<-TS->BR->";
    }

    return res;
}

string GetConfigB2(START start, Point C2, Point NL2, Point F2)//InFlow B2
{
    string res = "";

    res += "\n CONFIG B2 " + GetNumberFromB2(start, NL2, F2) + "\n";
    res += "\n";
    res += "C2_4.p4 = " + to_string(C2.p) + "\n";
    res += "C2_4.u4 = " + to_string(C2.u) + "\n";
    res += "\n";
    res += "NL2_3.p3 = " + to_string(NL2.p) + "\n";
    res += "NL2_3.u3 = " + to_string(NL2.u) + "\n";
    res += "\n";
    res += "NL2_31.p'3 = " + to_string(NL2.p) + "\n";
    res += "NL2_31.u'3 = " + to_string(NL2.u) + "\n";
    res += "\n";
    res += "F2_5.p5 = " + to_string(F2.p) + "\n";
    res += "F2_5.u5 = " + to_string(F2.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow_B(C2, F2));
    return res;
}

//////////////////////////////////////      InFlow supersonic

string GetNumberFromDA(START start, TwoPoints NN)//InFlow DA
{
    string res = "";
    if (NN.NL1.p < start.p2 && NN.NL2.p >= start.p1)//p5 < p2 && p4 >= p1
    {
        res = "number 1: R<-TBS->";
    }
    if (NN.NL1.p >= start.p2 && NN.NL2.p >= start.p1)//p5 >= p2 && p4 >= p1
    {
        res = "number 2: S<-TBS->";
    }
    return res;
}

string GetConfigDA(START start, TwoPoints NN)//InFlow DA
{
    string res = "";

    res += "\n CONFIG DA " + GetNumberFromDA(start, NN) + "\n";
    res += "\n";
    res += "NL2_4.p4 = " + to_string(NN.NL2.p) + "\n";
    res += "NL2_4.u4 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_5.p5 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_5.u5 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow(start, NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromD1(START start, TwoPoints NN)//InFlow D1
{
    string res = "";
    if (NN.NL1.p < start.p2 && NN.NL1.p <= NN.NL2.p)//p3 < p2 && p3 <= p5
    {
        res = "number 1: S<-TR->B";
    }
    if (NN.NL1.p >= start.p2 && NN.NL1.p <= NN.NL2.p)//p3 >= p2 && p3 <= p5
    {
        res = "number 2: R<-TR->B";
    }
    return res;
}

string GetConfigD1(START start, TwoPoints NN)//InFlow D1
{
    string res = "";

    res += "\n CONFIG D1 " + GetNumberFromD1(start, NN) + "\n";
    res += "\n";
    res += "NL2_4.p5 = " + to_string(NN.NL2.p) + "\n";
    res += "NL2_4.u5 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_5.p3' = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_5.u3' = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow(start, NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromD2(START start, TwoPoints NN)//InFlow D2
{
    string res = "";
    if (NN.NL1.p < start.p2 && NN.NL1.p >= NN.NL2.p)//p3 < p2 && p3 >= p5
    {
        res = "number 1: S<-TS->B";
    }
    if (NN.NL1.p >= start.p2 && NN.NL1.p >= NN.NL2.p)//p3 >= p2 && p3 >= p5
    {
        res = "number 2: R<-TS->RB";
    }
    return res;
}

string GetConfigD2(START start, TwoPoints NN)//InFlow D2
{
    string res = "";

    res += "\n CONFIG D2 " + GetNumberFromD2(start, NN) + "\n";
    res += "\n";
    res += "NL2_4.p5 = " + to_string(NN.NL2.p) + "\n";
    res += "NL2_4.u5 = " + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_5.p3' = " + to_string(NN.NL1.p) + "\n";
    res += "NL1_5.u3' = " + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "1.p1 = " + to_string(start.p1) + "\n";
    res += "1.u1 = " + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 = " + to_string(start.p2) + "\n";
    res += "2.u2 = " + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow(start, NN.NL2, NN.NL1));
    return res;
}