#include "header.h"
void quickSort_ld(vector<long double> &arr, int left, int right)
{
    /// ascending order
    int i = left, j = right;
    long double tmp;
    long double pivot = arr[(left + right) / 2];
    /* partition */
    while (i <= j)
    {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j)
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    /* recursion */
    if (left < j)
    {
        quickSort_ld(arr, left, j);
    }

    if (i < right)
    {
        quickSort_ld(arr, i, right);
    }

}
