#include <cmath>
#include <iostream>
#include <vector>
#include "const.h"
#include "header.h"
using std::vector;
using std::cout;
using std::endl;
void continuity_den_rf(vector<long double> rho,vector<long double> p,vector<vector<long double> > x,vector<vector<long double> > v,vector<vector<long double> > avg_v,
                       vector<long double> &drhodt,vector<int> pair_i,vector<int> pair_j,vector<vector<long double> > dwdx,
                       vector<int> i_type)
{
    extern const int dim;
    extern vector<long double> mass,c_i;
    extern int n_fluid_total,niac;
    extern long double const c_s,rho0;
    int i,j,k,l,dim_1=dim;
    long double cij,dv[dim_1],dx[dim_1],rij,dvdw,dxdw,delrhoi,delrhoj,delrhoij=0.0;


    for(k=0; k<n_fluid_total; k++)
    {
        drhodt[k]=0.0;
    }

    for(k=0; k<niac; k++)
    {
        i=pair_i[k];
        j=pair_j[k];
        dvdw=0.0;
        rij=0.0;
        dxdw=0.0;
        if(i_type[i]==1)
        {
            if(i_type[j]<1000){
            for(l=0; l<dim; l++)
            {

                dv[l] = v[l][i]-v[l][j];
            }}
            else{
            for(l=0; l<dim; l++)
            {

                dv[l] = v[l][i]- ( (2.0*v[l][j]) - avg_v[l][i] );
            }}
            for(l=0; l<dim; l++){
                dvdw = dvdw+(dv[l]*dwdx[l][k]);
                dx[l]=x[l][j]-x[l][i];
                rij=rij+(dx[l]*dx[l]);
            }
            rij=sqrtl(rij);

            for(l=0; l<dim; l++)
            {
                dxdw=dxdw + (dx[l]*dwdx[l][k]/rij);
            }

            cij=fmax( c_i[i],c_i[j] );
            //delrhoi=powl( (powl(rho[i],6.0) + (powl(rho0,6.0)*6.0*9.81*(x[1][j]-x[1][i])/(c_s*c_s)) ), (1.0/6.0) )-rho[i];
            //delrhoj=powl( (powl(rho[j],6.0) + (powl(rho0,6.0)*6.0*9.81*(x[1][i]-x[1][j])/(c_s*c_s)) ), (1.0/6.0) )-rho[j];
            //delrhoij= (delrhoi+delrhoj)*0.5;
            drhodt[i]=drhodt[i]+(mass[j]*dvdw/rho[j])+ ( cij*(rho[j]-rho[i])*mass[j]*dxdw/(rho[i]*rho[j]) );
            if(i_type[j]==1)
            {
               drhodt[j]=drhodt[j]+(mass[i]*dvdw/rho[i])+( cij*(rho[i]-rho[j])*mass[i]*dxdw/(rho[i]*rho[j]) );
            }

        }
        else
        {
            break;
        }
    }

    for(k=0; k<n_fluid_total; k++)
    {
        drhodt[k]=drhodt[k]*rho[k];
    }
}

