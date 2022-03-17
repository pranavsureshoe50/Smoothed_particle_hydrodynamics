#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <vector>
#include "const.h"
using std::vector;


void adami_wbt_wcsph(vector<vector<long double> > x,vector<long double> &rho,vector<long double> &p,
                     vector<int> pair_i,vector<int> pair_j,vector<long double> w_kernel, vector<int> i_type);

void art_visc_wcsph(vector<vector<long double> > x, vector<vector<long double> > v, vector<long double> h_sl,
                    vector<long double> rho, vector<vector<long double> >& f,vector<int> pair_i, vector<int> pair_j,
                    vector<vector<long double> > dwdx, vector<int> i_type);

void avg_fluid_vel( vector<vector<long double> > &v,vector<vector<long double> > &avg_v,vector<int> pair_i,vector<int> pair_j,
                    vector<long double> w_kernel,vector<int> i_type);

void apply_mls_correction(vector<vector<long double> > x,vector<long double> &rho,vector<int>& pair_i, vector<int>& pair_j,
                          vector<long double> & w_kernel,vector<int> &i_type);

void apply_hspr(vector<vector<long double> > x ,vector<long double> &p,vector<long double> &rho);

void body_force(vector<vector<long double> >& f);

void calc_dt(vector<vector<long double> > v, vector<long double> h_sl);

int cell_no(long double x[dim]);

void c_wcsph(vector<long double> rho);


void continuity_den( vector<long double> rho,vector<vector<long double> > v,vector<vector<long double> > avg_v,
                    vector<long double> &drhodt,vector<int> pair_i,vector<int> pair_j,vector<vector<long double> > dwdx,
                     vector<int> i_type);

void continuity_den_rf(vector<long double> rho,vector<long double> p,vector<vector<long double> > x,vector<vector<long double> > v,vector<vector<long double> > avg_v,
                       vector<long double> &drhodt,vector<int> pair_i,vector<int> pair_j,vector<vector<long double> > dwdx,
                       vector<int> i_type);

void column_height(vector<vector<long double> > x,vector<vector<long double> > v,vector<long double> w_kernel, vector<long double> h_sl, vector<int> i_type,
                   vector<int> pair_i,vector<int> pair_j);
void create_virtual_particle(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,
                             vector<long double> &h_sl,vector<long double> & rho,vector<long double> & rho_hts,
                             vector<long double> &p,vector<long double> & vx,vector<long double> & vy,
                             vector<long double> & vz, vector<int>& i_type);

void create_fluid_particle(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,vector<long double> &h_sl,
                           vector<long double> & rho,vector<long double> & rho_hts,vector<long double> & drhodt,
                            vector<long double> & p,vector<long double> & vx,vector<long double> & vy,vector<long double> & vz,
                           vector<int>& i_type);

void create_wall_particle(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,
                          vector<long double> &h_sl,vector<long double> & rho,vector<long double> & rho_hts,
                            vector<long double> &p,
                          vector<long double> & vx,vector<long double> & vy,vector<long double> & vz,vector<int>& i_type);

void create_air_particle(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,vector<long double> &h_sl,
                           vector<long double> & rho,vector<long double> & rho_hts,vector<long double> & drhodt,vector<long double> & p,vector<long double> & vx,
                           vector<long double> & vy,vector<long double> & vz,vector<int>& i_type);

void remove_temp_wall(vector<vector<long double> > &x,vector<vector<long double> > &v,vector<long double> &h_sl,vector<long double> &rho, vector<long double> &rho_hts,
                        vector<long double> &p,vector<int>& i_type);

void temp_wall(vector<long double> & x_pos, vector<long double> & y_pos, vector<long double> & z_pos,vector<long double> &h_sl,vector<long double> & rho,vector<long double> & rho_hts,
                vector<long double> &p,vector<long double> & vx,vector<long double> & vy,vector<long double> & vz,vector<int>& i_type);

void fsurface_pr_cor(vector<vector<long double> > x,vector<long double> rho,vector<long double> &p,vector<int> i_type,
                       vector<int> pair_i,vector<int> pair_j,vector<vector<long double> > dwdx);

void kernel(long double r,long double dx[dim],long double h_av);

void mat3inv(long double a[3][3],vector<vector<long double> > &inv1,int &singular_m);

void mat2inv (long double a[dim][dim],vector<vector<long double> > &inv) ;

void ncell_list(vector<vector<int> > &nc);

void pressure(vector<long double> rho,vector<long double> &p);

