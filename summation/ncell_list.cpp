#include <iostream>
#include "header.h"
#include "const.h"
#include "print_data.h"
void ncell_list(vector<vector<int> > &nc)
{
    extern const int dim;
    extern int NX, NY, NZ, ncell;
    int i,j;
    vector<int> a(27,-1);

    if(dim==3)
    {
        for (i=0; i<ncell; i++)
        {
            int k = 0;
            int b1 = i-(NX*NY)-NX-1;
            int b2 = i-(NX*NY)-NX;
            int b3 = i-(NX*NY)-NX+1;
            int b4 = i-(NX*NY)-1;
            int b5 = i-(NX*NY);
            int b6 = i-(NX*NY)+1;
            int b7 = i-(NX*NY)+NX-1;
            int b8 = i-(NX*NY)+NX;
            int b9 = i-(NX*NY)+NX+1;
            int m1 = i-NX-1;
            int m2 = i-NX;
            int m3 = i-NX+1;
            int m4 = i-1;
            int m5 = i;
            int m6 = i+1;
            int m7 = i+NX-1;
            int m8 = i+NX;
            int m9 = i+NX+1;
            int t1 = i+(NX*NY)-NX-1;
            int t2 = i+(NX*NY)-NX;
            int t3 = i+(NX*NY)-NX+1;
            int t4 = i+(NX*NY)-1;
            int t5 = i+(NX*NY);
            int t6 = i+(NX*NY)+1;
            int t7 = i+(NX*NY)+NX-1;
            int t8 = i+(NX*NY)+NX;
            int t9 = i+(NX*NY)+NX+1;

            if((i>=(NX*NY))&&(((i%(NX*NY))>=NX)&&(((i%(NX*NY))%NX)!=0)))
            {
                nc[i][k] = b1;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if((i>=(NX*NY))&&((i%(NX*NY))>=NX))
            {
                nc[i][k] = b2;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if((i>=(NX*NY))&&(((i%(NX*NY))>=NX)&&(((i%(NX*NY))%NX)!=(NX-1))))
            {
                nc[i][k] = b3;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i>=(NX*NY))&&(((i%(NX*NY))%NX)!=0))
            {
                nc[i][k] = b4;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if(i>=(NX*NY))
            {
                nc[i][k] = b5;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if((i>=(NX*NY))&&(((i%(NX*NY))%NX)!=(NX-1)))
            {
                nc[i][k] = b6;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i>=(NX*NY))&&(((i%(NX*NY))<(NX*(NY-1)))&&(((i%(NX*NY))%NX)!=0)))
            {
                nc[i][k] = b7;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i>=(NX*NY))&&((i%(NX*NY))<(NX*(NY-1))))
            {
                nc[i][k] = b8;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i>=(NX*NY))&&(((i%(NX*NY))<(NX*(NY-1)))&&(((i%(NX*NY))%NX)!=(NX-1))))
            {
                nc[i][k] = b9;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }

            if(((i%(NX*NY))>=NX)&&(((i%(NX*NY))%NX)!=0))
            {
                nc[i][k] = m1;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if((i%(NX*NY))>=NX)
            {
                nc[i][k] = m2;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if(((i%(NX*NY))>=NX)&&(((i%(NX*NY))%NX)!=(NX-1)))
            {
                nc[i][k] = m3;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if(((i%(NX*NY))%NX)!=0)
            {
                nc[i][k] = m4;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if(m5>=0)
            {
                nc[i][k] = m5;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if(((i%(NX*NY))%NX)!=(NX-1))
            {
                nc[i][k] = m6;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if(((i%(NX*NY))<(NX*(NY-1)))&&(((i%(NX*NY))%NX)!=0))
            {
                nc[i][k] = m7;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i%(NX*NY))<(NX*(NY-1)))
            {
                nc[i][k] = m8;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if(((i%(NX*NY))<(NX*(NY-1)))&&(((i%(NX*NY))%NX)!=(NX-1)))
            {
                nc[i][k] = m9;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }

            if((i<(NX*NY*(NZ-1)))&&(((i%(NX*NY))>=NX)&&(((i%(NX*NY))%NX)!=0)))
            {
                nc[i][k] = t1;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if((i<(NX*NY*(NZ-1)))&&((i%(NX*NY))>=NX))
            {
                nc[i][k] = t2;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if((i<(NX*NY*(NZ-1)))&&(((i%(NX*NY))>=NX)&&(((i%(NX*NY))%NX)!=(NX-1))))
            {
                nc[i][k] = t3;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i<(NX*NY*(NZ-1)))&&(((i%(NX*NY))%NX)!=0))
            {
                nc[i][k] = t4;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if(i<(NX*NY*(NZ-1)))
            {
                nc[i][k] = t5;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if((i<(NX*NY*(NZ-1)))&&(((i%(NX*NY))%NX)!=(NX-1)))
            {
                nc[i][k] = t6;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i<(NX*NY*(NZ-1)))&&(((i%(NX*NY))<(NX*(NY-1)))&&(((i%(NX*NY))%NX)!=0)))
            {
                nc[i][k] = t7;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i<(NX*NY*(NZ-1)))&&((i%(NX*NY))<(NX*(NY-1))))
            {
                nc[i][k] = t8;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
            if((i<(NX*NY*(NZ-1)))&&(((i%(NX*NY))<(NX*(NY-1)))&&(((i%(NX*NY))%NX)!=(NX-1))))
            {
                nc[i][k] = t9;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }
        }
    }

    else if(dim==2)
    {
        for (i=0; i<ncell; i++)
        {
            int k = 0;
            int b1 = -1;
            int b2 = -1;
            int b3 = -1;
            int b4 = -1;
            int b5 = -1;
            int b6 = -1;
            int b7 = -1;
            int b8 = -1;
            int b9 = -1;
            int m1 = i-NX-1;
            int m2 = i-NX;
            int m3 = i-NX+1;
            int m4 = i-1;
            int m5 = i;
            int m6 = i+1;
            int m7 = i+NX-1;
            int m8 = i+NX;
            int m9 = i+NX+1;
            int t1 = -1;
            int t2 = -1;
            int t3 = -1;
            int t4 = -1;
            int t5 = -1;
            int t6 = -1;
            int t7 = -1;
            int t8 = -1;
            int t9 = -1;

            nc[i][k] = b1;
            k = k+1;
            nc[i][k] = b2;
            k = k+1;
            nc[i][k] = b3;
            k = k+1;
            nc[i][k] = b4;
            k = k+1;
            nc[i][k] = b5;
            k = k+1;
            nc[i][k] = b6;
            k = k+1;
            nc[i][k] = b7;
            k = k+1;
            nc[i][k] = b8;
            k = k+1;
            nc[i][k] = b9;
            k = k+1;

            if((i>=NX)&&((i%NX)!=0))
            {
                nc[i][k] = m1;
                k = k+1;
            }
            if(i>=NX)
            {
                nc[i][k] = m2;
                k = k+1;
            }
            if((i>=NX)&&((i%NX)!=(NX-1)))
            {
                nc[i][k] = m3;
                k = k+1;
            }
            if((i%NX)!=0)
            {
                nc[i][k] = m4;
                k = k+1;
            }
            if(m5>=0)
            {
                nc[i][k] = m5;
                k = k+1;
            }
            if((i%NX)!=(NX-1))
            {
                nc[i][k] = m6;
                k = k+1;
            }
          /*  if(internal_flow==1)
            {
                if((i%NX)==(NX-1))
                {
                    nc[i][k] = (i+1-NX);
                    k = k+1;
                }
                if(((i%NX)==(NX-1)) && (i<NX))
                {
                    nc[i][k] = i+1;
                    k = k+1;
                }
                if(((i%NX)==(NX-1)) && ((i>(NX*(NY-1)))) )
                {
                    nc[i][k] =i-(NX+(i%NX));
                    k = k+1;
                }
                if( ((i%NX)==(NX-1)) && (i<(NX*(NY-1)))&& (i>NX) )
                {
                    nc[i][k] = i+1;
                    k = k+1;
                    nc[i][k] =i-(NX+(i%NX));
                    k = k+1;
                }
                ///////////////////////
                if( ((i%NX)==0) )
                {
                    nc[i][k] = (i+(NX-1));
                    k = k+1;
                }
                if( ((i%NX)==0) && (i<NX) )
                {
                    nc[i][k] = i+(NX+(NX-1));
                    k = k+1;
                }
                if( ((i%NX)==0) && (i>=(NX*(NY-1))) )
                {
                    nc[i][k] =i-1;
                    k = k+1;
                }
                if( ((i%NX)==0) && (i<(NX*(NY-1))) && (i>=NX) )
                {
                    nc[i][k] = i+(NX+(NX-1));
                    k = k+1;
                    nc[i][k] =i-1;
                    k = k+1;
                }
            }*/
            if( (i<(NX*(NY-1))) && ((i%NX)!=0) )
            {
                nc[i][k] = m7;
                k = k+1;
            }
            if( i<(NX*(NY-1)) )
            {
                nc[i][k] = m8;
                k = k+1;
            }
            if( (i<(NX*(NY-1))) && ((i%NX)!=(NX-1)) )
            {
                nc[i][k] = m9;
                k = k+1;
            }

            nc[i][k] = t1;
            k = k+1;
            nc[i][k] = t2;
            k = k+1;
            nc[i][k] = t3;
            k = k+1;
            nc[i][k] = t4;
            k = k+1;
            nc[i][k] = t5;
            k = k+1;
            nc[i][k] = t6;
            k = k+1;
            nc[i][k] = t7;
            k = k+1;
            nc[i][k] = t8;
            k = k+1;
            nc[i][k] = t9;
            k = k+1;
        }
    }

    else if (dim==1)
    {
        for (int i=0; i<ncell; i++)
        {
            int k = 0;
            int b1 = -1;
            int b2 = -1;
            int b3 = -1;
            int b4 = -1;
            int b5 = -1;
            int b6 = -1;
            int b7 = -1;
            int b8 = -1;
            int b9 = -1;
            int m1 = -1;
            int m2 = -1;
            int m3 = -1;
            int m4 = i-1;
            int m5 = i;
            int m6 = i+1;
            int m7 = -1;
            int m8 = -1;
            int m9 = -1;
            int t1 = -1;
            int t2 = -1;
            int t3 = -1;
            int t4 = -1;
            int t5 = -1;
            int t6 = -1;
            int t7 = -1;
            int t8 = -1;
            int t9 = -1;

            nc[i][k] = b1;
            k = k+1;
            nc[i][k] = b2;
            k = k+1;
            nc[i][k] = b3;
            k = k+1;
            nc[i][k] = b4;
            k = k+1;
            nc[i][k] = b5;
            k = k+1;
            nc[i][k] = b6;
            k = k+1;
            nc[i][k] = b7;
            k = k+1;
            nc[i][k] = b8;
            k = k+1;
            nc[i][k] = b9;
            k = k+1;

            nc[i][k] = m1;
            k = k+1;
            nc[i][k] = m2;
            k = k+1;
            nc[i][k] = m3;
            k = k+1;

            if(((i%(NX*NY))%NX)!=0)
            {
                nc[i][k] = m4;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if(m5>=0)
            {
                nc[i][k] = m5;
                k = k+1;
            }
            else
            {
                nc[i][k]=-1;
                k = k+1;
            }
            if(((i%(NX*NY))%NX)!=(NX-1))
            {
                nc[i][k] = m6;
                k = k+1;
            }
            else
            {
                nc[i][k] = -1;
                k = k+1;
            }

            nc[i][k] = m7;
            k = k+1;
            nc[i][k] = m8;
            k = k+1;
            nc[i][k] = m9;
            k = k+1;

            nc[i][k] = t1;
            k = k+1;
            nc[i][k] = t2;
            k = k+1;
            nc[i][k] = t3;
            k = k+1;
            nc[i][k] = t4;
            k = k+1;
            nc[i][k] = t5;
            k = k+1;
            nc[i][k] = t6;
            k = k+1;
            nc[i][k] = t7;
            k = k+1;
            nc[i][k] = t8;
            k = k+1;
            nc[i][k] = t9;
            k = k+1;
        }
    }
    for(i=0; i<ncell; i++)
    {
        for(j=0; j<27; j++)
        {
            a[j] = nc[i][j];
        }
        quickSort(a,0,26);
        for(j=0; j<27; j++)
        {
            nc[i][j] = a[j];
        }
    }
}
