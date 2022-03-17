#include <cmath>
#include <iostream>
#include <vector>
#include "const.h"
#include "header.h"
using std::vector;
using std::cout;
using std::endl;
void continuity_den( vector<long double> rho,vector<vector<long double> > v,vector<vector<long double> > avg_v,
                     vector<long double> &drhodt,vector<int> pair_i,vector<int> pair_j,vector<vector<long double> > dwdx,
                     vector<int> i_type)
{
    extern const int dim;
    extern vector<long double> mass;
    extern int n_fluid_total,niac;

    int i,j,k,l;
    long double dv,dvdw;

    for(k=0; k<n_fluid_total; k++)
    {
        drhodt[k]=0.0;
    }

    for(k=0; k<niac; k++)
    {
        i=pair_i[k];
        j=pair_j[k];
        dvdw=0.0;
        if(i_type[i]==1 || i_type[i] == 8)
        {
            if(!slip || i_type[j]==1 || i_type[j]==8)
            {
                if(i_type[j]<1000)
                {
                    for(l=0; l<dim; l++)
                    {
                        dv = v[l][i]-v[l][j];
                        dvdw = dvdw+(dv*dwdx[l][k]);
                    }
                }
                else
                {
                    for(l=0; l<dim; l++)
                    {
                        dv = v[l][i]- ( (2.0*v[l][j]) - avg_v[l][i] );
                        dvdw = dvdw+(dv*dwdx[l][k]);
                    }
                }
            }
            else ///For slip, wall impenetration condition is still applicable. This is applied below for the wall normal component.
            {
                if(i_type[j]==110 || i_type[j]==111)
                {
                        dv = v[0][i]-v[0][j];
                        dvdw = dvdw+(dv*dwdx[0][k]);
                }
                else if(i_type[j]==1110 || i_type[j]==1111)
                {
                        dv = v[0][i]- ( (2.0*v[0][j]) - avg_v[0][i] );
                        dvdw = dvdw+(dv*dwdx[0][k]);
                }
                else if (i_type[j]==220 || i_type[j]==221)
                {
                        dv = v[1][i]-v[1][j];
                        dvdw = dvdw+(dv*dwdx[1][k]);
                }
                else if (i_type[j]==2220 || i_type[j]==2221)
                {
                        dv = v[1][i]- ( (2.0*v[1][j]) - avg_v[1][i] );
                        dvdw = dvdw+(dv*dwdx[1][k]);
                }
            }
            drhodt[i]=drhodt[i]+(mass[j]*dvdw/rho[j]);
            if(i_type[j]==1 || i_type[j] == 8)
            {
                drhodt[j]=drhodt[j]+(mass[i]*dvdw/rho[i]);
            }


        }

    }

    for(k=0; k<n_fluid_total; k++)
    {
        drhodt[k]=drhodt[k]*rho[k];
    }
}
