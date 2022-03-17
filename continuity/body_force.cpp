#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
#include "print_data.h"
#define c 1.0e-10
using std::cout;
using std::endl;
using std::vector;
void body_force(vector<vector<long double> >& f)
{
    extern int n_fluid_total;
    extern long double sim_time,zeta;
    extern const int dim;
    extern const long double gravity,t_damp;

    int i;
    if((dim==2)||(dim==3))
    {
          if(sim_time<=t_damp)
        {
            zeta=0.5*( sinl ( -0.5+(sim_time/(t_damp+c))*M_PI)+1.0 );
            for(i=0; i<n_fluid_total; i++)
            {

                f[1][i] = f[1][i]-(zeta*gravity);
            }
        }
        else
        {
            zeta=0.99;
            for(i=0; i<n_fluid_total; i++)
            {
                f[1][i] = (f[1][i]-gravity);
            }
        }
    }
}

