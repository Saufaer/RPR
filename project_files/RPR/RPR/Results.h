#pragma once
using namespace std;


#include "Solver_Outflow.h"
#include "Solver_Inflow.h"
#include <iostream>


/////////////////////////////////////////////////////////////////////////////////////////        OutFlow

string GetNumberFromA(START start, TwoPoints NN)//OutFlow A
{
    string res = "";
    if (NN.NL2.p >= start.p2 && NN.NL1.p >= start.p1)//p5 > p2 && p4 >= p1
    {
        res = "11";
    }
    if (NN.NL2.p >= start.p2 && NN.NL1.p < start.p1)//p5 > p2 && p4 < p1
    {
        res = "12";
    }
    if (NN.NL2.p < start.p2 && NN.NL1.p < start.p1)//p5 < p2 && p4 < p1
    {
        res = "13";
    }
    if (NN.NL2.p < start.p2 && NN.NL1.p >= start.p1)//p5 < p2 && p4 >= p1
    {
        res = "14";
    }
    return res;
}
string GetConfigA(START start, TwoPoints NN)//OutFlow A
{
    string res = "";

    res += "\nCONFIG A - SUBSONIC\n";
    res += "CONFIG NUMBER: " + GetNumberFromA(start, NN) + "\n";
    res += "\n";
    res += "NL1_4.p4 =" + to_string(NN.NL1.p) + "\n";
    res += "NL1_4.u4 =" + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 =" + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 =" + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL2_5.p5 =" + to_string(NN.NL2.p) + "\n";
    res += "NL2_5.u5 =" + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "1.p1 =" + to_string(start.p1) + "\n";
    res += "1.u1 =" + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2 =" + to_string(start.p2) + "\n";
    res += "2.u2 =" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow(NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromB(START start, Point El2, Point NL1, Point E)//OutFlow B
{
    string res = "";
    if (E.p >= start.p2 && NL1.p >= start.p1)//p5 > p2 && p3 >= p1
    {
        res = "15";
    }
    if (E.p >= start.p2 && NL1.p < start.p1)//p5 > p2 && p3 < p1
    {
        res = "16";
    }
    if (E.p < start.p2 && NL1.p < start.p1)//p5 < p2 && p3 < p1
    {
        res = "17";
    }
    if (E.p < start.p2 && NL1.p >= start.p1)//p5 < p2 && p3 >= p1
    {
        res = "18";
    }
    return res;
}

string GetConfigB(START start,Point El2, Point NL1, Point E)//OutFlow B
{
    string res = "";

    res += "\nCONFIG B - SONIC\n";
    res += "CONFIG NUMBER: " + GetNumberFromB(start,  El2,  NL1,  E) + "\n";
    res += "\n";
    res += "El2_4.p4=" + to_string(El2.p) + "\n";
    res += "El2_4.u4=" + to_string(El2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3=" + to_string(NL1.p) + "\n";
    res += "NL1_3.u3=" + to_string(NL1.u) + "\n";
    res += "\n";
    res += "NL1.p'3=" + to_string(NL1.p) + "\n";
    res += "NL1.u'3=" + to_string(NL1.u) + "\n";
    res += "\n";
    res += "E_5.p5=" + to_string(E.p) + "\n";
    res += "E_5.u5=" + to_string(E.u) + "\n";
    res += "\n";
    res += "1.p1=" + to_string(start.p1) + "\n";
    res += "1.u1=" + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2=" + to_string(start.p2) + "\n";
    res += "2.u2=" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow(E, El2));
    return res;
}

/////////////////////////////////////////////////////////////////////////////////////////        InFlow

string GetNumberFromA1(START start, TwoPoints NN)//InFlow A1
{
    string res = "";
    if (NN.NL1.p >= start.p2 && NN.NL2.p < start.p1)//p5 >= p2 && p4 < p1
    {
        res = "21";
    }
    if (NN.NL1.p < start.p2 && NN.NL2.p < start.p1)//p5 < p2 && p4 < p1
    {
        res = "22";
    }
    if (NN.NL1.p < start.p2 && NN.NL2.p >= start.p1)//p5 < p2 && p4 >= p1
    {
        res = "23";
    }
    if (NN.NL1.p >= start.p2 && NN.NL2.p >= start.p1)//p5 >= p2 && p4 >= p1
    {
        res = "24";
    }
    return res;
}

string GetConfigA1(START start, TwoPoints NN)//InFlow A1
{
    string res = "";
    res += "\nCONFIG A1 - SUBSONIC\n";
    res += "CONFIG NUMBER: " + GetNumberFromA1(start, NN) + "\n";
    res += "NL2_4.p4=" + to_string(NN.NL2.p) + "\n";
    res += "NL2_4.u4=" + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "NL1_3.p3=" + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3=" + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_5.p5=" + to_string(NN.NL1.p) + "\n";
    res += "NL1_5.u5=" + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "1.p1=" + to_string(start.p1) + "\n";
    res += "1.u1=" + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2=" + to_string(start.p2) + "\n";
    res += "2.u2=" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow_A(NN.NL2, NN.NL1));
    return res;
}

string GetNumberFromB1(START start, Point NL2, Point F)//InFlow B1
{
    string res = "";
    if (NL2.p >= start.p2 && NL2.p < F.p)//p3 >= p2 && p3 < p5
    {
        res = "25";
    }
    if (NL2.p < start.p2 && NL2.p < F.p)//p3 < p2 && p3 < p5
    {
        res = "26";
    }
    if (NL2.p >= start.p2 && NL2.p >= F.p)//p3 >= p2 && p3 >= p5
    {
        res = "27";
    }
    if (NL2.p < start.p2 && NL2.p >= F.p)//p3 < p2 && p3 >= p5
    {
        res = "28";
    }

    return res;
}

string GetConfigB1(START start, Point C2, Point NL2, Point F)//InFlow B1
{
    string res = "";
    res += "\nCONFIG B1 - SUBSONIC\n";
    res += "CONFIG NUMBER: " + GetNumberFromB1(start, NL2, F) + "\n";
    res += "C2_4.p4=" + to_string(C2.p) + "\n";
    res += "C2_4.u4=" + to_string(C2.u) + "\n";
    res += "\n";
    res += "NL2_3.p3=" + to_string(NL2.p) + "\n";
    res += "NL2_3.u3=" + to_string(NL2.u) + "\n";
    res += "\n";
    res += "NL2_31.p'3=" + to_string(NL2.p) + "\n";
    res += "NL2_31.u'3=" + to_string(NL2.u) + "\n";
    res += "\n";
    res += "F_5.p5=" + to_string(F.p) + "\n";
    res += "F_5.u5=" + to_string(F.u) + "\n";
    res += "\n";
    res += "1.p1=" + to_string(start.p1) + "\n";
    res += "1.u1=" + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2=" + to_string(start.p2) + "\n";
    res += "2.u2=" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow_B(C2, F));
    return res;
}

