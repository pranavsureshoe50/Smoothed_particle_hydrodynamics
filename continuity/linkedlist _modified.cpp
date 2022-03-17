#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include "header.h"
#include "const.h"
#include "print_data.h"
using std::cout;
using std::endl;
using std::vector;

void linked_list(vector<vector<long double> > x,vector<vector<int> > nc,  vector<int> &headlist, vector<int> &taillist, vector<int>& pair_i, vector<int>& pair_j, vector<long double> h_sl,vector<long double> & w_kernel, vector<vector<long double> >& dwdx,vector<int> &i_type)
{
    extern const int dim;
    extern const long double k_f;
    extern int niac,ncell,n_fluid_total,ntotal;
    extern long double wtemp,dwdxtemp[];
    extern print printdata;

    int i, j, k, m, icell, flag, it,p1,nn=0;
    long double dr,r,h_av;
    vector<int> nl,cellno(ntotal,0.0);
    int nci[27],pt,p9;
    int dim_1=dim;
    long double dx[dim_1],xtemp[dim_1];
    w_kernel.clear(); pair_i.clear();pair_j.clear();
    dwdx[0].clear(); dwdx[1].clear();
    vector<int> countip(ntotal,0);
    niac=0;
    vector<vector<int> > particle_list(ncell,vector<int> (0 , 0))  ;

    for (i=0; i<ntotal; i++)
    {
        for(m=0; m<dim; m++)
        {
            xtemp[m]=x[m][i];
        }
        icell = cell_no(xtemp);
        if((icell<ncell) && (icell>=0) )
        {
            cellno[i]=(icell);
            particle_list[icell].push_back(i) ;
        }
        else
        {
            i_type[i]= -1;
        }
    }


    for (i=0; i<n_fluid_total; i++)
    {
        if(i_type[i] == -1)     {     continue;    }
        icell = cellno[i];//Take its cell no.

        for (j=0; j<27; j++)
        {
            nci[j] = nc[icell][j];// All neighbouring cells of this cell is put in nci array
        }

        for (j=0; j< 27; j++)
        {
            p9 = nci[j];//Take one cell
            if(p9 < 0  || p9> ncell)
            {
                break;
            }
            else if(particle_list[p9].size() >= 0 && particle_list[p9].size() < int((n_fluid_total*0.25)) )
            {

                p1 = particle_list[p9].size() ;

                for(it=0; it< p1; it++)
                {
                    pt = particle_list[p9][it];
                    if(pt > i)//Verify with prasanna
                    {
                        k = pt;
                        if(i_type[k]>0)
                        {
                            dr = 0;
                            for(m=0; m<dim_1; m++)
                            {
                                dx[m] = (x[m][i]-x[m][k]);
                                dr = dr+(dx[m]*dx[m]);
                            }
                            r = sqrtl(dr);
                            h_av = (h_sl[i]+h_sl[k])*0.5;
                            if (r>0.0 && r<(k_f*h_av))
                            {
                                pair_i.push_back(i);
                                pair_j.push_back(k);
                                countip[i]++; countip[k]++;
                                kernel(r,dx,h_av);
                                w_kernel.push_back(wtemp);
                                dwdx[0].push_back(dwdxtemp[0]);
                                if(dim==2)
                                {
                                    dwdx[1].push_back(dwdxtemp[1]);
                                }
                                niac++;
                            }
                        }
                    }
                }
            }
        }
    }

}
