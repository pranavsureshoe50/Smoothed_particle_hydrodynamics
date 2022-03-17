#include <vector>
#include <iostream>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;

void c_wcsph(vector<long double> rho)
{
    extern const long double c_s,gamma1,rho0;
    extern int ntotal;
    extern vector<long double> c_i;
    extern vector<int> i_type;
    int i;
    long double p_c=(gamma1-1.0)*0.5 , p_c1=(gammaA-1.0)*0.5;

    for(i=0;i<ntotal;i++)
    {
        if(i_type[i]==8)
        {
            c_i[i]=c_s*powl((rho[i]/rhoA0),p_c1);
        }
        else
        {
            c_i[i]=c_s*powl((rho[i]/rho0),p_c);
        }

    }
}
