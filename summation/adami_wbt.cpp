#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "print_data.h"
#include "const.h"
#define c 1.0e-10
using std::vector;
using std::cout;
using std::endl;
void adami_wbt_wcsph(vector<vector<long double> > x,vector<long double> &rho,vector<long double> &p,
vector<int> pair_i,vector<int> pair_j,vector<long double> w_kernel, vector<int> i_type)
{
    extern const int dim;
    extern int niac,ntotal,n_fluid_total;
    extern long double const gravity,rho0,pb,c_s,gamma1;
    extern print printdata;
    extern long double zeta;

    int i,j,k,l;
    long double term2dotacc,p0b,dx,p0b2;
    vector<long double> wtotal(ntotal,0.0);
    vector<long double> term1(ntotal,0.0);
    vector<long double> g_v(dim,0.0);
    vector<vector<long double> > gdotr(dim,vector<long double>(ntotal,0.0));


    if(body_f)
    {
        g_v[1]=-zeta*gravity;
    }

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        if(i_type[j]>10)
        {
            term1[j]=term1[j]+(p[i]*w_kernel[k]);
            wtotal[j]=wtotal[j]+w_kernel[k];
            for(l=0; l<dim; l++)
            {
                dx=x[l][j]-x[l][i];
                gdotr[l][j]=gdotr[l][j] + (rho[i]*dx*w_kernel[k]);
            }
        }
    }

    for(i=n_fluid_total; i<ntotal; i++)
    {
        term2dotacc=0.0;
        for(l=0; l<dim; l++)
        {
            term2dotacc=term2dotacc + (g_v[l]*gdotr[l][i]);
        }
        p[i]= (term1[i]+term2dotacc)/(wtotal[i]+c);
    }

 p0b=(rho0*c_s*c_s/gamma1);
    for(i=n_fluid_total; i<ntotal; i++)
    {
        rho[i]=rho0 * powl( ( ( (p[i]-pb)/p0b)+1.0 ),(1.0/gamma1) );
    }
   // printdata.SaveData<long double, long double, long double, long double,int > (x,v,p,rho,i_type, "check");
}
