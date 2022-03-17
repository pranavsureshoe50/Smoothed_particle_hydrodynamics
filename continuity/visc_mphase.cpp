#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
void visc_f2(vector<vector<long double> > x, vector<vector<long double> > v, vector<vector<long double> > avg_v,
            vector<long double> rho, vector<vector<long double> >& f,vector<int> pair_i,vector<int> pair_j,
            vector<vector<long double> > dwdx,vector<int> i_type)
{
    extern int niac;
    extern const int dim,slip_condition;
    extern vector<long double> mass;
    extern const long double nu;
    extern long double h_sl_pilot;

    int i, j, k, l;
    long double  rr, dv[dim], dx, eta_square,vdotr,temp,temp1,temp2,drdw,vol_temp;

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        rr = 0;drdw =0.0;

        if(i_type[i]<0 || i_type[j]<0){continue;}
        if(i_type[j]==1 || i_type[j] == 8 )
        {
            for(l=0; l<dim; l++)
            {
                dv[l] = v[l][i]-v[l][j];
                dx = x[l][i]-x[l][j];
                drdw += (dx*dwdx[l][k]);
                rr += (dx*dx);
            }
        }
///Wall slip and no-slip application
        if(!slip)///No-slip
        {
            if(i_type[j]<1000 && i_type[j] > 100)
            {
                for(l=0; l<dim; l++)
                {
                    dv[l] = v[l][j]-v[l][i];
                    dx = x[l][j]-x[l][i];
                    drdw += (dx*dwdx[l][k]);
                    rr += (dx*dx);
                }
            }
            else if(i_type[j]>1000)
            {
                for(l=0; l<dim; l++)
                {
                    dv[l] = v[l][i]- ( (2.0*v[l][j]) - avg_v[l][i] );
                    dx = x[l][i]-x[l][j];
                    drdw += (dx*dwdx[l][k]);
                    rr += (dx*dx);
                }
            }
        }
        else ///For slip, wall impenetration condition is still applicable. This is applied below for the wall normal component.
        {
            if(i_type[j]>10)
            {
        for (l=0;l<dim;l++)
        {dv[l] = 0.0;}
            rr =((x[0][j]-x[0][i])*(x[0][j]-x[0][i])) +((x[1][j]-x[1][i])+(x[1][j]-x[1][i])) ;
            }
            if(i_type[j]==110 || i_type[j]==111)
            {
                    dv[0] = v[0][j]-v[0][i];
                    dx = x[0][j]-x[0][i];
                    drdw += (dx*dwdx[0][k]);

            }
            else if(i_type[j]==1110 || i_type[j]==1111)
            {
                    dv[0] = v[0][i]- ( (2.0*v[0][j]) - avg_v[0][i] );
                    dx = x[0][i]-x[0][j];
                    drdw += (dx*dwdx[0][k]);

            }
            else if (i_type[j]==220 || i_type[j]==221)
            {
                    dv[1] = v[1][j]-v[1][i];
                    dx = x[1][j]-x[1][i];
                    drdw += (dx*dwdx[1][k]);

            }
            else if (i_type[j]==2220 || i_type[j]==2221)
            {
                    dv[1] = v[1][i]- ( (2.0*v[1][j]) - avg_v[1][i] );
                    dx = x[1][i]-x[1][j];
                    drdw += (dx*dwdx[1][k]);
            }
        }

        eta_square= rr + powl(0.01*h_sl_pilot,2.0);
        vol_temp = ((mass[i]/rho[i])*(mass[i]/rho[i])) + ((mass[j]/rho[j])*(mass[j]/rho[j]));

        temp1 = (i_type[i] == 1 ) ? nu : nua;
        temp2 = (i_type[j] == 1 ) ? nu : nua;
        temp = (2*temp1*temp2) / (temp1 + temp2) ;

        for(l=0; l<dim; l++)
        {

            f[l][i] = f[l][i]+((1.0/mass[i])*temp*(vol_temp)*(drdw/eta_square)*dv[l]);
            if(i_type[j]==1 || i_type[j] == 8)
            {
                f[l][j] = f[l][j]+((1.0/mass[j])*temp*(vol_temp)*(-drdw/eta_square)*dv[l]);
            }
        }

    }

}

