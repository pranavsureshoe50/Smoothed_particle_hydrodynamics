#include <cmath>
#include "header.h"
#include "const.h"
void kernel(long double r,long double dx[dim],long double h_av)
{
    extern const int dim;
    extern long double wtemp,dwdxtemp[];
    extern const long double k_f;
    extern int const kernel_type;

    long double q, alpha_d,c0,c1;
    int l;

        c0=expl(-9);
    c1=c0*(10);

    q = r/h_av;

    if(kernel_type==0)
    {
        alpha_d = 1.0/( powl(h_av,dim)*powl(M_PI,(dim/2.0) ) );

        if((q>=0.0) && (q<3.0))
        {
            wtemp = alpha_d*(expl(-q*q) );
            for(l=0; l<dim; l++)
            {
                dwdxtemp[l] = wtemp*(-2.0*(dx[l]/(h_av*h_av) ) );
            }
        }
        else
        {
            wtemp = 0.0;
            for(l=0; l<dim; l++)
            {
                dwdxtemp[l] = 0.0;
            }
        }
    }

    if(kernel_type==1)
    {

        if(dim==3)
        {
            alpha_d = 3.0/(2.0*M_PI*powl(h_av,3.0));
        }
        else if(dim==2)
        {
            alpha_d = 15.0/(7.0*M_PI*powl(h_av,2.0));
        }
        else
        {
            alpha_d = 1.0/h_av;
        }

        if((q>=0.0) && (q<1.0))
        {
            wtemp = alpha_d*((2.0/3.0)-(powl(q,2.0))+(powl(q,3.0)*0.5));
            for(l=0; l<dim; l++)
            {
                dwdxtemp[l] = alpha_d*(-2.0+(1.5*q))*(dx[l]/(h_av*h_av));
            }
        }
        else if((q>=1.0) && (q<2.0))
        {
            wtemp = alpha_d*((1.0/6.0)*(powl((2.0-q),3.0)));
            for(l=0; l<dim; l++)
            {
                dwdxtemp[l] = alpha_d*(-0.5)*(powl((2.0-q),2.0))*dx[l]/(r*h_av);
            }
        }
        else
        {
            wtemp = 0.0;
            for(l=0; l<dim; l++)
            {
                dwdxtemp[l] = 0.0;
            }
        }
    }

    if(kernel_type==2)
    {
        alpha_d = 1.0/( ( powl(h_av,dim)*powl(M_PI,(dim/2.0) ) )*(1.0-c1) );
        if((q>=0.0) && (q<3.0))
        {
            wtemp = alpha_d*(expl(-q*q)-c0 );
            for(l=0; l<dim; l++)
            {
                dwdxtemp[l] = alpha_d*(expl(-q*q))*-2.0*dx[l]/(h_av*h_av);
            }
        }
        else
        {
            wtemp = 0.0;
            for(l=0; l<dim; l++)
            {
                dwdxtemp[l] = 0.0;
            }
        }
    }

}
