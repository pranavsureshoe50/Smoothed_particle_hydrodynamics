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

void setup_problem_data(vector<vector<long double> > &x, vector<vector<long double> > &v ,vector<long double> &p,
                        vector<long double> &rho, vector<int> &i_type)
{
    extern print printdata;
    extern int n_fluid_total, n_water_total, ntotal,n_fixed_vir_total,n_air_total,n_wall_total, ncell,nx_wall,
    ny_wall, nz_wall,nx_vir, ny_vir, nz_vir, NX,NY,NZ ,vir_lx,vir_ly,vir_lz;
    extern long double L,W,H, dx,dy,dz,h_sl_pilot, cell_l,sim_time;
    char k;
    int i;

    REREAD:
    int program_continue=0,iter_continue=0;
    std::string input_filename1;
    cout<<"|-----------------------------|"<<endl;
    cout<<"|        program begins       |"<<endl;
    cout<<"|-----------------------------|"<<endl;
    cout<<"was the program interupted before? (y/n):: ";
    cin>>k;
    if(k == 'y' || k=='Y')
    {
        cout<<"Enter file name to read inital data..."<<endl;
        cin>>input_filename1;
        cout<<"Enter iter no.(THE NO. IN THE FILE-NAME):";
        cin>>iter_continue;
        cout<<"Enter sim_time";
        cin>>sim_time;
        std::ifstream infile;
        infile.open(input_filename1.c_str());
        if ( infile.is_open() )
        {
            cout<<"file opening successful......Reading data!"<<endl;
            for (int j = 0; j < ntotal; ++j)
            {
                for (int i = 0; i < 7; ++i)
                {
                    if(i==0 || i==1)    {  infile >> x[i][j];    }
                    if(i==2 || i==3)    {  infile >> v[i-2][j];  }
                    if(i==4)            {  infile >> p[j];       }
                    if(i==5)            {  infile >> rho[j];     }
                    if(i==6)            {  infile >> i_type[j];  }
                    infile.get(); // Throw away the comma
                }
            }
        }
        else
        {
            cout<<"file could not be read :( check file name and path in source!"<<endl;
            goto REREAD;
        }
        infile.close();
        iter=(iter_continue*printevery)+1;
        print_count=iter_continue+1;
        //linked_list(x, nc,headlist,taillist, pair_i, pair_j,h_sl, w_kernel, dwdx, i_type);
    }

    std::string filename1;
    std::ofstream myfile1;
    filename1 = "problem_details.dat";
    myfile1.open(filename1.c_str());
    myfile1<<"--------------------------------------------- "<<std::endl
           <<"TITLE = Bubble rise "<<std::endl
           <<"--------------------------------------------- "<<std::endl<<endl
           <<"----------------problem description----------------"<<endl
           <<"problem dimensionality= "<<dim<<endl
           <<"no. of fixed ghost particle layers= "<<n_vir_layer<<endl<<endl
           <<"----------------domain description----------------"<<endl
           <<"domain size(fluid) -->> l= "<<l<<"; h= "<<h<<"; w= "<<w<<std::endl
           <<"domain size(including virtual layers) -->> L= "<<L<<"; H= "<<H<<"; W= "<<W<<std::endl
           <<"no. of particles -->> nx= "<<nx<<"; ny= "<<ny<<"; nz= "<<nz<<std::endl
           <<"initial inter-particle spacing -->> dx= "<<dx<<"; dy= "<<dy<<"; dz= "<<dz<<std::endl
           <<"co-efficient of initial spacing for smoothing length= "<<K<<endl
           <<"smoothing length h= "<<h_sl_pilot<<endl
           <<"no. of wall particles -->> nx_wall= "<<nx_wall<<"; ny_wall= "<<ny_wall<<"; nz_wall= "<<nz_wall<<std::endl
           <<"no. of virtual particles -->"<<"nx_vir="<<nx_vir<<",ny_vir="<<ny_vir<<",nz_vir="<<nz_vir<<std::endl
           <<"size of virtual layer -->"<<"vir_lx="<<vir_lx<<",vir_ly="<<vir_ly<<",vir_lz="<<vir_lz<<std::endl
           <<"no. of cells -->>"<< "NX= "<<NX<<"; NY= "<<NY<<"; NZ= "<<NZ<<std::endl
           <<"cell_l= "<<cell_l<<std::endl
           <<"total no. of cells= "<<ncell<<std::endl
           <<"total particles ="<<ntotal<<std::endl
            <<"total fluid particles ="<<n_fluid_total<<std::endl
             <<"total water particles ="<<n_water_total<<std::endl
              <<"total air particles ="<<n_air_total<<std::endl
           <<"total wall particles ="<<n_wall_total<<std::endl
           <<"total fixed virtual particles ="<<n_fixed_vir_total<<std::endl
           <<"----------------fluid properties----------------"<<endl
           <<"density= "<<rho0<<endl
          <<"density of air= "<<rhoA0<<endl
          <<"dynamic viscosity of air= "<<nua<<endl
           <<"Background pressure= "<<pb<<endl
           <<"initial sound speed= "<<c_s<<endl
           <<"initial sound speed= "<<c_sa<<endl
           <<"dynamic viscosity of water= "<<nu<<endl;
            myfile1.close();

  ///////////////////////////////////////////////////////////////////////
  ///Files to be truncated
    cout<< "Do u have any files to be truncated? Eg. dt_history.dat, ha.dat , y_pos.dat (y/n)"<< endl;
    cin >> k ;
    if(k == 'y' || k=='Y')
    {
        cout<< "Files truncating..."<< endl;
        filename1="dt_history.dat";
        myfile1.open(filename1.c_str(),std::ios_base::trunc);
        myfile1.close();
        filename1="Velocity_bubble.dat";
        myfile1.open(filename1.c_str(),std::ios_base::trunc);
        myfile1.close();
        filename1="Centre_of_mass.dat";
        myfile1.open(filename1.c_str(),std::ios_base::trunc);
        myfile1.close();
    }

}
