#include <iostream>
#include <vector>
#include "header.h"
#include "const.h"
#include "print_data.h"
using std::cout;
using std::endl;
using std::vector;
void create_fluid_particle(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,vector<long double> &h_sl,
                           vector<long double> & rho,vector<long double> & rho_hts,vector<long double> & drhodt,vector<long double> & p,vector<long double> & vx,
                           vector<long double> & vy,vector<long double> & vz,vector<int>& i_type)
{
    extern const int nx, ny, nz, dim;
    extern long double dx, dy, dz,vir_lx,vir_ly,vir_lz,h_sl_pilot;
    extern const long double pb,rho0;
    extern int n_fluid_total;

    int i, j, k;
    int temp = 0;
    n_fluid_total=0;
    long double pi=pb,rhoi=rho0;

    if(dim==3)
    {
        for(k=1; k<=nz; k++)
        {
            for(j=1; j<=(ny); j++)
            {
                for(i=1; i<=(nx); i++)
                {

                    x_pos.push_back((i*dx)+(vir_lx));
                    y_pos.push_back((j*dy)+(vir_ly));
                    z_pos.push_back((k*dz)+(vir_lz));
                    h_sl.push_back(h_sl_pilot);
                    i_type.push_back(1);
                    rho.push_back(rhoi);
                    rho_hts.push_back(rhoi);
                    drhodt.push_back(0);
                    vx.push_back(0);
                    vy.push_back(0);
                    vz.push_back(0);
                    p.push_back(pi);
                    temp = temp+1;
                }
            }
        }
    }
    else if(dim==2)
    {
        for(j=1; j<=ny; j++)
        {
            for(i=1; i<=nx; i++)
            {
                x_pos.push_back((i*dx)+(vir_lx));
                y_pos.push_back((j*dy)+(vir_ly));
                i_type.push_back(1);
                h_sl.push_back(h_sl_pilot);
                rho.push_back(rhoi);
                rho_hts.push_back(rhoi);
                drhodt.push_back(0);
                vx.push_back(0);
                vy.push_back(0);
                p.push_back(pi);
                temp = temp+1;
            }
        }
    }
    else
    {
        for(i=1; i<=nx; i++)
        {
            x_pos.push_back((i*dx)+(vir_lx));
            i_type.push_back(1);
            h_sl.push_back(h_sl_pilot);
            rho.push_back(rhoi);
            rho_hts.push_back(rhoi);
            drhodt.push_back(0);
            vx.push_back(0);
            p.push_back(pi);
            temp = temp+1;
        }
    }
    n_fluid_total=temp;
}
