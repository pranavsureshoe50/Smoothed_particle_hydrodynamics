#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include "header.h"
#include "print_data.h"
#include "const.h"
#define c 1.0e-10
using std::vector;
using std::cout;
using std::endl;

void column_height(vector<vector<long double> > x,vector<vector<long double> > v,vector<long double> w_kernel, vector<long double> h_sl, vector<int> i_type,
                   vector<int> pair_i,vector<int> pair_j)
{
    extern int n_fluid_total,ntotal,niac;
    extern long double const h,rho0;
    extern long double vir_lx,vir_ly,vir_lz,h_sl_pilot,sim_time;
    long double com=0.0,vel=0.0,n=0.0;
    extern vector<int> i_type;
    int i,j,k,l;
    long double time = sim_time;
    std::string filename1;
    std::ofstream myfile1;


    for(i=0;i<n_fluid_total;i++)
    {
        if(i_type[i] == 8)
        {
            com += x[1][i] ;
            n++ ;
        }
    }

    filename1="Centre_of_mass.dat";
    myfile1.open(filename1.c_str(),std::ios_base::app);
    myfile1<<std::left<<std::fixed<<std::setw(10)<<std::setprecision(4)<<time;
    myfile1<<std::left<<std::fixed<<std::setw(10)<<std::setprecision(4)<<(com/(n+c))<<endl;
    myfile1.close();

    ///-------------------------Velocity----------------------///
    n = 0.0;
    for(i=0;i<n_fluid_total;i++)
    {
        if(i_type[i] == 8)
        {
            vel += v[1][i] ;
            n++ ;
        }
    }


    filename1="Velocity_bubble.dat";
    myfile1.open(filename1.c_str(),std::ios_base::app);
    myfile1<<std::left<<std::fixed<<std::setw(10)<<std::setprecision(4)<<time;
    myfile1<<std::left<<std::fixed<<std::setw(10)<<std::setprecision(4)<<(vel/(n+c))<<endl;
    myfile1.close();
}
