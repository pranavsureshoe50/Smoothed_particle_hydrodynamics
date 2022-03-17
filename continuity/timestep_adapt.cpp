#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
void calc_dt(vector<vector<long double> > v, vector<long double> h_sl)
{
    extern const int dim;
    extern long double dt;
    extern const long double nu,gravity,c_s;
    extern int n_fluid_total;
    int i,l;
    long double vtemp,vmax;
    long double h_min ;/// change beta_dt if required
    vector<long double> v_mag(n_fluid_total,0.0);
    vector<long double> dt_temp(4,0.0);

    h_min= *std::min_element( h_sl.begin(),h_sl.end() );


    for(i=0; i<n_fluid_total; i++)
    {
        vtemp=0.0;
        for(l=0; l<dim; l++)
        {
            vtemp=vtemp+(v[l][i]*v[l][i]);
        }
        v_mag[i]=sqrtl(vtemp);
    }

    vmax=*std::max_element(v_mag.begin(),v_mag.end());

    dt_temp[0]= 0.25*(h_min/ (vmax+c_sa ) );
    dt_temp[1]= 0.125*(h_min*h_min*rho0/ nu ) ;
    dt_temp[2]= 0.25*sqrtl(h_min/gravity);
    dt_temp[3]= 0.25*sqrtl(rhoA0*h_min*h_min*h_min/(2*3.1416*sig));
    dt= *std::min_element( dt_temp.begin(),dt_temp.end() );
//dt = 1.0e-6 ;

}
