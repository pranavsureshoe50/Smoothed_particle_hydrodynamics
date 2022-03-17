#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
void visc_f1(vector<vector<long double> > x, vector<vector<long double> > v, vector<vector<long double> > avg_v,
            vector<long double> rho, vector<vector<long double> >& f,vector<int> pair_i,vector<int> pair_j,
            vector<vector<long double> > dwdx,vector<int> i_type)
{
    extern int niac;
    extern const int dim,slip_condition;
    extern vector<long double> mass;
    extern const long double nu;
    extern long double h_sl_pilot;

    int i, j, k, l;
    long double  rr, dv, dx, eta_square,vdotr,temp,temp1,temp2;

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        rr = 0;
        vdotr=0.0;if(i_type[i]<0){continue;}
        if(i_type[j]==1 || i_type[j] == 8 )
        {
            for(l=0; l<dim; l++)
            {
                dv = v[l][j]-v[l][i];
                dx = x[l][j]-x[l][i];
                vdotr = vdotr +(dv*dx);
                rr = rr+(dx*dx);
            }
        }
        if(slip_condition==1)
        {
            if(i_type[j]<1000)
            {
                for(l=0; l<dim; l++)
                {
                    dv = v[l][j]-v[l][i];
                    dx = x[l][j]-x[l][i];
                    vdotr = vdotr +(dv*dx);
                    rr = rr+(dx*dx);
                }
            }
            if(i_type[j]>1000)
            {
                for(l=0; l<dim; l++)
                {
                    dv = v[l][i]- ( (2.0*v[l][j]) - avg_v[l][i] );
                    dx = x[l][i]-x[l][j];
                    vdotr = vdotr +(dv*dx);
                    rr = rr+(dx*dx);
                }
            }
        }

        eta_square=0.01*powl(h_sl_pilot*0.5,2.0);
        temp2 = (nu*8.0*vdotr)/(rr+eta_square);
        temp1 = (nua*8.0*vdotr)/(rr+eta_square);
        temp = (i_type[i] == 1) ? temp2 : temp1;
        for(l=0; l<dim; l++)
        {

            f[l][i] = f[l][i]+(mass[j]*temp*dwdx[l][k]/rho[j]);
            if(i_type[j]==1 || i_type[j] == 8)
            {
                temp = (i_type[j] == 1) ? temp2 : temp1;
                f[l][j] = f[l][j]+(mass[i]*temp*(-dwdx[l][k]/rho[i]));
            }
        }

    }

}

