#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
void p_f_wcsph(vector<long double> rho, vector<long double> p, vector<vector<long double> >& f,
               vector<int> i_type, vector<int> pair_i, vector<int> pair_j,vector<vector<long double> > dwdx)
{
    extern const int dim;
    extern int niac,n_fluid_total;
    extern vector<long double> mass;

    int i, j, k, l;
    long double temp_p,dx,temp2,e1 = 0.07,e2 = 0.001,e3 = 0.0001,e4 = 0.15,e5 = 0.0001;

    for(i=0; i<n_fluid_total; i++)
    {
        for(l=0; l<dim; l++)
        {
            f[l][i] = 0.0;
        }
    }

    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
            if(i_type[i]<0){continue;}

            temp_p = (p[i]*powl( (mass[i]/rho[i]),2.0))  + (p[j]*(powl( (mass[j]/rho[j]) ,2.0 )));

            for(l=0; l<dim; l++)
            {
                f[l][i] = f[l][i]+(temp_p*dwdx[l][k]);
                if(i_type[j] ==1 || i_type[j] == 8)
                {
                    f[l][j] = f[l][j]+(temp_p*(-dwdx[l][k]));
                }
            }

    }
    for(k=0; k<n_fluid_total; k++)
    {
        for(l=0; l<dim; l++)
        {
            f[l][k] = (-1.0/mass[k])*f[l][k];
        }
    }

    ///Multiphase Repulsion///
    for(k=0; k<niac; k++)
    {
        i = pair_i[k];
        j = pair_j[k];
        if(i_type[i]<0)
        {
            continue;
        }

        if(((i_type[i] ==1 ) && (i_type[j] == 8)) || ((i_type[i] ==8 ) && (i_type[j] == 1)))
        {
            temp2 = (abs(p[i])*(mass[i]/rho[i])*(mass[i]/rho[i])) + (abs(p[j])*(mass[j]/rho[j])*(mass[j]/rho[j])) ;
            for(l=0; l<dim; l++)
            {
                f[l][i] += -(e1/mass[i])*temp2*dwdx[l][k] ;
                f[l][j] += (e1/mass[j])*temp2*dwdx[l][k] ;
            }
        }
    }
//
/////Multiphase Repulsion///
//    for(k=0; k<niac; k++)
//    {
//        i = pair_i[k];
//        j = pair_j[k];
//        if(i_type[i]<0)
//        {
//            continue;
//        }
//
//        if(i_type[i] ==1 && i_type[j] == 8)
//        {
//            temp2 = (abs(p[i])*(mass[i]/rho[i])*(mass[i]/rho[i])) + (abs(p[j])*(mass[j]/rho[j])*(mass[j]/rho[j])) ;
//            temp2 = temp2 / (rho[i]+rho[j]) ;
//            for(l=0; l<dim; l++)
//            {
//                f[l][i] += -(0.08*(rho0 - rhoA0)/(rho0 + rhoA0))*temp2*dwdx[l][k] ;
//                f[l][j] += -(0.08*(rho0 - rhoA0)/(rho0 + rhoA0))*temp2*-dwdx[l][k] ;
//            }
//        }
//    }
////
//    ///Multiphase Repulsion///colograssi
//    for(k=0; k<niac; k++)
//    {
//        i = pair_i[k];
//        j = pair_j[k];
//        if(i_type[i]<0)
//        {
//            continue;
//        }
//
//        if((i_type[i] == 8 ) && (i_type[j] == 8))
//        {
//            temp_p = (rho[i]*rho[i]) + (rho[j]*rho[j]) ;
//            for(l=0; l<dim; l++)
//            {
//
//                f[l][i] += (e2/rho[i])*(temp_p)*(mass[j]/rho[j])*dwdx[l][k] ;
//                f[l][j] += (e2/rho[j])*(temp_p)*(mass[i]/rho[i])*-dwdx[l][k] ;
//
//            }
//
//        }
//    }

//    for(k=0; k<niac; k++)
//    {
//        i = pair_i[k];
//        j = pair_j[k];
//        if(i_type[i]<0)
//        {
//            continue;
//        }
//
//        if((i_type[i] == 1 ) && (i_type[j] == 8))
//        {
//            temp_p = e3*((rho0 - rhoA0)/(rho0 + rhoA0))*abs((p[i]+p[j])/(rho[i]*rho[j])) ;
//            for(l=0; l<dim; l++)
//            {
//
//                f[l][i] += (temp_p*mass[j]*dwdx[l][k]) ;
//                f[l][j] += (2*temp_p*mass[i]*-dwdx[l][k]) ;
//
//            }
//
//        }
//    }

//
//  for(k=0; k<niac; k++)
//    {
//        i = pair_i[k];
//        j = pair_j[k];
//        if(i_type[i]<0)
//        {
//            continue;
//        }
//        if(((i_type[i] ==1 ) && (i_type[j] == 8)) || ((i_type[i] ==8 ) && (i_type[j] == 1)))
//        {
//            dx = 0.0;
//            for(l=0;l<dim;l++)
//            {
//                dx += (x[l][i] - x[l][j])*(x[l][i] - x[l][j]) ;
//            }

//            if(dx > (h_sl_pilot*0.5) )
//            {
//                continue ;
//            }
//        }
//
//        if(((i_type[i] ==1 ) && (i_type[j] == 8)) || ((i_type[i] ==8 ) && (i_type[j] == 1)))
//        {
//            temp_p = ((mass[i]/rho[i])*(mass[i]/rho[i])) + ((mass[j]/rho[j])*(mass[j]/rho[j]) ) ;
//            for(l=0; l<dim; l++)
//            {
//                f[l][i] += e4*temp_p*(-dwdx[l][k] / mass[i] );
//                f[l][j] += e4*temp_p*(dwdx[l][k] / mass[j] );
//            }
//        }
//    }


//    for(k=0; k<niac; k++)
//    {
//        i = pair_i[k];
//        j = pair_j[k];
//        if(i_type[i]<0)
//        {
//            continue;
//        }
//        if(((i_type[i] ==1 ) && (i_type[j] == 8)) || ((i_type[i] ==8 ) && (i_type[j] == 1)))
//        {
//            dx = 0.0;
//            for(l=0;l<dim;l++)
//            {
//                dx += (x[l][i] - x[l][j])*(x[l][i] - x[l][j]) ;
//            }
//            if(dx > (h_sl_pilot*0.5) )
//            {
//                continue ;
//            }
//            temp_p = ((mass[i]/rho[i])*(mass[i]/rho[i])) + ((mass[j]/rho[j])*(mass[j]/rho[j]) ) ;
//            for(l=0; l<dim; l++)
//            {
//
//                f[l][i] += pow(e4,(dx*2/h_sl_pilot))*temp_p*(-dwdx[l][k] / mass[i] );
//                f[l][j] += pow(e4,(dx*2/h_sl_pilot))*temp_p*(dwdx[l][k] / mass[j] );
//
//            }
//
//        }
//    }

//    for(k=0; k<niac; k++)
//    {
//        i = pair_i[k];
//        j = pair_j[k];
//        if(i_type[i]<0)
//        {
//            continue;
//        }
//
//        if((i_type[i] == 1 ) && (i_type[j] == 8))
//        {
//            temp_p = -e5*((rho[i]*rho[i]) + (rho[j]*rho[j]) ) ;
//            for(l=0; l<dim; l++)
//            {
//                f[l][i] += 0.5*temp_p*(dwdx[l][k] * (mass[j]/rho[j])  );
//                f[l][j] += temp_p*(-dwdx[l][k] * (mass[i]/rho[i])  );
//            }
//
//        }
//    }
}
