#include "const.h"
#include "header.h"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
#define c 1.0e-12
void mat2inv (long double a[dim][dim],vector<vector<long double> > &inv)
{
    long double det;

	det=( (a[0][0]*a[1][1]) - a[0][1]*a[1][0]);
	if(det == 0)
    {
        det = c ;
    }
	inv[0][0]=a[1][1]/det;
	inv[0][1]=-a[0][1]/det;
	inv[1][0]=-a[1][0]/det;
	inv[1][1]=a[0][0]/det;
}
