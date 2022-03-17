/*****************************************************************************/
/**  LAgrangian Meshless Particle based Hydrodynamics solver (LAMPHS code)  **/
/*****************************************************************************/
#include <fstream>
#include <iostream>
#include <vector> ///c++ dynamic array similar to pointers arrays
#include <cmath>  ///contains math library functions
#include "header.h" /// contains the function declarations
#include "const.h"  /// contains all the global constants of the problem
#include "print_data.h" /// contains a object with templated member functions for printing different variables

using std::vector; /// directive required for recognizing vector type container
using std::cout;
using std::cin;
using std::endl;
int iter=0,NX, NY, NZ, ncell, ntotal, n_fixed_vir_total, n_water_total,n_wall_total,n_moving_wall=0,n_raise_wall=0, n_fluid_total,nf_total = 0,n_air_total = 0,niac,n_w_f,print_count=0,m;/// refer manual for the description of variable names
int nx_wall, ny_wall, nz_wall,nx_vir, ny_vir, nz_vir;
long double sim_time,wall_break_time,dt=0.0001,dx, dy, dz,vir_lx=0.0, vir_ly=0.0, vir_lz=0.0, L, W, H, cell_l, mass_f, mass_a,wtemp, h_sl_pilot;/// refer manual for the description of variable names
long double dwdxtemp[dim],zeta,xtemp[dim];
vector<long double> mass,c_i,rhostar;
vector<int > countip, i_type;
int prog_terminate_flag=0;
long double l_wall,h_wall,w_wall,e1_ipe,e1f,e8_ipe,e8f;
print printdata;
vector< vector<long double> > xstar, vstar;
vector<long double> h_sl,rho,drhodt,rho_hts,p,w_kernel,e,e_hts,dedt;
int main()
{
    long double vol,dmax;
    int i;

    vector< vector<long double> > x, v, x_hts, v_hts,dwdx(dim,vector<long double>(0,0.0));
    vector<long double> x_pos, y_pos, z_pos, vx, vy, vz ;
    vector<int> pair_i, pair_j;

    n_fixed_vir_total = 0;
    n_wall_total = 0;
    n_fluid_total = 0;
    n_w_f=0;
    niac = 0;
////////////////////////////////////////////////
/// calculating initial inter-particle seperation
    dx = l/(nx+1); dz = w/(nz+1); dy = h/(ny+1);
///////////////////////////////////////////////////////////////////////////////////////////////
///calculating the smoothing length based on maximum interparticle seperation in x,y,z direction
    switch (dim)
    {
    case 3 :
        dmax = fmax(dx,fmax(dy,dz)); vol = dx*dy*dz ; break ;
    case 2 :
        dmax = fmax(dx,dy); vol = dx*dy; break;
    case 1 :
        dmax = dx; vol = dx ; break;
    }
    h_sl_pilot = K*dmax;
///////////////////////////////////////////////////////////////////////////////////////////////
///calculating the mass of particle
    mass_a = rhoA0*vol;
    mass_f = rho0*vol;
////////////////////////////////////////////////////////
///calculating the length of the virtual particle layers

        vir_lx = n_vir_layer*dx;
        vir_ly = n_vir_layer*dy;
        vir_lz = n_vir_layer*dz;
/////////////////////////////////////////////////////////
///calculating the size of the computational domain
    switch (dim)
    {
    case 3 :
        if( fmodl( (times_w*w),( dz) ) >1e-10)
        {
            w_wall = ( (times_w*w)-fmodl( (times_w*w),( dz) )+( dz) );
            nz_wall = double( w_wall/( dz) )+1;
        }
        else
        {
            w_wall =times_w*w;
            nz_wall = double( w_wall/( dz) )+1;
        }

        if( fmodl( ((w_wall)+(2.0*vir_lz)),( dz) ) >1e-10 )
        {
            W = ( (w_wall)+(2.0*vir_lz)-fmodl(((w_wall)+(2.0*vir_lz)),( dz))+(( dz)) );
            nz_vir = double(W/( dz))+1;
        }
        else
        {
            W = (w_wall)+(2.0*vir_lz);
            nz_vir = double(W/( dz) )+1;
        }

    case 2 :
        if( fmodl( (times_h*h),( dy) ) >1e-10 )
        {
            h_wall = ( (times_h*h)-fmodl( (times_h*h),( dy) )+ ( dy) );
            ny_wall = double( h_wall/( dy) )+1;
        }
        else
        {
            h_wall =times_h*h;
            ny_wall = double( h_wall/( dy) )+1;
        }

        if( fmodl( ((h_wall)+(2.0*vir_ly)),( dy) ) > 1e-10 )
        {
            H = (((h_wall)+(2.0*vir_ly))-fmodl(((h_wall)+(2.0*vir_ly)),( dy))+ ( dy));
            ny_vir = double( H/( dy) ) + 1 ;
        }
        else
        {
            H = ( (h_wall)+(2.0*vir_ly) );
            ny_vir = double(H/( dy) )+1;
        }

    case 1 :
        if( fmodl( (times_l*l),( dx) ) >1e-10 )
        {
        l_wall = ( (times_l*l)-fmodl( (times_l*l),( dx) )+( dx) );
        nx_wall = double( l_wall/( dx) )+1;
        }
        else
        {
        l_wall =times_l*l;
        nx_wall = double( l_wall/( dx) )+1;
        }

        if( fmodl( ( (l_wall) + (2.0*vir_lx) ),( dx) ) >1e-10 )
        {
        L = ( (l_wall)+(2.0*vir_lx)- fmodl( ((l_wall)+(2.0*vir_lx)),( dx) )+(( dx)) );
        nx_vir = double(L/( dx))+1;
        }
        else
        {
        L = ( (l_wall)+(2.0*vir_lx) );
        nx_vir = double(L/( dx))+1;
        }
        break;
    }

////////////////////////////////////////////////////////////////////////////
///creating the initial particle distribution

        create_fluid_particle( x_pos, y_pos, z_pos, h_sl, rho, rho_hts, drhodt, p, vx, vy, vz, i_type);
        create_air_particle( x_pos, y_pos, z_pos,h_sl, rho, rho_hts, drhodt, p, vx,vy,vz,i_type);
        create_wall_particle( x_pos,  y_pos, z_pos,h_sl, rho, rho_hts,  p, vx, vy, vz, i_type);
        n_w_f = n_wall_total+n_fluid_total+n_raise_wall;
        create_virtual_particle( x_pos,  y_pos, z_pos,h_sl,rho,rho_hts, p, vx, vy,vz,i_type);
        //temp_wall( x_pos,  y_pos, z_pos,h_sl,rho,rho_hts, p, vx, vy,vz,i_type);
        ntotal = n_w_f+n_fixed_vir_total+n_moving_wall;
        n_water_total = n_fluid_total - n_air_total ;
        //n_fluid_total += n_air_total;
////////////////////////////////////////////////////////////////////////////
///initializing the variables
    for(i=0; i<ntotal; i++)
    {
        if(i_type[i] == 8)
            c_i.push_back(c_sa);
        else
            c_i.push_back(c_s) ;
        countip.push_back(0);
    }

    for(i=0; i<n_fluid_total; i++)
    {
        rhostar.push_back(0);
    }

    x.push_back(x_pos);
    x_hts.push_back(x_pos);
    v.push_back(vx);
    v_hts.push_back(vx);

    if(dim==2)
    {
        x.push_back(y_pos);
        x_hts.push_back(y_pos);
        v.push_back(vy);
        v_hts.push_back(vy);
    }
    if(dim==3)
    {
        x.push_back(y_pos);
        x.push_back(z_pos);
        x_hts.push_back(y_pos);
        x_hts.push_back(z_pos);
        v.push_back(vy);
        v.push_back(vz);
        v_hts.push_back(vy);
        v_hts.push_back(vz);
    }
    vector<vector<long double> > f(dim, vector<long double>(n_fluid_total,0.0) );
    vector<vector<long double> > avg_v(dim, vector<long double>(n_fluid_total,0.0) );
    e.resize(n_fluid_total,0.0);
    e_hts.resize(n_fluid_total,0.0);
    dedt.resize(n_fluid_total,0.0);
    for(i=0;i<dim;i++)
    {
        xstar.push_back(rhostar);
        vstar.push_back(rhostar);
    }

//////////////////////////////////////////////////////////////////////////////////

    for(i=0; i<ntotal; i++)
    {
        if(i_type[i] == 8)
        {
            mass.push_back(mass_a);
        }
        else
        {mass.push_back(mass_f);}
    }

///////////////////////////////////////////////////////////////////////////
///calculating the no. of cells in each direction
///calculating the cell length for the linked list
    cell_l = (3.0001*h_sl_pilot);
    NX = ceil(L/cell_l);
    if((dim==2)||(dim==3))
    {
        NY = ceil(H/cell_l);
    }
    else
    {
        NY = 1;
    }
    if(dim==3)
    {
        NZ = ceil(W/cell_l);
    }
    else
    {
        NZ = 1;
    }
//////////////////////////////////////////////////////////////////
///creating the list of neighbor cells for any given cell
    ncell = NX*NY*NZ;//total no. of cells
    vector<vector<int> > nc(ncell, vector<int> (27,-1) );
    ncell_list(nc);//calling the function which creates the neighbor cell list
    //printdata.SaveData<long double, long double, long double,long double,int > (x,v,p,rho,i_type, "inital_setup");

    vector<int> headlist(ncell,-1);
    vector<int> taillist(ntotal,-1);
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// Hydrostatic pressure apply and density change
apply_hspr(x ,p,rho) ;
/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Problem specifications
    setup_problem_data(x,v ,p,rho, i_type);
    int cap = ntotal*100;
    pair_i.reserve(cap);pair_j.reserve(cap);w_kernel.reserve(cap);dwdx[0].reserve(cap);dwdx[1].reserve(cap);
    linked_list(x, nc,headlist,taillist, pair_i, pair_j,h_sl, w_kernel, dwdx, i_type);
    adami_wbt_wcsph(x,rho, p,  pair_i,pair_j, w_kernel,  i_type);
///////////////////////////////////////////////////////////////////////
printdata.SaveData<long double, long double, long double,long double,int > (x,v,p,rho,i_type, "final_setup");
///////////////////////////////////////////////////////////////////////////////////////////////
///Initial energy
e1_ipe=0.0,e1f=16472.6,e8_ipe=0.0,e8f=381.313;
for(i=0;i<n_fluid_total;i++)
{
    if (i_type[i] ==  1)
     e1_ipe += (rho[i]*9.81*x[1][i]*dx*dy);
    else if  (i_type[i] ==  8)
     e8_ipe += (rho[i]*9.81*x[1][i]*dx*dy);
}

///////////////////////////////////////////////////////////////////////
/// start of time iteration

    std::string filename1;
    std::ofstream myfile1;
    while(iter<=max_iter)
    {
        calc_dt(v, h_sl);
        filename1="dt_history.dat";
        myfile1.open(filename1.c_str(),std::ios_base::app);
        myfile1<<iter<<"\t"<<dt<<"\t"<<sim_time<<endl;
        myfile1.close();

        sim_time=sim_time+dt;
        if(prog_terminate_flag==0 )
        {
            time_integration_vv(x,x_hts,v,v_hts,avg_v,rho,rho_hts,p,drhodt,f,h_sl,nc,headlist,taillist,pair_i,pair_j,w_kernel,dwdx,i_type);
        }
        if(prog_terminate_flag==1 || iter==max_iter)
        {
            std::cout<<"solution converged :)";
            printdata.SaveData<long double, long double,long double, long double, int > (x,v,p,rho,i_type,"result");
            return 0;
        }
        iter++;
    }
////////////////////////////////////////////////////////////////////////
    return 0;
}///end of main program
