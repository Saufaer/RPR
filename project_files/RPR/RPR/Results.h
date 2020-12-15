#pragma once
using namespace std;


#include "Solver_Outflow.h"
#include "Solver_Inflow.h"
#include <iostream>

string GetConfigA(START start, TwoPoints NN)//OutFlow
{
    string res = "";

    res += "\nCONFIG A";
    res += "\n";
    res += "NL1_4.p4 =" + to_string(NN.NL1.p) + "\n";
    res += "NL1_4.u4 =" + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL1_3.p3 =" + to_string(NN.NL1.p) + "\n";
    res += "NL1_3.u3 =" + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "NL2.p5 =" + to_string(NN.NL2.p) + "\n";
    res += "NL2.u5 =" + to_string(NN.NL2.u) + "\n";
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

string GetConfigB(START start,Point El2, Point NL1, Point E)//OutFlow
{
    string res = "";

    res += "\nCONFIG B";
    res += "\n";
    res += "p4=" + to_string(El2.p) + "\n";
    res += "u4=" + to_string(El2.u) + "\n";
    res += "\n";
    res += "p3=" + to_string(NL1.p) + "\n";
    res += "u3=" + to_string(NL1.u) + "\n";
    res += "\n";
    res += "p'3=" + to_string(NL1.p) + "\n";
    res += "u'3=" + to_string(NL1.u) + "\n";
    res += "\n";
    res += "p5=" + to_string(E.p) + "\n";
    res += "u5=" + to_string(E.u) + "\n";
    res += "\n";
    res += "p1=" + to_string(start.p1) + "\n";
    res += "u1=" + to_string(start.u1) + "\n";
    res += "\n";
    res += "p2=" + to_string(start.p2) + "\n";
    res += "u2=" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Outflow(E, El2));
    return res;
}

string GetConfigA1(START start, TwoPoints NN)//InFlow
{
    string res = "";
    res += "\nCONFIG A1\n";
    res += "p4=" + to_string(NN.NL2.p) + "\n";
    res += "u4=" + to_string(NN.NL2.u) + "\n";
    res += "\n";
    res += "p3=" + to_string(NN.NL1.p) + "\n";
    res += "u3=" + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "p5=" + to_string(NN.NL1.p) + "\n";
    res += "u5=" + to_string(NN.NL1.u) + "\n";
    res += "\n";
    res += "p1=" + to_string(start.p1) + "\n";
    res += "u1=" + to_string(start.u1) + "\n";
    res += "\n";
    res += "p2=" + to_string(start.p2) + "\n";
    res += "u2=" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow_A(NN.NL2, NN.NL1));
    return res;
}

string GetConfigB1(START start, Point C2, Point NL2, Point F)//InFlow
{
    string res = "";
    res += "\nCONFIG B1\n";
    res += "p4=" + to_string(C2.p) + "\n";
    res += "u4=" + to_string(C2.u) + "\n";
    res += "\n";
    res += "p3=" + to_string(NL2.p) + "\n";
    res += "u3=" + to_string(NL2.u) + "\n";
    res += "\n";
    res += "p'3=" + to_string(NL2.p) + "\n";
    res += "u'3=" + to_string(NL2.u) + "\n";
    res += "\n";
    res += "p5=" + to_string(F.p) + "\n";
    res += "u5=" + to_string(F.u) + "\n";
    res += "\n";
    res += "p1=" + to_string(start.p1) + "\n";
    res += "u1=" + to_string(start.u1) + "\n";
    res += "\n";
    res += "p2=" + to_string(start.p2) + "\n";
    res += "u2=" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow_B(C2, F));
    return res;
}

string GetConfigB2(START start, Point C2, Point NL2, Point F2)//InFlow
{
    string res = "";
    res += "\nCONFIG B1\n";
    res += "p4=" + to_string(C2.p) + "\n";
    res += "u4=" + to_string(C2.u) + "\n";
    res += "\n";
    res += "p3=" + to_string(NL2.p) + "\n";
    res += "u3=" + to_string(NL2.u) + "\n";
    res += "\n";
    res += "p'3=" + to_string(NL2.p) + "\n";
    res += "u'3=" + to_string(NL2.u) + "\n";
    res += "\n";
    res += "p5=" + to_string(F2.p) + "\n";
    res += "u5=" + to_string(F2.u) + "\n";
    res += "\n";
    res += "p1=" + to_string(start.p1) + "\n";
    res += "u1=" + to_string(start.u1) + "\n";
    res += "\n";
    res += "p2=" + to_string(start.p2) + "\n";
    res += "u2=" + to_string(start.u2) + "\n";
    res += "\n";
    res += "CHECK: " + to_string(Check_RES_Inflow_B(C2, F2));
    return res;
}