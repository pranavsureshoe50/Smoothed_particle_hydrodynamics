#include <vector>
#include <iostream>
#include <cmath>
#include "header.h"
#include "const.h"
using std::vector;
using std::cout;
using std::endl;
void create_virtual_particle(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,
                             vector<long double> &h_sl,vector<long double> & rho,vector<long double> & rho_hts,
                             vector<long double> &p,vector<long double> & vx,vector<long double> & vy,
                             vector<long double> & vz, vector<int>& i_type)
{
    extern const int dim;
    extern const long double rho0,pb;
    extern long double dx, dy, dz,h_sl_pilot;
    extern int n_fixed_vir_total,nx_vir, ny_vir, nz_vir;

    int nx_v=nx_vir;int ny_v=ny_vir;int nz_v=nz_vir;
    int i, j, k;
    int temp = 0;
    n_fixed_vir_total=0;
    long double pi=pb,rhoi=rho0;
   //////////////////////////////////////////////////////////
    if(dim==3)
    {
        temp = 0;
        for(k=0; k<nz_v; k++)
        {
            for(j=0; j<ny_v; j++)
            {
                for(i=0; i<nx_v; i++)
                {
                    if( (k<n_vir_layer)||(k>=(nz_v-n_vir_layer)) )///front and back layers
                    {
                        x_pos.push_back(i*dx);
                        y_pos.push_back(j*dy);
                        z_pos.push_back(k*dz);
                        if(k<n_vir_layer){i_type.push_back(3330);}/// back layer
                        if(k>=(nz_v-n_vir_layer)){i_type.push_back(3331);}/// front layer
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        vz.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;
                    }
                    else if( (j<n_vir_layer))//||(j>=(ny_v-n_vir_layer)) )/// bottom and top layers
                    {
                        x_pos.push_back(i*dx);
                        y_pos.push_back(j*dy);
                        z_pos.push_back(k*dz);
                        if(j<n_vir_layer){i_type.push_back(2220);}/// bottom layer
                        if(j>=(ny_v-n_vir_layer)){i_type.push_back(2221);}/// top layer
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        vz.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;
                    }
                    else if( (i<n_vir_layer)||(i>=(nx_v-n_vir_layer)) )/// left and right wall
                    {
                        x_pos.push_back(i*dx);
                        y_pos.push_back(j*dy);
                        z_pos.push_back(k*dz);
                        if(i<n_vir_layer){i_type.push_back(1110);}
                        if(i>=(nx_v-n_vir_layer)){i_type.push_back(1111);}
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        vz.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;
                    }
                }
            }
        }
    }
    /////////////////////////////////////////////////////////
    if(dim==2)
    {
        temp = 0;
        for(j=0; j<ny_v; j++)
        {
            for( i=0; i<nx_v; i++)
            {
                if((j<n_vir_layer)||(j>=(ny_v-n_vir_layer)))
                {
                    x_pos.push_back(i*dx);
                    y_pos.push_back(j*dy);
                    if(j<n_vir_layer){i_type.push_back(2220);}/// bottom layer
                    if(j>=(ny_v-n_vir_layer)){i_type.push_back(2221);}/// top layer
                    h_sl.push_back(h_sl_pilot);
                    h_sl.push_back(h_sl_pilot);
                    rho.push_back(rhoi);
                    rho_hts.push_back(rhoi);
                    if(j>=n_vir_layer){vx.push_back(0);}else{
                    vx.push_back(0);}
                    vy.push_back(0);
                    p.push_back(pi);
                    temp = temp+1;
                }
                else if((i<n_vir_layer)||(i>=(nx_v-n_vir_layer)) )
                {
                    if((j<=(ny_v-n_vir_layer)) )
                    {
                        x_pos.push_back(i*dx);
                        y_pos.push_back(j*dy);
                        if(i<n_vir_layer){i_type.push_back(1110);}/// left wall
                        if(i>=(nx_v-n_vir_layer)){i_type.push_back(1111);}/// right wall
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;
                    }
                }
            }
        }
    }
    /////////////////////////////////////////////////////////
    if(dim==1)
    {
        temp = 0;
        for( i=0; i<nx_v; i++)
        {
            if( (i<n_vir_layer)||(i>=(nx_v-n_vir_layer)) )
            {
                x_pos.push_back(i*dx);
                i_type.push_back(-1);
                h_sl.push_back(h_sl_pilot);
                rho.push_back(rhoi);
                rho_hts.push_back(rhoi);
                vx.push_back(0);
                p.push_back(pi);
                temp = temp+1;
            }
        }
    }
    n_fixed_vir_total = temp;
}

