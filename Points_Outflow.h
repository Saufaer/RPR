#pragma once
#include "Curves.h"
#include "Start.h"
#include "Rule_6_7_8_9.h"
double M5Max(double alpha, double gamma2)
{
    double M5max = sqrt((1 + (1 - alpha)*gamma2) - sqrt(powf((1 + (1 - alpha)*gamma2), 2) - powf(alpha,2)));
    return M5max;
}
Point B(START start)
{
    double p = start.p2;
    double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
    while (true)
    {
        if (u > 0.001) { p += 0.1; }
        else { break; }
        u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
    }
    Point b{ p,0 };
    return b;
}

//Point D(START start)
//{
//	double p = start.p2;
//	double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
//	while (true)
//	{
//		if (u <= start.c2) { p -= 0.1; }
//		else { break; }
//		u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
//	}
//	Point d{ p,u };
//	return d;
//}

Point E(START start)
{
    Point e{ NULL };

    double M5max = M5Max(ALPHA1(start.A1, start.A2), start.gamma2);
    e = Point{ 0,0 };
        {

            double p = start.p2;
            double u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);

           
            if (u < M5max * start.c2)//go up from (p2,u2)
            {
                while (true) // go up from p2u2
                {
                    if (fabs(u - M5max * start.c2) <= 0.5) {
                        e = Point{ p,u }; 
                        break;
                    }
                    p -= 0.1;
                    if (p <= 0) { break; }
                    if (u <= 0) { break; }
                    u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
                }
            }
            else {
                //cout << "\n\n Search E down \n\n M5max * start.c2 = " << M5max * start.c2 << "\n\n u = " << u << "";
                p = start.p2;
                u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
                while (true) // go down from p2u2
                {
                    //cout << "\n\n u = " << u << "";
                    if (fabs(u - M5max * start.c2) <= 0.5) {
                        //cout << "\n\n u = " << u << "";
                        e = Point{ p,u };
                        break;
                    }
                    p += 0.1;
                    if (u <= 0) { break; }
                    if (p <= 0) { break; }
                    u = L2(p, start.u2, start.p2, start.ro2, start.gamma2, start.c2);
                }
            }
        }

    return e;
}

Point Es(START start)
{
    Point es{ NULL };
    double M2 = start.u2 / start.c2;
    double ps = start.p2*((1+ muiquadr(start.gamma2))*(pow(M2,2))- muiquadr(start.gamma2));
    double us = start.u2 - (1 - muiquadr(start.gamma2))*start.c2*(M2 - (1 / M2));
    es = Point{ ps,us };
    return es;
}

