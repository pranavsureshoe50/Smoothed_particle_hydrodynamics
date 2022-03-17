#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
#include <omp.h>
#define c 1.0e-10
using std::cout;
using std::endl;
using std::vector;
void surf_tension( vector<vector<long double> > x,vector<long double> rho,  vector<vector<long double> >& f,
                   vector<int> i_type, vector<int> pair_i, vector<int> pair_j,vector<vector<long double> > dwdx)
{
    extern const int dim;
    extern int niac,ntotal,n_air_total,n_fluid_total;


    extern vector<long double> mass;
    vector<vector<long double> > gradc(dim, vector<long double>(ntotal,0.0));
    int i, j, k, l,dim_1 = dim;
    long double Kr;
    vector <long double> gnormal(ntotal,0.0),delg(ntotal,0.0);
     //Surface Tension coefficient: Water-air interface at 25 C temperature
    long double temp_c, rr = 0.0, phi;


    for(k = 0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        if((i_type[i]<0 ) || (i_type[j] > 10))
        {
            continue;
        }
        //rr = 0;
        if ( i_type[j] != i_type[i] )
        {
            temp_c = ( ((mass[i]/rho[i])*(mass[i]/rho[i])) + ((mass[j]/rho[j])*(mass[j]/rho[j])) );
            for(l=0; l<dim; l++)
            {
                gradc[l][i] = gradc[l][i]+((rho[i]/(rho[i]+rho[j]))*(rho[i]/mass[i])*(temp_c)*dwdx[l][k]);

                gradc[l][j] = gradc[l][j]+((rho[j]/(rho[i]+rho[j]))*(rho[j]/mass[j])*(temp_c)*-dwdx[l][k]);
            }
        }
    }

    long double rr1=0.0,ni[dim_1],nj[dim_1] , nW = 0.0 , rW = 0.0;
    for(k = 0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        rr1 = 0.0;
        rr=0.0;
        nW = 0.0;
        rW = 0.0;

        if(i_type[i] != i_type[j])
        {
            phi = -1.0 ;
        }
        else
        {
            phi = 1.0 ;
        }

        if(i_type[i] < 0) {continue;}

        if ((i_type[j] > 0) && (i_type[j] < 10) )
        {
            for(l=0; l<dim_1; l++)
            {
                rr += (gradc[l][i]*gradc[l][i]);
                rr1 += (gradc[l][j]*gradc[l][j]);
            }

            for(l=0; l<dim; l++)
            {
                ni[l] = gradc[l][i] / (c+sqrt(rr));
                nj[l] = gradc[l][j] / (c+sqrt(rr1));
                nW += (ni[l]- (phi*nj[l]))*dwdx[l][k] ;
                rW += abs((x[l][i]-x[l][j])*dwdx[l][k] ) ;
            }

            if(i_type[i] != i_type[j])
            {
                gnormal[i] += nW*(mass[j]/rho[j]);
                gnormal[j] += -nW*(mass[i]/rho[i]);
            }
            else
            {
                gnormal[i] += nW*(mass[j]/rho[j]);
                gnormal[j] += nW*(mass[i]/rho[i]);
            }

            delg[i] += rW*(mass[j]/rho[j]);
            delg[j] += rW*(mass[i]/rho[i]);
        }
    }
    for(i = 0; i<n_fluid_total; i++)
    {
        gnormal[i] = dim_1*(gnormal[i]/(delg[i]+c));
        for(l=0; l<dim; l++)
        {
            f[l][i] += ((sig*gradc[l][i]*gnormal[i])*(1/rho[i]));
        }
    }

}
