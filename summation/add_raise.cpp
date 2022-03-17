#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::vector;
using std::cout;
using std::endl;
void raise_wall(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,
               vector<long double> &h_sl,vector<long double> & rho,vector<long double> & rho_hts,
               vector<long double> & e, vector<long double> & e_hts,
               vector<long double> &p,vector<long double> & vx,vector<long double> & vy,vector<long double> & vz,
               vector<int>& i_type)
{
    extern const int  dim;
    extern long double dx, dy, dz, h_sl_pilot,vir_lx,vir_ly,vir_lz,fac;
    extern int ny_wall,n_fluid_total,n_raise_wall;

    int i, j, k;
    int temp = 0;

//////////////////////////////////////////////////
    if(dim==3)
    {


    }

    ///////////////////////////////////////////////////////////
    if(dim==2)
    {
        temp = 0;k=10;
        for(j=1; j<8; j++)
        {
            for(i=0; i<k; i++)
            {
                x_pos.push_back(2.0-(i*dx));
                y_pos.push_back((j*dy)+(vir_ly));
                i_type.push_back(411);
                h_sl.push_back(h_sl_pilot);
                rho.push_back(0);
                rho_hts.push_back(0);
                e.push_back(0);
                e_hts.push_back(0);
                vx.push_back(0);
                vy.push_back(0);
                p.push_back(0);
                temp = temp+1;
            }
            k=k-1;
        }
        n_raise_wall=temp;
    }
}
