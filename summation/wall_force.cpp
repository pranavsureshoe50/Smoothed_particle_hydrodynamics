#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
void wall_force(vector<vector<long double> > x, vector<vector<long double> >& f, vector<int> i_type, vector<long double> h_sl,vector<int> pair_i, vector<int> pair_j)
{
    extern const int dim;
    extern const long double gravity,h;
    extern int niac;
    extern long double h_sl_pilot;

    int dim_1=dim;
    int i, j, k, l;
    long double r, rr, r_ratio;
    long double dx[dim_1];

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];if(i_type[i]<0){continue;}
        if( i_type[j]>10 )
        {
            if(i_type[j]<1000)
            {
                rr = 0.0;
                for(l=0; l<dim; l++)
                {
                    dx[l] = x[l][i]-x[l][j];
                    rr = rr+(dx[l]*dx[l]);
                }
                r = sqrt(rr);
                r_ratio=(h_sl_pilot*0.5/r);
                if(r_ratio>1.0)
                {
                    //cout<<"here"<<endl;
                    for(l=0; l<dim; l++)
                    {
                        if(i_type[i] == 1)
                        f[l][i] = f[l][i]+( gravity*h*( pow(r_ratio,4.0) - pow(r_ratio,2.0) ) * (dx[l]/rr) );
                        else
                        f[l][i] = f[l][i]+( (rhoA0/rho0)*(rhoA0/rho0)*gravity*h*( pow(r_ratio,4.0) - pow(r_ratio,2.0) ) * (dx[l]/rr) );
                    }
                }
            }
        }
    }
}
