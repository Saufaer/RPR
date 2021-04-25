
#include "Solver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <list>
void SetDefault(START *start)
{
    start->A2 = 10;
    start->A1 = 5;

    start->p2 = 303975;
    start->p1 = 353975;

    start->u2 = -150;
    start->u1 = -170;

    start->ro2 = 1.667;
    start->ro1 = 1.667;

    start->gamma2 = 1.4;
    start->gamma1 = 1.4;
}
int main(int argc, char **argv)
{

	/*remove("Points.txt");

	remove("L2_1.txt");
	remove("cl2_1.txt");
	remove("L1_1.txt");

	remove("L2_2.txt");
	remove("cl2_2.txt");
	remove("L1_2.txt");*/

	typedef std::numeric_limits< double > dbl;
	cout.precision(10);

	START start;

	if (argc == 1)
	{
		SetDefault(&start);
		system("RD /s/q  1");
		system("mkdir 1");
		Solve(start,1);
	}
	else if (argc == 11)
	{
		start.A2 = std::atof(argv[1]);
		start.A1 = std::atof(argv[2]);

		start.p2 = std::atof(argv[3]);
		start.p1 = std::atof(argv[4]);

		start.u2 = std::atof(argv[5]);
		start.u1 = std::atof(argv[6]);

		start.ro2 = std::atof(argv[7]);
		start.ro1 = std::atof(argv[8]);

		start.gamma2 = std::atof(argv[9]);
		start.gamma1 = std::atof(argv[10]);
		system("RD /s/q  1");
		system("mkdir 1");
		Solve(start,1);
	}
	else if (argc == 2)
	{
		string line;
		ifstream fin;
		fin.open(argv[1]);
		string var = "";
		int c = 1;
		while (getline(fin, line))
		{
            string res = "\n\nINPUT:";
            cout << res;
            

			list<double> vars;
			for (int i = 0; i < line.length(); i++)
			{
				if(line[i] != ' ' && line[i] != ';')
				var += line[i];
				if (line[i + 1] == ' ' || line[i + 1] == ';' || i + 1 == line.length())
				{
                    res += to_string(std::atof(var.c_str())) + line[i + 1];
                    
					cout << std::atof(var.c_str()) << line[i + 1];
					vars.push_back(std::atof(var.c_str()));
					var = "";
				}
			}
            res += "";
			auto iter = vars.begin();

			start.A2 = *iter++;
			start.A1 = *iter++;

			start.p2 = *iter++;
			start.p1 = *iter++;

			start.u2 = *iter++;
			start.u1 = *iter++;

			start.ro2 = *iter++;
			start.ro1 = *iter++;

			start.gamma2 = *iter++;
			start.gamma1 = *iter++;
			string comm = "RD /s/q " + to_string(c);
			system(comm.c_str());
			comm = "mkdir " + to_string(c);
			system(comm.c_str());
            Write(res, "Points.txt", c);
			Solve(start, c);
			c++;
		}
		fin.close();
		cout << endl;
	}


	return 0;
}

