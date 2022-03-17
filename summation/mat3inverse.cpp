#include "const.h"
#include "header.h"
#include <vector>
#include <cmath>
#include <iostream>
#include </home/ssudarsan/Documents/library/matrix_rank/eigen-eigen-10219c95fe65/Eigen/Dense>

using std::cout;
using std::endl;
using std::vector;
using Eigen::MatrixXd;
void mat3inv(long double a[3][3],vector<vector<long double> > &inv1,int &singular_m)
{
    long double det1;
    int i,j,rank;
    MatrixXd m(3,3);
    static int count;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            m(i,j)=a[i][j];
        }
    }

    det1= (a[0][0]*( (a[1][1]*a[2][2])-(a[2][1]*a[1][2]) )) - ( a[0][1]*( (a[1][0]*a[2][2])-(a[1][2]*a[2][0]) ) )+ ( a[0][2]*( (a[1][0]*a[2][1])-(a[1][1]*a[2][0]) ));//adjoinv
    Eigen::FullPivLU< Eigen::MatrixXd > luA(m);
    rank = luA.rank();
    if(rank<3)
    {
        count++;
       // cout<<"possible singular matrix"<<"\t"<<count<<"\t"<<rank<<endl;
        singular_m=1;
    }
    else
    {
        inv1[0][0]=( (a[1][1]*a[2][2])-(a[1][2]*a[2][1]) )/det1;
    inv1[0][1]=-( (a[0][1]*a[2][2]) -(a[0][2]*a[2][1]) )/det1;
    inv1[0][2]=( (a[0][1]*a[1][2]) -(a[0][2]*a[1][1]) )/det1;
    inv1[1][0]=-( (a[1][0]*a[2][2])-(a[1][2]*a[2][0]) )/det1;
    inv1[1][1]=( (a[0][0]*a[2][2]) -(a[0][2]*a[2][0]) )/det1;
    inv1[1][2]=-( (a[0][0]*a[1][2]) -(a[0][2]*a[1][0]) )/det1;
    inv1[2][0]=( (a[1][0]*a[2][1]) -(a[2][0]*a[1][1]) )/det1;
    inv1[2][1]=-( (a[0][0]*a[2][1]) -(a[0][1]*a[2][0]) )/det1;
    inv1[2][2]=( (a[0][0]*a[1][1]) -(a[0][1]*a[1][0]) )/det1;

    }

}
