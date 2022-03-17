#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::vector;
using std::cout;
using std::endl;
void neigh_list(vector<vector<long double> > x,vector<vector<int> > nc,vector<int> headlist, vector<int> taillist, vector<int> i_type,long double xtemp[],
                vector<int> & neighbour)
{
    extern const int dim;
    extern int ncell;
    extern long double h_sl_pilot;
    int j, k, m, icell, q, flag, next0, next1;
    long double dr,r;
    vector<int> nl;
    int nci[27];
    int dim_1=dim;
    long double dx[dim_1];
    vector<int> ().swap(neighbour);

    icell = cell_no(xtemp);


    if( (icell<=ncell) && (icell>=0) )
    {
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

        int nl_size=nl.size()-1;
        for(j=0; j<=nl_size; j++)
        {
            k = nl[j];
            if( i_type[k]==1)
            {
                dr = 0;
                for(m=0; m<dim_1; m++)
                {
                    dx[m] = (x[m][k]-xtemp[m]);
                    dr = dr+(dx[m]*dx[m]);
                }
                r = sqrtl(dr);

                if (r<=3.0*h_sl_pilot)
                {
                    neighbour.push_back(k);

                }
            }
        }
    }
}

