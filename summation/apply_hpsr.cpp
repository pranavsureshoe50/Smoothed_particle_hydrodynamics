#include <vector>
#include <cmath>
#include "const.h"
#include "header.h"
using std::vector;
void apply_hspr(vector<vector<long double> > x ,vector<long double> &p,vector<long double> &rho)/// apply hydrostatic pressure to the particles
{
    int i;
    extern int n_fluid_total;
    extern const long double vir_ly,c_s ,dx,dy,c_sa;
    extern const long double rho0,gravity,pb;
    extern vector<long double> mass;
    extern vector<int> i_type;
    long double temp,p0 = pb;

    for (i=0; i<n_fluid_total; i++)
    {

           p[i]=p0+ (rho0*gravity*std::abs( (x[1][n_fluid_total-1]-x[1][i]) ));

           if(i_type[i] == 8)
           {
               p[i] += (2*sig/Rb) ;
           }
    }
    for (i=0; i<n_fluid_total; i++)
    {
            if(i_type[i] == 1)
            {
                temp=(1.0+ ( gamma1*(p[i]-p0)/(rho0*c_s*c_s) ) );
                rho[i]=rho0*powl(temp,(1.0/gamma1)); //rho = rho0*(temp)^1/gamma
            }
            else if(i_type[i] == 8)
            {
                temp=(1.0+ ( gammaA*(p[i]-p0)/(rhoA0*c_sa*c_sa) ) );
                rho[i]=rhoA0*powl(temp,(1.0/gammaA)); //rho = rho0*(temp)^1/gamma
            }

            mass[i] = rho[i]*dx*dy ;
    }

}
