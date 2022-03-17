#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::vector;
using std::cout;
using std::endl;
void remove_temp_wall(vector<vector<long double> > &x,vector<vector<long double> > &v,vector<long double> &h_sl,vector<long double> &rho, vector<long double> &rho_hts,
                    vector<long double> &p,vector<int>& i_type)
{
    extern const int  dim;
    extern int n_w_f,n_fixed_vir_total,ntotal;

    int i, j, k;
    int temp = 0;
//////////////////////////////////////////////////
    if(dim==3)
    {


    }
    ///////////////////////////////////////////////////////////

    if(dim==2)
    {
            ntotal=n_w_f+n_fixed_vir_total;
            x[0].resize(ntotal);
            x[1].resize(ntotal);
            i_type.resize(ntotal);///right wall
            h_sl.resize(ntotal);
            rho.resize(ntotal);
            rho_hts.resize(ntotal);
            v[0].resize(ntotal);
            v[1].resize(ntotal);
            p.resize(ntotal);
    }
}
