#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
#define c 1e-10
using std::cout;
using std::endl;
using std::vector;
void visc_f(vector<vector<long double> > x, vector<vector<long double> > v, vector<vector<long double> > avg_v,
            vector<long double> rho, vector<vector<long double> >& f,vector<int> pair_i,vector<int> pair_j,
            vector<vector<long double> > dwdx,vector<int> i_type)

{
    extern int niac,n_fluid_total;
    extern const long double nu;
    extern const int dim, slip_condition;
    extern vector<long double> mass;

    int i, j, k, l;
    long double dwdote,r,temp,nuij;
    vector<vector<long double> > ftemp(dim,vector<long double>(n_fluid_total,0.0));
    vector<long double> dv(dim,0.0);
    vector<long double> dx(dim,0.0);

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        if(i_type[i]<0)
        {
            continue;
        }
        if(i_type[i] == 1 && i_type[j] == 8)
        {
            nuij = 2*nu*nua/(nu+nua) ;
        }
        else if (i_type[i] == 8 && i_type[j] == 1)
        {
            nuij = 2*nu*nua/(nu+nua) ;
        }
        else if (i_type[j] == 8 && i_type[i] == 8)
        {
            nuij = nua;
        }
        else
        {
            nuij = nu;
        }
        dwdote = 0.0;
        r = 0.0;
        for(l=0; l<dim; l++)
        {
            dx[l] = x[l][i]-x[l][j];
            r = r+(dx[l]*dx[l]);
        }
        r=sqrt(r);

        if(i_type[j]==1 || i_type[j] == 8)
        {
            for(l=0; l<dim; l++)
            {
                dv[l] = v[l][i]-v[l][j];
            }
        }
        else if(slip_condition==1)
        {
            if(i_type[j]<1000)
            {
                for(l=0; l<dim; l++)
                {
                    dv[l] = v[l][i]-v[l][j];
                }
            }
            if(i_type[j]>1000)
            {
                for(l=0; l<dim; l++)
                {

                    dv[l] = v[l][i]- ( (2.0*v[l][j]) - avg_v[l][i] );
                }
            }
        }


        for(l=0; l<dim; l++)
        {
            dwdote = dwdote +( dwdx[l][k]*(r)/(dx[l]+1e-10 ) ) ;
        }


        temp = (powl( (mass[j]/rho[j]) ,2.0 )+ powl( (mass[i]/rho[i]),2.0) )*nuij*dwdote/(r+1e-10);

        for(l=0; l<dim; l++)
        {
            ftemp[l][i] = ftemp[l][i]+(temp*dv[l]);
            if(i_type[j]==1 || i_type[j] == 8)
            {
                ftemp[l][j] = ftemp[l][j]-(temp*dv[l]);
            }
        }
    }

    for(i=0; i<n_fluid_total; i++)
    {
        for(l=0; l<dim; l++)
        {
            ftemp[l][i] = ftemp[l][i]/mass[i];
            f[l][i] = f[l][i]+ftemp[l][i];
        }
    }
}
