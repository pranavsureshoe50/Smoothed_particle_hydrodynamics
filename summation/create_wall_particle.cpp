#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::vector;
using std::cout;
using std::endl;
void create_wall_particle(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,
                          vector<long double> &h_sl,vector<long double> & rho,vector<long double> & rho_hts,
                          vector<long double> &p,vector<long double> & vx,vector<long double> & vy,vector<long double> & vz,
                          vector<int>& i_type)
{
    extern const int  dim;
    extern const long double rho0,pb;
    extern long double dx, dy, dz, h_sl_pilot,vir_lx,vir_ly,vir_lz;
    extern int n_wall_total,nx_wall, ny_wall, nz_wall;

    int i, j, k;
    int temp = 0;
    n_wall_total=0;
    long double pi=pb,rhoi=rho0;

    if(dim==3)
    {
        temp = 0;
        for(k=0; k<nz_wall; k++)
        {
            for(j=0; j<ny_wall; j++)
            {
                for(i=0; i<nx_wall; i++)
                {
                    if(k==0)///back wall
                    {
                        x_pos.push_back((i*dx)+(vir_lx));
                        y_pos.push_back((j*dy)+(vir_ly));
                        z_pos.push_back(vir_lz);
                        i_type.push_back(330);/// back wall
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        vz.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;
                    }
                    else if(k==(nz_wall-1))///front wall
                    {
                        x_pos.push_back((i*dx)+(vir_lx));
                        y_pos.push_back((j*dy)+(vir_ly));
                        z_pos.push_back(vir_lz+(k*dz));
                        i_type.push_back(331);/// front wall
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        vz.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;
                    }
                    else if(j==0)///bottom wall
                    {
                        x_pos.push_back((i*dx)+(vir_lx));
                        y_pos.push_back(vir_ly);
                        z_pos.push_back((k*dz)+(vir_lz));
                        i_type.push_back(220);///bottom wall
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        vz.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;
                    }
                    else if(j==(ny_wall-1))///top wall
                    {
                       /* x_pos.push_back((i*dx)+(vir_lx));
                        y_pos.push_back((j*dy)+vir_ly);
                        z_pos.push_back((k*dz)+(vir_lz));
                        i_type.push_back(221);///top wall
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        vz.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;*/
                    }
                    else if(i==0)/// left wall
                    {
                            x_pos.push_back(vir_lx);
                            y_pos.push_back((j*dy)+(vir_ly));
                            z_pos.push_back((k*dz)+(vir_lz));
                            i_type.push_back(110);/// left wall
                            h_sl.push_back(h_sl_pilot);
                            rho.push_back(rhoi);
                            rho_hts.push_back(rhoi);
                            vx.push_back(0);
                            vy.push_back(0);
                            vz.push_back(0);
                            p.push_back(pi);
                            temp = temp+1;
                    }
                    else if(i==(nx_wall-1))///right wall
                    {
                         x_pos.push_back((i*dx)+vir_lx);
                            y_pos.push_back((j*dy)+(vir_ly));
                            z_pos.push_back((k*dz)+(vir_lz));
                            i_type.push_back(111);///right wall
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
    ///////////////////////////////////////////////////////////
    if(dim==2)
    {
        temp = 0;
        for(j=0; j<ny_wall; j++)
        {
            for(i=0; i<nx_wall; i++)
            {
                if(j==0)/// bottom wall
                {
                    x_pos.push_back((i*dx)+(vir_lx));
                    y_pos.push_back(vir_ly);
                    i_type.push_back(220);
                    h_sl.push_back(h_sl_pilot);
                    rho.push_back(rhoi);
                    rho_hts.push_back(rhoi);
                    vx.push_back(0);
                    vy.push_back(0);
                    p.push_back(pi);
                    temp = temp+1;
                }
                else if(j==(ny_wall-1))///top wall
                {
                    x_pos.push_back((i*dx)+(vir_lx));
                    y_pos.push_back((j*dy)+(vir_ly));
                    i_type.push_back(221);
                    h_sl.push_back(h_sl_pilot);
                    rho.push_back(rhoi);
                    rho_hts.push_back(rhoi);
                    vx.push_back(0);
                    vy.push_back(0);
                    p.push_back(pi);
                    temp = temp+1;
                }
                else if(i==0)///left wall
                {

                        x_pos.push_back(vir_lx);
                        y_pos.push_back((j*dy)+(vir_ly));
                        i_type.push_back(110);///left wall
                        h_sl.push_back(h_sl_pilot);
                        rho.push_back(rhoi);
                        rho_hts.push_back(rhoi);
                        vx.push_back(0);
                        vy.push_back(0);
                        p.push_back(pi);
                        temp = temp+1;

                }
                else if(i==(nx_wall-1))///right wall
                {

                        x_pos.push_back(vir_lx+(i*dx));
                        y_pos.push_back((j*dy)+(vir_ly));
                        i_type.push_back(111);///right wall
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

    ////////////////////////////////////////////////////////////////////////
    if (dim==1)
    {
        temp = 0;
        for(i=0; i<nx_wall; i++)
        {
            if(i==0)
            {
                x_pos.push_back(vir_lx);
                i_type.push_back(0);
                h_sl.push_back(h_sl_pilot);
                rho.push_back(rhoi);
                rho_hts.push_back(rhoi);
                vx.push_back(0);
                p.push_back(pi);
                temp = temp+1;
            }
            else if(i==(nx_wall-1))
            {
                x_pos.push_back(vir_lx+(i*dx));
                i_type.push_back(0);
                h_sl.push_back(h_sl_pilot);
                rho.push_back(rhoi);
                rho_hts.push_back(rhoi);
                vx.push_back(0);
                p.push_back(pi);
                temp = temp+1;
            }
        }
    }
    n_wall_total = temp;
}
