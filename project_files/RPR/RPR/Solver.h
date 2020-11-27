using namespace std;


#include "Solver_Outflow.h"
#include "Solver_Inflow.h"
#include <iostream>
#include "windows.h"
void Solve_Outflow(START  &start,int i)
{

	Point B(B(start));
	Write("\nB.p = " + to_string(B.p) + "\nB.u = " + to_string(B.u) + "\n","Points.txt",i);
	Point E(E(start));
	Write("\nE.p = " + to_string(E.p) + "\nE.u = " + to_string(E.u) + "\n", "Points.txt", i);
	Point El2 = Get_from_l2(E.p, E.u, E, B, start);
	Write("\nEl2.p = " + to_string(El2.p) + "\nEl2.u = " + to_string(El2.u) + "\n", "Points.txt", i);


	//Point D(D(start));
	if (Check_CONF_A(start, El2, B))
	{
		TwoPoints NN = Search_Conf_A(start, E, B, i);

		string res = "";

		res += "\nCONFIG A";
		res += "\n";
		res += "NL1_4.p4 =" + to_string(NN.NL1.p)   + "\n";
		res += "NL1_4.u4 =" + to_string(NN.NL1.u)   + "\n";
		res += "\n";					 
		res += "NL1_3.p3 =" + to_string(NN.NL1.p)   + "\n";
		res += "NL1_3.u3 =" + to_string(NN.NL1.u)   + "\n";
		res += "\n";					 
		res += "NL2.p5 =" + to_string(NN.NL2.p)   + "\n";
		res += "NL2.u5 =" + to_string(NN.NL2.u)   + "\n";
		res += "\n";
		res += "1.p1 =" + to_string(start.p1)   + "\n";
		res += "1.u1 =" + to_string(start.u1)   + "\n";
		res += "\n";
		res += "2.p2 =" + to_string(start.p2)  + "\n";
		res += "2.u2 =" + to_string(start.u2)   + "\n";
		res += "\n";
		res += "CHECK: " + to_string(Check_RES_Outflow(NN.NL2, NN.NL1));
		cout << res;
		
		Write(res, "Points.txt", i);
	}
	else
	{
		Point NL1 = Search_Conf_B(start, El2, B, i);

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
		cout << res;
		Write(res, "Points.txt", i);

		//cout << endl << "CONFIG B" << endl;
		//cout << "p4=" << El2.p << endl;
		//cout << "u4=" << El2.u << endl;
		//cout << endl;
		//cout << "p3=" << NL1.p << endl;
		//cout << "u3=" << NL1.u << endl;
		//cout << endl;
		//cout << "p'3=" << NL1.p << endl;
		//cout << "u'3=" << NL1.u << endl;
		//cout << endl;
		//cout << "p5=" << E.p << endl;
		//cout << "u5=" << E.u << endl;
		//cout << endl;
		//cout << "p1=" << start.p1 << endl;
		//cout << "u1=" << start.u1 << endl;
		//cout << endl;
		//cout << "p2=" << start.p2 << endl;
		//cout << "u2=" << start.u2 << endl;
		//cout << endl;
		//cout << "CHECK: " << Check_RES_Outflow(E, El2);
	}

}

void Solve_Inflow(START  &start, int i)
{
	Point C1(C1(start));
	Point C2(C2(start));

	Point H(Get_H_from_l1(C2.p, C2.u, C2, C1, start));

	if (Check_Inflow(start, C1))
	{
		if (Check_CONF_A1(start, H, C1))
		{
			TwoPoints NN = Search_Conf_A1(start, C2, C1);

			cout << endl << "CONFIG A1" << endl;
			cout << "p4=" << NN.NL2.p << endl;
			cout << "u4=" << NN.NL2.u << endl;
			cout << endl;
			cout << "p3=" << NN.NL1.p << endl;
			cout << "u3=" << NN.NL1.u << endl;
			cout << endl;
			cout << "p5=" << NN.NL1.p << endl;
			cout << "u5=" << NN.NL1.u << endl;
			cout << endl;
			cout << "p1=" << start.p1 << endl;
			cout << "u1=" << start.u1 << endl;
			cout << endl;
			cout << "p2=" << start.p2 << endl;
			cout << "u2=" << start.u2 << endl;
			cout << endl;
			cout << "CHECK: " << Check_RES_Inflow_A(NN.NL2, NN.NL1);
		}
		else
		{
			Point F(Get_F_from_l1(C2.p, C2.u, C2, C1, start));

			if (Check_CONF_B1(start, F, C1))
			{
				Point NL2 = Search_Conf_B1(start, F, C1);

				cout << endl << "CONFIG B1" << endl;
				cout << "p4=" << C2.p << endl;
				cout << "u4=" << C2.u << endl;
				cout << endl;
				cout << "p3=" << NL2.p << endl;
				cout << "u3=" << NL2.u << endl;
				cout << endl;
				cout << "p'3=" << NL2.p << endl;
				cout << "u'3=" << NL2.u << endl;
				cout << endl;
				cout << "p5=" << F.p << endl;
				cout << "u5=" << F.u << endl;
				cout << endl;
				cout << "p1=" << start.p1 << endl;
				cout << "u1=" << start.u1 << endl;
				cout << endl;
				cout << "p2=" << start.p2 << endl;
				cout << "u2=" << start.u2 << endl;
				cout << endl;
				cout << "CHECK: " << Check_RES_Inflow_B(C2, F);
			}
			else
			{
				Point F2(Get_F2_from_l1(F, C2, start));

				if (Check_CONF_B2(start, F2, C1))
				{
					Point NL2 = Search_Conf_B2(start, F2, C1);

					cout << endl << "CONFIG B2" << endl;
					cout << "p4=" << C2.p << endl;
					cout << "u4=" << C2.u << endl;
					cout << endl;
					cout << "p3=" << NL2.p << endl;
					cout << "u3=" << NL2.u << endl;
					cout << endl;
					cout << "p'3=" << NL2.p << endl;
					cout << "u'3=" << NL2.u << endl;
					cout << endl;
					cout << "p5=" << F2.p << endl;
					cout << "u5=" << F2.u << endl;
					cout << endl;
					cout << "p1=" << start.p1 << endl;
					cout << "u1=" << start.u1 << endl;
					cout << endl;
					cout << "p2=" << start.p2 << endl;
					cout << "u2=" << start.u2 << endl;
					cout << endl;
					cout << "CHECK: " << Check_RES_Inflow_B(C2, F2);
				}
			}
		}
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
		Solve_Outflow(start,i);
	}
	if (start.u2 < 0 && start.u1 < 0 && start.u1 / start.c1 > -1)
	{
		Solve_Inflow(start,i);
	}
}
