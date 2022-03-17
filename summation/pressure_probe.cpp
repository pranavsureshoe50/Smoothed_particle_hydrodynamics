#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::vector;
using std::cout;
using std::endl;

void pressure_sensor(vector<vector<long double> > x, vector<vector<int> > nc,vector<long double> p,
                     vector<int> headlist, vector<int> taillist, vector<int> i_type)
{
    extern long double wall_break_time,vir_lx,vir_ly,vir_lz,h_sl_pilot,sim_time,dt;
    extern long double const h,gravity,rho0;
    long double x1=(3.22+vir_lx),y1=vir_ly+(0.26667*h);//3.255

    extern const int dim;
    extern int ncell,n_fluid_total;
    static int count_prpt=0;static long double prpt_tot=0.0,dt_tot=0.0;
    std::string filename1;
    std::ofstream myfile1;

    int i, j, k,icell, q, flag, next0, next1;
    long double time;
    vector<int> nl;
    int nci[27];
    int dim_1=dim;
    long double dx[dim_1],xtemp[dim_1];
    vector<int> neigh;
    long double pr_pt=0.0,ds_p=0.0,dy_p;
    time= (sim_time-wall_break_time)*powl( (gravity/h), 0.5);
    xtemp[0]=x1;
    xtemp[1]=y1;
    icell = cell_no(xtemp);

        q = 0;
        for (j=0; j<27; j++)
        {
            nci[j] = nc[icell][j];
        }

        for (j=0; j<27; j++)
        {
            flag = 0;
            next0 = nci[j];

            if (next0==-1)
            {
                continue;
            }
            if(headlist[next0]!=-1)
            {
                nl.push_back(headlist[next0]);
                while(flag==0)
                {
                    next1 = taillist[nl[q]];
                    if(next1!=-1)
                    {
                        nl.push_back(next1);
                        q = q+1;
                    }
                    if(next1==-1)
                    {
                        flag=1;
                    }
                }
                q = q+1;
            }
        }
        long double q1,q2,q3;
        q1= (y1+(0.045));q2=(y1-(0.045));q3=(x1-(2.5*h_sl_pilot));
        int nl_size=nl.size()-1;
        for(j=0; j<=nl_size; j++)
        {
            k = nl[j];
            if ( (k<=n_fluid_total) )
            {
                if( (x[1][k]<q1) && (x[1][k]>q2) && (x[0][k]>q3) )
                {
                    neigh.push_back(k);
                }
            }
        }


    int neigh_size=neigh.size();

    if(neigh_size>=3)
    {

        vector<long double>p_y(neigh_size,0.0);
        vector<long double>p_y_unsorted(neigh_size,0.0);
        vector<int>neigh_sorted(neigh_size,-1);

        for (i=0; i<neigh_size; i++)
        {
            p_y[i]=x[1][neigh[i]];
            p_y_unsorted[i]=x[1][neigh[i]];
        }

        quickSort_ld(p_y,0,neigh_size-1);

        for(i=0; i<neigh_size; i++)
        {
            for(j=0; j<neigh_size; j++)
            {
                if(p_y[i]==p_y_unsorted[j])
                {
                    neigh_sorted[i]=neigh[j];
                    break;
                }
            }
        }

        for(i=0; i<neigh_size; i++)
        {
            if( i==0)
            {
                dy_p= (p_y[i+1]-p_y[i])*0.5;
                if( p[neigh_sorted[i]]>0.0 )
                {
                   pr_pt=pr_pt+( p[neigh_sorted[i]]*(dy_p) );
                }
                ds_p=ds_p+dy_p;
            }

            else if(i<(neigh_size-1) )
            {
                dy_p=(p_y[i+1]-p_y[i-1])*0.5;
                if( p[neigh_sorted[i]]>0.0 )
                {
                   pr_pt=pr_pt+( p[neigh_sorted[i]]*(dy_p) );
                }
                ds_p=ds_p+dy_p;
            }

            else
            {
                dy_p=(p_y[i]-p_y[i-1])*0.5;
                if( p[neigh_sorted[i]]>0.0 )
                {
                   pr_pt=pr_pt+( p[neigh_sorted[i]]*(dy_p) );
                }
                ds_p=ds_p+dy_p;
            }
        }

        pr_pt= pr_pt/(ds_p + 1.0e-8);
        pr_pt= pr_pt / (rho0*gravity*h);
    }

    count_prpt=count_prpt+1;
    prpt_tot=prpt_tot+(pr_pt*dt);
    dt_tot=dt_tot+(dt);


    if(( count_prpt% 100)==0)
    {
        pr_pt=prpt_tot/dt_tot;
        count_prpt=0;
        prpt_tot=0.0;
        dt_tot=0.0;
    filename1="p_c.dat";
    myfile1.open(filename1.c_str(),std::ios_base::app);
    myfile1<<std::left<<std::fixed<<std::setw(10)<<std::setprecision(4)<<time;
    myfile1<<std::left<<std::fixed<<std::setw(10)<<std::setprecision(4)<<pr_pt<<endl;
    myfile1.close();
    }

}