void pressure_sensor(vector<vector<long double> > x, vector<vector<int> > nc,vector<long double> p,
                     vector<int> headlist, vector<int> taillist, vector<int> i_type);

void p_f(vector<long double> rho, vector<long double> p, vector<vector<long double> >& f,
         vector<int> i_type, vector<int> pair_i, vector<int> pair_j,vector<vector<long double> > dwdx);

void p_f_wcsph(vector<long double> rho, vector<long double> p, vector<vector<long double> >& f,
               vector<int> i_type, vector<int> pair_i, vector<int> pair_j,vector<vector<long double> > dwdx);

void linked_list(vector<vector<long double> > x,vector<vector<int> > nc,  vector<int> &headlist, vector<int> &taillist, vector<int>& pair_i, vector<int>& pair_j,
                vector<long double> h_sl,vector<long double> & w_kernel, vector<vector<long double> >& dwdx,vector<int> &i_type);

void quickSort(vector<int> &arr,int,int);

void quickSort_ld(vector<long double> &arr, int left, int right);

void sum_density (vector<long double> & rho,vector<long double> w_kernel, vector<long double> h_sl, vector<int> i_type,
                   vector<int> pair_i,vector<int> pair_j);

void surf_tension( vector<vector<long double> > x,vector<long double> rho,  vector<vector<long double> >& f,
                   vector<int> i_type, vector<int> pair_i, vector<int> pair_j,vector<vector<long double> > dwdx);

void setup_problem_data(vector<vector<long double> > &x, vector<vector<long double> > &v ,vector<long double> &p,
                        vector<long double> &rho, vector<int> &i_type);

void boundary_check(vector<vector<long double> >& f , vector<vector<long double> > x, vector<vector<long double> > v , vector<int>     pair_i , vector<int>  pair_j , vector<int> i_type , vector<long double> h_sl , vector<long double> &p);

void time_integration_rk(vector<vector<long double> >& x, vector<vector<long double> >& x_hts, vector<vector<long double> >& v,vector<vector<long double> >& v_hts,
                         vector<vector<long double> >& avg_v,vector<long double> & rho,vector<long double> & rho_hts,vector<long double> & p,
                         vector<long double> &drhodt,vector<vector<long double> >& f,vector<long double> &h_sl,vector<vector<int> > nc, vector<int> &headlist,
                         vector<int> &taillist, vector<int>& pair_i,vector<int>& pair_j,vector<long double> & w_kernel, vector<vector<long double> >& dwdx,
                         vector<int> i_type);

void time_integration_vv(vector<vector<long double> >& x, vector<vector<long double> >& x_hts, vector<vector<long double> >& v,vector<vector<long double> >& v_hts,
                         vector<vector<long double> >& avg_v,vector<long double> & rho,vector<long double> & rho_hts,vector<long double> & p,
                         vector<long double> &drhodt,vector<vector<long double> >& f,vector<long double> &h_sl,vector<vector<int> > nc, vector<int> &headlist,
                         vector<int> &taillist, vector<int>& pair_i,vector<int>& pair_j,vector<long double> & w_kernel, vector<vector<long double> >& dwdx,
                         vector<int> i_type);

void visc_f(vector<vector<long double> > x, vector<vector<long double> > v, vector<vector<long double> > avg_v,
            vector<long double> rho, vector<vector<long double> >& f,vector<int> pair_i,vector<int> pair_j,
            vector<vector<long double> > dwdx,vector<int> i_type);

void visc_f1(vector<vector<long double> > x, vector<vector<long double> > v, vector<vector<long double> > avg_v,
            vector<long double> rho, vector<vector<long double> >& f,vector<int> pair_i,vector<int> pair_j,
            vector<vector<long double> > dwdx,vector<int> i_type);

void visc_f2(vector<vector<long double> > x, vector<vector<long double> > v, vector<vector<long double> > avg_v,
            vector<long double> rho, vector<vector<long double> >& f,vector<int> pair_i,vector<int> pair_j,
            vector<vector<long double> > dwdx,vector<int> i_type);

void wall_force(vector<vector<long double> > x, vector<vector<long double> >& f, vector<int> i_type, vector<long double> h_sl,
                vector<int> pair_i, vector<int> pair_j);

void int_energy_wcsph(vector<vector<long double> > x,vector<vector<long double> > v,vector<vector<long double> > avg_v,vector<long double> p,vector<long double> rho, vector<long double> &dedt,vector<int> pair_i,
                    vector<int> pair_j,vector<vector<long double> > dwdx, vector<int> i_type);


#endif // HEADER_H_INCLUDED