string GetNumberFromB2(START start, Point NL2, Point F2)//InFlow B2
{
    string res = "";
    if (NL2.p >= start.p2 && NL2.p < F2.p)//p3 >= p2 && p3 < p5
    {
        res = "25";
    }
    if (NL2.p < start.p2 && NL2.p < F2.p)//p3 < p2 && p3 < p5
    {
        res = "26";
    }
    if (NL2.p >= start.p2 && NL2.p >= F2.p)//p3 >= p2 && p3 >= p5
    {
        res = "27";
    }
    if (NL2.p < start.p2 && NL2.p >= F2.p)//p3 < p2 && p3 >= p5
    {
        res = "28";
    }

    return res;
}

string GetConfigB2(START start, Point C2, Point NL2, Point F2)//InFlow B2
{
    string res = "";
    res += "\nCONFIG B2\n";
    res += "CONFIG NUMBER: " + GetNumberFromB2(start, NL2, F2) + "\n";
    res += "C2_4.p4=" + to_string(C2.p) + "\n";
    res += "C2_4.u4=" + to_string(C2.u) + "\n";
    res += "\n";
    res += "NL2_3.p3=" + to_string(NL2.p) + "\n";
    res += "NL2_3.u3=" + to_string(NL2.u) + "\n";
    res += "\n";
    res += "NL2_31.p'3=" + to_string(NL2.p) + "\n";
    res += "NL2_31.u'3=" + to_string(NL2.u) + "\n";
    res += "\n";
    res += "F2_5.p5=" + to_string(F2.p) + "\n";
    res += "F2_5.u5=" + to_string(F2.u) + "\n";
    res += "\n";
    res += "1.p1=" + to_string(start.p1) + "\n";
    res += "1.u1=" + to_string(start.u1) + "\n";
    res += "\n";
    res += "2.p2=" + to_string(start.p2) + "\n";
    res += "2.u2=" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow_B(C2, F2));
    return res;
}