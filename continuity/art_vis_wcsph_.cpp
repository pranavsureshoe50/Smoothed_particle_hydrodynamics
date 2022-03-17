#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
void art_visc_wcsph(vector<vector<long double> > x, vector<vector<long double> > v,vector<long double> h_sl,
                    vector<long double> rho, vector<vector<long double> >& f,vector<int> pair_i,
                    vector<int> pair_j,vector<vector<long double> > dwdx, vector<int> i_type)
{
    extern int niac;
    extern const int dim;
    extern vector<long double> mass,c_i;

    int i, j, k, l;
    long double hij, vdotr,cab, rr, dv, dx, temp,rhoij,eta_square,alpha_av_wcsph=0.05;

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        if(i_type[i]<0){continue;}
        if((i_type[i]==1) && (i_type[j]==1) )
        {
            vdotr = 0.0;
            rr = 0.0;
            for(l=0; l<dim; l++)
            {
                dv = v[l][i]-v[l][j];
                dx = x[l][i]-x[l][j];
                vdotr = vdotr +(dv*dx);
                rr = rr+(dx*dx);
            }
            if(vdotr < 0.0)
            {
                rhoij= (rho[i]+rho[j])*0.5;
                hij= (h_sl[i]+h_sl[j])*0.5;
                eta_square=0.01*powl(hij,2.0);
                cab=(c_i[i]+c_i[j])*0.5;
                temp = (-alpha_av_wcsph*hij*cab*vdotr)/(rhoij*(rr+eta_square));
                for(l=0; l<dim; l++)
                {
                    f[l][i] = f[l][i]+(-mass[j]*temp*dwdx[l][k]);
                    f[l][j] = f[l][j]+(-mass[i]*temp*(-dwdx[l][k]));
                }
            }

        }

        else if((i_type[i]==8) && (i_type[j]==8))
        {
            vdotr = 0.0;
            rr = 0.0;
            for(l=0; l<dim; l++)
            {
                dv = v[l][i]-v[l][j];
                dx = x[l][i]-x[l][j];
                vdotr = vdotr +(dv*dx);
                rr = rr+(dx*dx);
            }
            if(vdotr < 0.0)
            {
                rhoij= (rho[i]+rho[j])*0.5;
                hij= (h_sl[i]+h_sl[j])*0.5;
                eta_square=0.01*powl(hij,2.0);
                cab=(c_i[i]+c_i[j])*0.5;
                temp = (-alpha_av_wcsph*hij*cab*vdotr)/(rhoij*(rr+eta_square));
                for(l=0; l<dim; l++)
                {
                    f[l][i] = f[l][i]+(-mass[j]*temp*dwdx[l][k]);
                    f[l][j] = f[l][j]+(-mass[i]*temp*(-dwdx[l][k]));
                }
            }

        }

    }
}
