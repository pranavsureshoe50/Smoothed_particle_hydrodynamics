#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
#include <fstream>
#define cc 1.0e-14
using std::cout;
using std::endl;
using std::vector;
using std::cin;
//using namespace std;
void int_energy_wcsph(vector<vector<long double> > x,vector<vector<long double> > v,vector<vector<long double> > avg_v,vector<long double> p,vector<long double> rho, vector<long double> &dedt,vector<int> pair_i,
                    vector<int> pair_j,vector<vector<long double> > dwdx, vector<int> i_type)
{
    extern int niac,n_fluid_total,iter;
    extern const int dim;
    extern vector<long double> mass,e,e_hts;
	std::string filename1;
    std::ofstream myfile1;
    int i,j,k,l;
	extern long double e1_ipe,e1f,e8_ipe,e8f,sim_time,dt;
 	long double e1_ke=0.0,e1_pe=0.0,e1_ie=0.0,e1tot=0.0;
	long double e8_ke=0.0,e8_pe=0.0,e8_ie=0.0,e8tot=0.0;
    long double etot,dv,dvdw;

    std::fill(dedt.begin(), dedt.end(), 0.0);

    for(k=0; k<niac; k++)
    {
        i=pair_i[k];
        j=pair_j[k];
        dvdw=0.0;
        if(i_type[i] == 1 &&  ((i_type[j] < 10)))
		{
			for(l=0; l<dim; l++)
			{
				if(i_type[j]>1000)
				{
					dv = v[l][i]-( (2.0*v[l][j])-avg_v[l][i]);
				}
				else
				{
					dv = v[l][i]-v[l][j];
				}
				dv = v[l][i]-v[l][j];
				dvdw = dvdw+(dv*dwdx[l][k]);
			}
        dedt[i]=dedt[i]+(mass[j]*dvdw/rho[j]);
        dedt[j]=dedt[j]+(mass[i]*dvdw/rho[i]);
        }
		else if(i_type[i] == 8 && (i_type[j] < 10))
		{
		for(l=0; l<dim; l++)
        {
            if(i_type[j]>1000)
            {
                dv = v[l][i]-( (2.0*v[l][j])-avg_v[l][i]);
            }
            else
            {
                dv = v[l][i]-v[l][j];
            }
            dv = v[l][i]-v[l][j];
            dvdw = dvdw+(dv*dwdx[l][k]);
        }
        dedt[i]=dedt[i]+(mass[j]*dvdw/rho[j]);
        dedt[j]=dedt[j]+(mass[i]*dvdw/rho[i]);
        }
    }

    for(k=0; k<n_fluid_total; k++)
    {
        dedt[k]=dedt[k]*p[k]/rho[k];
        e_hts[k]=e[k]+( dedt[k]*dt*0.5);
        e[k]=(2.0*e_hts[k])-e[k];
    }

	if((iter% 200) ==0)
    {
            for(i=0; i<n_fluid_total; i++)
            {
                if (i_type[i]==1 && e[i]==e[i])
				{
				e1_ke=e1_ke+(0.5*mass[i]*( (v[0][i]*v[0][i]) + (v[1][i]*v[1][i]) ) );
                e1_pe=e1_pe+(mass[i]*gravity*(x[1][i] -(0)) );
                e1_ie=e1_ie+(mass[i]*e[i]);
				}
				else if (i_type[i]==8 && e[i]==e[i])
				{
				e8_ke=e8_ke+(0.5*mass[i]*( (v[0][i]*v[0][i]) + (v[1][i]*v[1][i]) ) );
                e8_pe=e8_pe+(mass[i]*gravity*(x[1][i] -(0)) );
                e8_ie=e8_ie+(mass[i]*e[i]);
				}
            }
            e1tot=((e1_ke+e1_pe+e1_ie)-e1_ipe)/(e1_ipe-e1f+cc);
			e8tot=((e8_ke+e8_pe+e8_ie)-e8_ipe)/(e8_ipe-e8f+cc);
			etot = e1tot + e8tot ;

//			filename1="total_e.dat";
//            myfile1.open(filename1.c_str(),std::ios_base::app);
//            myfile1<<(sim_time)<<"\t"<<etot<<"\t"<<e1tot<<"\t"<<e8tot<<endl;
//            myfile1.close();
            long double enet = ((e1_ke+e1_pe+e1_ie)-e1_ipe+((e8_ke+e8_pe+e8_ie)-e8_ipe))/(cc+e8_ipe-e8f+e1_ipe-e1f) ;
            filename1="total_e_bubble.dat";
            myfile1.open(filename1.c_str(),std::ios_base::app);
            myfile1<<(sim_time*(gravity/h))<<"\t"<<enet<<"\t"<< (e1_ke+e8_ke)<<"\t"<<(e1_pe+e8_pe)<<"\t"<<(e1_ie+e8_ie)<<"\t"<<endl;
            myfile1.close();
    }
}

