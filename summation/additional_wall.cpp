#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::vector;
using std::cout;
using std::endl;
void moving_wall_particle(vector<vector<long double> > &x, vector<int> i_type)
{
    extern const int  dim,n_vir_layer; extern long double const l;
    extern long double dx,L,vir_lx,fac;
    extern int iter,ntotal,n_w_f,n_fluid_total;

    int i;
//////////////////////////////////////////////////
    if(dim==3)
    {


    }
    ///////////////////////////////////////////////////////////
    if(dim==2)
    {
        if(iter<3000)
        {

        for(i=n_fluid_total; i<n_w_f; i++)
        {
            if(i_type[i]==111)
            {
                x[0][i]=vir_lx+l;
            }
        }
        long double temp1=(L-(x[0][n_w_f-1])-(2*dx));
        for(i=n_w_f; i<ntotal; i++)
        {
            if ( (i_type[i]==1111) && (i!=3354) && (i!=3355) )
            {
                x[0][i]=x[0][i]-temp1;
            }
        }

    }
    else
    {
        for(i=n_fluid_total; i<n_w_f; i++)
        {
            if(i_type[i]==111)
            {
                x[0][i]=L-(2*dx);
            }
        }
        long double temp1;
        for(i=n_w_f; i<ntotal; i++)
        {
            if ( (i_type[i]==1111) && (i!=3354) && (i!=3355) )
            {
                temp1=x[0][i]-(vir_lx+l);
                x[0][i]=L+temp1-(2*dx);
            }
        }

    }
    }

    ////////////////////////////////////////////////////////////////////////
    if (dim==1)
    {

    }

}
