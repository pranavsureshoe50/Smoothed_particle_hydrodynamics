#include <vector>
#include "header.h"
#include "const.h"
using std::vector;
void sum_density (vector<long double> & rho,vector<long double> w_kernel, vector<long double> h_sl, vector<int> i_type,
                   vector<int> pair_i,vector<int> pair_j)
{
    extern const int dim;
    extern int ntotal,n_fluid_total, niac;
    extern long double  wtemp;
    extern vector<long double> mass;

    int dim_1=dim;
    int i, j, k, l;
    long double dx[dim_1];

    for(l=0; l<dim; l++)
    {
        dx[l] = 0.0;
    }
    for(i=0; i<n_fluid_total; i++)
    {
        kernel(0.0,dx,h_sl[i]);
        rho[i] = mass[i]*wtemp;
    }
    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        rho[i] = rho[i]+(mass[i]*w_kernel[k]);
        rho[j] = rho[j]+(mass[j]*w_kernel[k]);


    }
}
