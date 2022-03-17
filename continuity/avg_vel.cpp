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
void avg_fluid_vel( vector<vector<long double> > & v,vector<vector<long double> > &avg_v,vector<int> pair_i,vector<int> pair_j,vector<long double> w_kernel,vector<int> i_type)
{
    extern const int dim;
    extern int niac,n_fluid_total;
    extern print printdata;

    int i,j,k,l;
    vector<long double> wtotal(n_fluid_total,0.0);

    for(i=0; i<n_fluid_total; i++)
    {
        for(l=0; l<dim; l++)
        {
            avg_v[l][i]=0;
        }
    }


    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];if(i_type[i]<0){continue;}
        if(i_type[j]==i_type[i])
        {
            for(l=0; l<dim; l++)
            {
                avg_v[l][i]=avg_v[l][i]+(v[l][j]*w_kernel[k]);
                avg_v[l][j]=avg_v[l][j]+(v[l][i]*w_kernel[k]);
            }
            wtotal[i]=wtotal[i]+w_kernel[k];
            wtotal[j]=wtotal[j]+w_kernel[k];
        }

    }

    for(i=0; i<n_fluid_total; i++)
    {
        for(l=0; l<dim; l++)
        {
            avg_v[l][i]=avg_v[l][i]/(wtotal[i]+c);

        }
    }
    //printdata.SaveData<long double,int > (avg_v,i_type, "check");

}
