#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
void pressure(vector<long double> rho,vector<long double> &p)
{
    extern const long double gamma1,rho0,pb,c_s,c_sa,gammaA,rhoA0;
    extern int n_fluid_total;
    extern vector<int> i_type;
    int i;
    long double beta1,beta2,a = 2.0;
    beta1 = rho0*c_s*c_s/gamma1;
    beta2 = rhoA0*c_sa*c_sa/gammaA;
    for(i=0; i<n_fluid_total; i++)
    {
        if(i_type[i] == 1)
        {
            p[i] =pb + ( beta1*(powl( (rho[i]/rho0),gamma1 )-1.0) ) ;// only for water
        }

        //p[i]=pb+(c_s*c_s*(rho[i]-rho0));
        else if (i_type[i] == 8)
        {
            p[i] = pb + ( beta2*(powl( (rho[i]/rhoA0), gammaA )-1.0) ) ; // only for air
        }
    }
}




