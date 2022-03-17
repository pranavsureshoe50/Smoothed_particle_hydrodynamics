#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"
#include "const.h"
using std::cout;
using std::endl;
using std::vector;
int cell_no(long double x[dim])
{
    extern const int dim;
    extern int NX,NY;
    extern long double cell_l;

    int cellno1;
    int l;
    int dim_1=dim;
    long double x_step[dim_1];

    if(dim==3)
    {
        for(l=0; l<dim; l++)
        {
            x_step[l] = (x[l]/cell_l);
            if((x_step[l]==floor(x_step[l]))&&(floor(x_step[l]!=0)))
            {
                x_step[l] = (floor(x_step[l])-1);
            }
            else
            {
                x_step[l] = (floor(x_step[l]));
            }
        }
        cellno1=( (x_step[0] + (x_step[1]*NX) + (x_step[2]*(NX*NY)) ) );
    }

    else if(dim==2)
    {
        for(l=0; l<dim; l++)
        {
            x_step[l] = (x[l]/cell_l);
            if((x_step[l]==floor(x_step[l]))&&(floor(x_step[l]!=0)))
            {
                x_step[l] = (floor(x_step[l])-1);
            }
            else
            {
                x_step[l] = (floor(x_step[l]));
            }
        }
        cellno1=((x_step[0]+(x_step[1]*NX)));
    }
    else if(dim==1)
    {
        for(l=0; l<dim; l++)
        {
            x_step[l] = (x[l]/cell_l);
            if(x_step[l]==floor(x_step[l]))
            {
                x_step[l] = (floor(x_step[l])-1);
            }
            else
            {
                x_step[l] = (floor(x_step[l]));
            }
        }
        cellno1=(x_step[0]);
    }
return cellno1;
}

