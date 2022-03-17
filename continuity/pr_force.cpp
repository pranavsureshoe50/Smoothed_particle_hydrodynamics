#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
void p_f( vector<long double> rho, vector<long double> p, vector<vector<long double> >& f,
         vector<int> i_type, vector<int> pair_i, vector<int> pair_j,vector<vector<long double> > dwdx)
{
    extern const int dim;
    extern int niac,n_fluid_total;
    extern vector<long double> mass;

    int i, j, k, l;
    long double temp_p;

    for(i=0; i<n_fluid_total; i++)
    {
        for(l=0; l<dim; l++)
        {
            f[l][i] = 0.0;
        }
    }

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        if(i_type[i]==1)
        {
            temp_p = ( (p[i]/powl(rho[i],2.0)) + (p[j]/powl(rho[j],2.0)) );

            for(l=0; l<dim; l++)
            {
                f[l][i] = f[l][i]+(mass[j]*(-temp_p)*dwdx[l][k]);
                if(i_type[j]==1)
                {
                    f[l][j] = f[l][j]-(mass[i]*(-temp_p)*dwdx[l][k]);
                }
            }
        }
        else{break;}
    }
}
