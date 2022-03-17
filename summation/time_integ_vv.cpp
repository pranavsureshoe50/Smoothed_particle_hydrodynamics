#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
#include "print_data.h"
using std::cout;
using std::endl;
using std::vector;
void time_integration_vv(vector<vector<long double> >& x, vector<vector<long double> >& x_hts, vector<vector<long double> >& v,vector<vector<long double> >& v_hts,
                         vector<vector<long double> >& avg_v,vector<long double> & rho,vector<long double> & rho_hts,vector<long double> & p,vector<long double> &drhodt,
                         vector<vector<long double> >& f,vector<long double> &h_sl,vector<vector<int> > nc,  vector<int> &headlist, vector<int> &taillist,
                         vector<int>& pair_i,vector<int>& pair_j,vector<long double> & w_kernel, vector<vector<long double> >& dwdx,vector<int> i_type)
{

    extern const int dim,printevery;
    extern int n_fluid_total,print_count,iter;
    extern print printdata;
    extern long double dt, sim_time,wall_break_time;
    extern vector<long double> rhostar,c_i,dedt;
    extern vector< vector<long double> > xstar,vstar;

    int i, l;

    avg_fluid_vel(v,avg_v, pair_i, pair_j, w_kernel,i_type);
    p_f_wcsph(rho, p,f,i_type, pair_i, pair_j,dwdx);
    if(art_visc)
    {
        art_visc_wcsph(x,v,h_sl, rho, f,pair_i, pair_j,dwdx, i_type);
    }
    if(phy_visc)
    {
        visc_f2( x,v,avg_v,rho,f,pair_i,pair_j,dwdx,i_type);
    }
    if(surface_tension)
    {
        surf_tension(x,rho, f,i_type, pair_i,pair_j, dwdx) ;
    }
    if(body_f)
    {
        body_force(f);
    }

    for(i=0; i<n_fluid_total; i++)
    {
        for(l=0; l<dim; l++)
        {
            v_hts[l][i] = v[l][i]+(f[l][i]*dt*0.5);
            x_hts[l][i] = x[l][i]+(v[l][i]*dt*0.5);
        }
    }

    linked_list(x_hts, nc,headlist,taillist, pair_i, pair_j,h_sl, w_kernel, dwdx, i_type);
    sum_density ( rho_hts, w_kernel,  h_sl,  i_type, pair_i,pair_j);
    pressure(rho_hts,p);
    adami_wbt_wcsph(x_hts,rho_hts, p,pair_i,pair_j, w_kernel,  i_type);

////////////////////////////////////////////////////////////////////////////////////////////
///2nd step///
///////////////////////////////////////////////////////////////////////////////////////////
    avg_fluid_vel(v_hts,avg_v, pair_i, pair_j, w_kernel,i_type);
    p_f_wcsph(rho_hts, p,f,i_type, pair_i, pair_j,dwdx);
    if(art_visc)
    {
        art_visc_wcsph(x_hts,v_hts,h_sl, rho_hts, f,pair_i, pair_j,dwdx, i_type);
    }
    if(phy_visc)
    {
        visc_f2( x_hts,v_hts,avg_v,rho_hts,f,pair_i,pair_j,dwdx,i_type);
    }
    if(surface_tension)
    {
        surf_tension(x_hts,rho_hts, f,i_type, pair_i,pair_j, dwdx) ;
    }
    if(body_f)
    {
        body_force(f);
    }

    for(i=0; i<n_fluid_total; i++)
    {
        for(l=0; l<dim; l++)
        {
            vstar[l][i] = v[l][i]+(f[l][i]*dt*0.5);
            xstar[l][i] = x[l][i]+(vstar[l][i]*dt*0.5);
            v[l][i] = (2.0*vstar[l][i])-v[l][i];
            x[l][i] = (2.0*xstar[l][i])-x[l][i];

        }
    }
    linked_list(x, nc,headlist,taillist, pair_i, pair_j,h_sl, w_kernel, dwdx, i_type);
    sum_density ( rho, w_kernel,  h_sl,  i_type, pair_i,pair_j);
    if(use_mls)
    {
        if((iter % 20) == 0)
        {
            apply_mls_correction(x,rho,pair_i,pair_j,w_kernel,i_type) ;
        }
    }
    pressure(rho,p);
    adami_wbt_wcsph(x,rho, p,pair_i,pair_j, w_kernel,  i_type);

    if (energy_calculation)
    {
        int_energy_wcsph(x,v,avg_v,p,rho, dedt, pair_i,pair_j,dwdx, i_type);
    }
    if(iter % printevery == 0)
    {
        cout<<"Iteration "<< iter<<endl;
        print_count=print_count+1;
        printdata.SaveData<long double, long double, long double, long double,int > (x,v,p,rho,i_type, "v");
        column_height( x,v,w_kernel,h_sl,  i_type, pair_i, pair_j);
    }
}
