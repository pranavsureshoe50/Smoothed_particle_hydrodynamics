#ifndef PRINT_DATA_H_INCLUDED
#define PRINT_DATA_H_INCLUDED

#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "const.h"
extern int  iter,print_count,ncell;
extern int const dim;
extern long double sim_time;
using std::vector;
class print
{
public:
    /////////////single array //////////////////
        template<typename T1>
        void SaveData( T1 data1[],int N,std::string var)
        {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (int i=0; i<N; i++)
        {
            myfile
                    <<std::left<<std::fixed<<std::setw(8)<<i+1
                    <<std::left<<std::setw(12)<<std::setprecision(6)<<data1[i]
                    <<std::endl;
        }
        myfile.close();
        }
    ////////// single vector /////////////////////
    template<typename T1>
    void SaveData( vector<T1> data1,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (size_t i=0; i<data1.size(); i++)
        {
            myfile
                    <<std::left<<std::fixed<<std::setw(8)<<i+1
                    <<std::left<<std::setw(12)<<std::setprecision(4)<<data1[i]
                    <<std::endl;
        }
        myfile.close();
    }


    ////////// one multi dimensional vector /////////////
    template<typename T1>
    void SaveData(vector<vector<T1> > data1,int n,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (size_t i=0; i<data1.size(); i++)
        {
            myfile<<std::left<<std::fixed;
            for(int j=0; j<n; j++)
            {
                myfile<<std::left<<std::setw(18)<<std::setprecision(8)<<data1[i][j];
            }
            myfile <<std::endl;
        }
        myfile.close();
    }
    ////////// one multi dimensional vector /////////////
    template<typename T1>
    void SaveData(vector<vector<T1> > data1,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (size_t i=0; i<data1.size(); i++)
        {
            myfile<<std::left<<std::fixed;
            for(int j=0; j<dim; j++)
            {
                myfile<<std::left<<std::setw(18)<<std::setprecision(8)<<data1[j][i];
            }
            myfile <<std::endl;
        }
        myfile.close();
    }
    ////////////// two array ///////////////////////////////
    template<typename T1,typename T2>
    void SaveData( T1 data1[],T2 data2[],int N,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (int i=0; i<N; i++)
        {
            myfile
                    <<std::left<<std::fixed
                    <<std::left<<std::setw(12)<<std::setprecision(6)<<data1[i]
                    <<std::left<<std::setw(12)<<std::setprecision(6)<<data2[i]
                    <<std::endl;
        }
        myfile.close();
    }
    /////////////// two vector  ////////////////////
    template<typename T1,typename T2>
    void SaveData( vector<T1> data1,vector<T2> data2, std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(),std::ios::trunc);
        for (size_t i=0; i<data1.size(); i++)
        {
            myfile
                    <<std::left<<std::fixed//<<std::setw(8)<<i+1
                    <<std::left<<std::setw(12)<<std::setprecision(4)<<data1[i]
                    <<std::left<<std::setw(12)<<std::setprecision(8)<<data2[i]
                    <<std::endl;
        }
        myfile.close();
    }

    ///////////two multi dimensional vector ////////////////////
    template<typename T1,typename T2>
    void SaveData(vector<vector<T1> > data1,vector<vector<T2> > data2,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (size_t i=0; i<data2[0].size(); i++)
        {
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::left<<std::setw(12)<<std::setprecision(6)<<data1[j][i];
            }
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::left<<std::setw(18)<<std::setprecision(4)<<data2[j][i];
            }
                    myfile<<std::endl;
        }
        myfile.close();
    }



    ////////// one multi dimensional vector and one single dimension array/////////////
    template<typename T1,typename T2>
    void SaveData(vector<vector<T1> > data1,vector<T2> data2,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (size_t i=0; i<data1[0].size(); i++)
        {
            myfile
                    <<std::left<<std::fixed;
                    for(int j=0; j<dim; j++)
            {
                        myfile<<std::left<<std::setw(12)<<std::setprecision(6)<<data1[j][i];
            }
                    myfile<<std::left<<std::setw(12)<<std::setprecision(6)<<data2[i]
                    <<std::endl;
        }
        myfile.close();
    }

 ///////////two multi dimensional vector and 1single dimensional vector ////////////////////
    template<typename T1,typename T2,typename T3>
    void SaveData(vector<vector<T1> > data1,vector<vector<T2> > data2,vector<T3> data3,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (size_t i=0; i<data2[0].size(); i++)
        {
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::left<<std::setw(18)<<std::setprecision(4)<<data1[j][i];
            }
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::left<<std::setw(18)<<std::setprecision(4)<<data2[j][i];
            }
            myfile<<std::left<<std::setw(12)<<std::setprecision(6)<<data3[i]<<std::endl;
        }
        myfile.close();
    }

    ///////////one multi dimensional vector and 2single dimensional vector ////////////////////
    template<typename T1,typename T2,typename T3>
    void SaveData(vector<vector<T1> > data1,vector<T2> data2,vector<T3> data3,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc);
        for (size_t i=0; i<data1[0].size(); i++)
        {
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::left<<std::setw(18)<<std::setprecision(4)<<data1[j][i];
            }
            myfile<<std::left<<std::setw(18)<<std::setprecision(4)<<data2[i];
            myfile<<std::left<<std::setw(12)<<std::setprecision(6)<<data3[i]<<std::endl;
        }
        myfile.close();
    }
   /* ///////////two multi dimensional vector and three dimensional vector ////////////////////
    template<typename T1,typename T2,typename T3,typename T4,typename T5>
    void SaveData(vector<vector<T1> > data1,vector<vector<T2> > data2,vector<T3> data3,vector<T4> data4,vector<T5> data5,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".dat";
        myfile.open(filename.c_str(), std::ios::trunc | std::ios_base::binary);
        myfile<<"TITLE = LID-DRIVEN CAVITY AT Re=100"<<std::endl;
        if(dim==1){
        myfile<<"VARIABLES = \"X(M)\",\"U(M/S)\",\"P\",\"RHO\",\"I_TYPE\" "<<std::endl;}
        if(dim==2){
        myfile<<"VARIABLES = \"X(M)\", \"Y(M)\", \"U(M/S)\",\"V(M/S)\",\"P\",\"RHO\",\"I_TYPE\" "<<std::endl;}
        if(dim==3){
        myfile<<"VARIABLES = \"X(M)\", \"Y(M)\",\"Z(M)\", \"U(M/S)\",\"V(M/S)\",\"W(M/S)\",\"P\",\"RHO\",\"I_TYPE\" "<<std::endl;}
        myfile<<"ZONE T=\""<<print_count<<"\", " <<"STRANDID=1,"<<"SOLUTIONTIME="<<sim_time<<std::endl;
        for (size_t i=0; i<data1[0].size(); i++)
        {
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::left<<std::fixed<<std::setw(10)<<std::setprecision(4)<<data1[j][i];
            }
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::left<<std::scientific<<std::setw(15)<<std::setprecision(4)<<data2[j][i];
            }
            myfile<<std::left<<std::fixed<<std::setw(15)<<std::setprecision(2)<<data3[i];
            myfile<<std::left<<std::fixed<<std::setw(10)<<std::setprecision(2)<<data4[i];
            myfile<<std::left<<std::fixed<<std::setw(5)<<std::setprecision(1)<<data5[i]<<std::endl;
        }
        myfile.close();
    }*/
     ///////////two multi dimensional vector and three dimensional vector ////////////////////
    template<typename T1,typename T2,typename T3,typename T4,typename T5>
    void SaveData(vector<vector<T1> > data1,vector<vector<T2> > data2,vector<T3> data3,vector<T4> data4,vector<T5> data5,std::string var)
    {
        std::ofstream myfile;
        std::string filename;
        std::stringstream a;
        a << print_count;
        filename = var + a.str();
        filename += ".csv";
        myfile.open(filename.c_str(), std::ios::trunc | std::ios_base::binary);
        for (size_t i=0; i<data1[0].size(); i++)
        {
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::setprecision(4)<<data1[j][i]<<",";
            }
            for(int j=0; j<dim; j++)
            {
                    myfile<<std::setprecision(4)<<data2[j][i]<<",";
            }
            myfile<<std::setprecision(6)<<data3[i]<<",";
            myfile<<std::setprecision(6)<<data4[i]<<",";
            myfile<<std::setprecision(1)<<data5[i]<<std::endl;
        }
        myfile.close();
    }
};
#endif // PRINT_DATA_H_INCLUDED
