#include <iostream>
#include <vector>
#include "header.h"
#include "const.h"
#include "print_data.h"
using std::cout;
using std::endl;
using std::vector;
void apply_mls_correction(vector<vector<long double> > x,vector<long double> &rho,vector<int>& pair_i, vector<int>& pair_j,
                          vector<long double> & w_kernel,vector<int> &i_type)
{
    extern const int dim;
    extern long double dx,wtemp,h_sl_pilot;
    extern int niac,ntotal,n_fluid_total;
    extern print printdata;
    extern vector<long double> mass;
    int i,j,k,l,dim_1=dim,singular_m=0;
    long double dx1[dim_1],temp_aij,a[3][3],wself;

    vector<vector<long double> > aij(n_fluid_total,vector<long double>(6,0.0));
    vector<vector<long double> > b(3,vector<long double>(3,0.0));
    vector<vector<long double> >  beta(n_fluid_total,vector<long double>(3,0.0));
    vector<int> mat_check(n_fluid_total,0);


    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        for(l=0; l<dim; l++)
        {
            dx1[l]=x[l][i]-x[l][j];
        }
        temp_aij=(mass[j]*w_kernel[k]/rho[j]);
        aij[i][0]=aij[i][0]+temp_aij;
        aij[i][1]=aij[i][1]+(dx1[0]*temp_aij);
        aij[i][2]=aij[i][2]+(dx1[1]*temp_aij);
        aij[i][3]=aij[i][3]+(dx1[0]*dx1[0]*temp_aij);
        aij[i][4]=aij[i][4]+(dx1[0]*dx1[1]*temp_aij);
        aij[i][5]=aij[i][5]+(dx1[1]*dx1[1]*temp_aij);
        if(i_type[j]==1 || i_type[j] == 8)
        {
        temp_aij=(mass[i]*w_kernel[k]/rho[i]);
        aij[j][0]=aij[j][0]+(temp_aij);
        aij[j][1]=aij[j][1]+(-dx1[0]*temp_aij);
        aij[j][2]=aij[j][2]+(-dx1[1]*temp_aij);
        aij[j][3]=aij[j][3]+(dx1[0]*dx1[0]*temp_aij);
        aij[j][4]=aij[j][4]+(dx1[0]*dx1[1]*temp_aij);
        aij[j][5]=aij[j][5]+(dx1[1]*dx1[1]*temp_aij);
        }
    }

    for(l=0; l<dim_1; l++)
    {
        dx1[l]=0.0;
    }
    kernel(0.0,dx1,h_sl_pilot);
    wself=wtemp;

    for(i=0; i<n_fluid_total; i++)
    {

         aij[i][0]=aij[i][0]+( mass[i]*wself/rho[i] );
    }

    for(i=0; i<n_fluid_total; i++)
    {
        a[0][0]=aij[i][0];
        a[0][1]=aij[i][1];
        a[0][2]=aij[i][2];
        a[1][0]=aij[i][1];
        a[1][1]=aij[i][3];
        a[1][2]=aij[i][4];
        a[2][0]=aij[i][2];
        a[2][1]=aij[i][4];
        a[2][2]=aij[i][5];
        singular_m=0;
        mat3inv(a,b,singular_m);
        mat_check[i]=singular_m;
        for(l=0; l<3; l++)
        {
            beta[i][l]=b[l][0];
        }
    }

    for(i=0; i<n_fluid_total; i++)
    {
        if(mat_check[i]==0)
        {
            rho[i] = mass[i]*( beta[i][0] )*wself;
        }
        else
        {
            rho[i] = mass[i]*wself;
        }

    }

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        for(l=0; l<dim; l++)
        {
            dx1[l]=x[l][i]-x[l][j];
        }
        if(mat_check[i]==0)
        {
            rho[i] = rho[i] + (mass[i]*( beta[i][0] + (beta[i][1]*dx1[0]) + (beta[i][2]*dx1[1]) )*w_kernel[k] ) ;
        }
        else
        {
            rho[i] = rho[i] + (mass[i]*w_kernel[k] ) ;
        }
        if(i_type[j] == 1 || i_type[j] == 8)
        {
            if(mat_check[j]==0)
            {
                rho[j] = rho[j] + (mass[j]* ( beta[j][0] + (beta[j][1]*-dx1[0]) + (beta[j][2]*-dx1[1]) )*w_kernel[k] ) ;
            }
            else
            {
                rho[j] = rho[j] + (mass[j]*w_kernel[k] ) ;
            }
        }
    }
}


