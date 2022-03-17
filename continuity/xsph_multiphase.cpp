#include <cmath>
#include <iostream>
#include <vector>
#include "const.h"
#include "header.h"
#include "print_data.h"
using std::vector;
using std::cout;
using std::endl;

void xsph_mphase( vector<long double> rho,vector<vector<long double> > v, vector<int> pair_i,vector<int> pair_j, vector<long double> w_kernel,vector<vector<long double> > &du,vector<int> i_type)
{
extern print printdata;
extern vector<long double> mass;
extern int n_fluid_total,niac;
int dim_1 = dim;
int i,j,k,l;
long double dv,dvdw,e = 0.5,ddvdw,dv1[dim_1],rhoij;

	for(k=0; k<niac; k++)
    {
        i=pair_i[k];
        j=pair_j[k];

        if(i_type[i]<0){continue;}

            if( (i_type[i]==1) && (i_type[j]==1) )
            {
                for(l=0; l<dim; l++)
                {
                    dv1[l] = v[l][i]-v[l][j];
                }
                rhoij = (rho[i]+rho[j])*0.5;
                for(l=0; l<dim; l++)
                {
                    du[l][i] +=  (e*0.5*mass[j]*(-dv1[l])*w_kernel[k]*(1.0/(rhoij)) );
                    du[l][j] +=  (e*0.5*mass[i]*(dv1[l])*w_kernel[k]*(1.0/(rhoij)));
                }
            }
            else if ((i_type[i]==8) && (i_type[j]==8))
            {
                for(l=0; l<dim; l++)
                {
                    dv1[l] = v[l][i]-v[l][j];
                }
                rhoij = (rho[i]+rho[j])*0.5;
                for(l=0; l<dim; l++)
                {
                    du[l][i] +=  (e*0.5*mass[j]*(-dv1[l])*w_kernel[k]*(1.0/(rhoij)) );
                    du[l][j] +=  (e*0.5*mass[i]*(dv1[l])*w_kernel[k]*(1.0/(rhoij) ));
                }
            }

//            else if (i_type[i]==1 && i_type[j]==8)
//            {
//               for(l=0; l<dim; l++)
//                {
//                    dv1[l] = v[l][i]-v[l][j];
//                }
//                for(l=0; l<dim; l++)
//                {
//                    du[l][i] +=  (e*0.5*mass[j]*(-dv1[l])*w_kernel[k]*(1.0/(rho[j])) );
//                    du[l][j] +=  (e*0.5*mass[i]*(dv1[l])*w_kernel[k]*(1.0/(rho[i]) ));
//                }
//            }
    }
}
