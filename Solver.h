using namespace std;


#include "Solver_Outflow.h"
#include "Solver_Inflow.h"
#include <iostream>



void Solve_Outflow(START  &start)
{

	Point B(B(start));
	Point D(D(start));
	Point E(E(start));
	Point El2 = Get_from_l2(E.p, E.u, E, B, start);

	if (Check_CONF_A(start, El2, B))
	{
		TwoPoints NN = Search_Conf_A(start, E, B);

		cout << endl << "CONFIG A" << endl;
		cout << "p4=" << NN.NL1.p << endl;
		cout << "u4=" << NN.NL1.u << endl;
		cout << endl;
		cout << "p3=" << NN.NL1.p << endl;
		cout << "u3=" << NN.NL1.u << endl;
		cout << endl;
		cout << "p5=" << NN.NL2.p << endl;
		cout << "u5=" << NN.NL2.u << endl;
		cout << endl;
		cout << "p1=" << start.p1 << endl;
		cout << "u1=" << start.u1 << endl;
		cout << endl;
		cout << "p2=" << start.p2 << endl;
		cout << "u2=" << start.u2 << endl;
		cout << endl;
		cout << "CHECK: " << Check_RES_Outflow(NN.NL2, NN.NL1);
	}
	else
	{
		Point NL1 = Search_Conf_B(start, El2, B);

		cout << endl << "CONFIG B" << endl;
		cout << "p4=" << El2.p << endl;
		cout << "u4=" << El2.u << endl;
		cout << endl;
		cout << "p3=" << NL1.p << endl;
		cout << "u3=" << NL1.u << endl;
		cout << endl;
		cout << "p'3=" << NL1.p << endl;
		cout << "u'3=" << NL1.u << endl;
		cout << endl;
		cout << "p5=" << E.p << endl;
		cout << "u5=" << E.u << endl;
		cout << endl;
		cout << "p1=" << start.p1 << endl;
		cout << "u1=" << start.u1 << endl;
		cout << endl;
		cout << "p2=" << start.p2 << endl;
		cout << "u2=" << start.u2 << endl;
		cout << endl;
		cout << "CHECK: " << Check_RES_Outflow(E, El2);
	}

}

void Solve_Inflow(START  &start)
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

void Solve(START &start)
{
	if (start.u2 > 0 && start.u1 > 0)
	{
		Solve_Outflow(start);
	}
	if (start.u2 < 0 && start.u1 < 0)
	{
		Solve_Inflow(start);
	}
}
