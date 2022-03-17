#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED
const int dim = 2;

const bool energy_calculation(false) ;
const bool use_mls(false) ;
const bool art_visc(true) ; ///true for adding artificial viscosity for numerical stability
const bool phy_visc(true) ; ///true for including fluid viscous forces and also to enable no-slip condition
const bool body_f(true);///true
const bool slip(true);/// 0 for free slip and 1 for no slip
const bool surface_tension(true);///true

const long double gravity = 0.980,t_damp=0.0;///Changes according to spheric paper. Rechange if needed.

const int fixed_virtual= 1;/// 0 for mirror and 1 for fixed virtual particles
const int n_vir_layer= 4;

const int nx = 100;
const int ny = 200;
const int nz = 0;
const long double sig = 24.5;
const long double Rb = 0.25;
const long double l = 4*Rb;
const long double h = 8*Rb;
const long double w = 0.0;
const long double times_l = 1.0;
const long double times_h = 1.0;
const long double times_w = 1.0;

const int kernel_type=2;
const long double k_f = 3.0;/// size of the support domain;k_f*h_sl;2.0 for cubic;3.0 for Gaussian
const long double K = 1.3;/// co-efficient of initial spacing to determine initial h_sl

const long double Re = 00.0;
const long double nu = 10.0;
const long double rho0 = 1000.0 ;//initial density
const long double pb = 100.0;///initial pressure or background pressure in wcsph
                                ///  (pb/rho*g*h) = 17.4

const long double c_s = 10.0;///10*vmax. change vmax for different problems///
const long double gamma1 = 7.0;///for tait's equation of state for water

const int max_iter = 3200000;
const int printevery =100;
const long double err_tol = 1.0e-5;

const long double nua = 1.0;//1.0e-6;//1.0e-8;
const long double rhoA0 = 100.0;///initial density
const long double gammaA = 1.4;///for tait's equation of state for air
const long double c_sa =14.14;
/// problem setup notes ///

/// in adami_wbt.cpp file change wall velocity acc.

#endif // CONST_H_INCLUDED
