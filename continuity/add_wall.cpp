#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::vector;
using std::cout;
using std::endl;
void temp_wall(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,vector<long double> &h_sl,vector<long double> & rho,vector<long double> & rho_hts,
              vector<long double> &p,vector<long double> & vx,vector<long double> & vy,vector<long double> & vz,vector<int>& i_type)
{
    extern const int  dim,n_vir_layer;
    extern const long double rho0,pb;
    extern long double dx, dy, dz, h_sl_pilot,vir_lx,vir_ly,vir_lz;
    extern int n_moving_wall,ny_wall,n_fluid_total;

    int i, j, k;
    int temp = 0;
    long double irho=rho0,ip=pb;
//////////////////////////////////////////////////
    if(dim==3)
    {


    }
    ///////////////////////////////////////////////////////////
    if(dim==2)
    {
        temp = 0;
        for(j=1; j<int(0.65*ny_wall); j++)
        {
            for(i=1; i<=n_vir_layer; i++)
            {
                x_pos.push_back((x_pos[n_fluid_total-1])+(i*dx));
                y_pos.push_back((j*dy)+(vir_ly));
                if(i==1)
                {
                    i_type.push_back(411);
                }
                else
                {
                    i_type.push_back(4111);
                }
                h_sl.push_back(h_sl_pilot);
                rho.push_back(irho);
                rho_hts.push_back(irho);
                vx.push_back(0);
                vy.push_back(0);
                p.push_back(ip);
                temp = temp+1;
            }
        }
        n_moving_wall=temp;
    }
}
