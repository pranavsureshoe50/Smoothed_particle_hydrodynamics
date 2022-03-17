#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
#include "print_data.h"
using std::cout;
using std::endl;
using std::vector;
void create_air_particle(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,vector<long double> &h_sl,
                           vector<long double> & rho,vector<long double> & rho_hts,vector<long double> & drhodt,vector<long double> & p,vector<long double> & vx,
                           vector<long double> & vy,vector<long double> & vz,vector<int>& i_type)
{
    extern const int nx, ny, nz, dim,ny_wall,nx_wall;
    extern long double dx, dy, dz,vir_lx,vir_ly,vir_lz,dxa,dya,dza,l_wall,h_wall,h_sl_pilot;
    extern int n_fluid_total,n_air_total;
    //h_wall = h_wall;
    int i, j, k,nh,nv;
    int temp = 0 , n=0;
    n_air_total=0;
    long double rhoi = rhoA0,pi = pb,p_air=pb+(2*sig/Rb);
long double x1,y1,dist;
    if(dim==3)
    {
        for(k=1; k<=nz; k++)
        {
            for(j=1; j<=(ny); j++)
            {
                for(i=1; i<=(nx); i++)
                {

                    x_pos.push_back((i*dx)+(vir_lx));
                    y_pos.push_back(((j+ny)*dy)+(vir_ly));
                    z_pos.push_back((k*dz)+(vir_lz));
                    i_type.push_back(8);
                    temp = temp+1;
                }
            }
        }
    }

    else if(dim==2)
    {
        x1 = vir_lx + (0.5*l) ;
        y1 = vir_ly + (0.5*l) ;
        temp = 0;

        for(j=1; j<=(ny); j++)
        {
                for(i=1; i<=(nx); i++)
                {
                    dist = sqrtl(((x_pos[temp]-x1)*(x_pos[temp]-x1)) + ((y_pos[temp]-y1)*(y_pos[temp]-y1)) ) ;
                    if(dist <= Rb)
                    {
                        i_type[temp] = 8;
                        rho[temp] = rhoA0 ;
                        rho_hts[temp] = rhoA0 ;
                        p[temp] = p_air;
                        n++ ;
                    }
                    temp++ ;
                }
        }
    }
    else
    {
        for(i=1; i<=nx; i++)
        {
            x_pos.push_back((i*dx)+(vir_lx));
            i_type.push_back(8);
            temp = temp+1;
        }
    }
    n_air_total=n;
}
