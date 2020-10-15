#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std ;
//--------- Global varibles---------
int Num_P ,Num_R ,process_request ;
char a='A' , *r=new char[Num_R] ;
bool *finish =new bool [Num_P] ;
int *work =new int[Num_R] ;

// ---------Functions prototypes ---------
void ReadPR();
void ReadFile(int **allocation ,int **max ,int **need ,int *available , int *request ,int &process_request);
void print (int **allocation ,int **max ,int **need ,int *available , int *request ,int process_request);
bool safe (int **allocation ,int **need ,int *available  );
void request(int **allocation ,int **max ,int **need ,int *available , int *request ,int process_request);
void TestRequest(int **allocation ,int **need ,int *available , int *request ,int process_request);


//--------- Main function ---------
int main()
{
    ReadPR();
    
    int **allocation =new int*[Num_P] ;        //--------- 2D Dynamuc Arr for Allocation Matrix
    for(int i = 0; i < Num_P; ++i)
        allocation[i] = new int[Num_R];
    int **max =new int*[Num_P] ;               //---------2D Dynamuc Arr for Max Matrix
    for(int i = 0; i < Num_P; ++i)
        max[i] = new int[Num_R];
    int **need =new int*[Num_P] ;              //---------2D Dynamuc Arr for Need Matrix
    for(int i = 0; i < Num_P; ++i)
        need[i] = new int[Num_R];
    int *available =new int[Num_R] ;           //---------1D Dynamuc Arr for Available Vector
    int *request =new int[Num_R] ;             //---------1D Dynamuc Arr for Request Vector
    
    
    ReadFile(allocation ,max ,need ,available, request,process_request);
    print(allocation ,max ,need ,available ,request,process_request);
    TestRequest(allocation , need , available , request , process_request);

    
    delete [] allocation ;
    delete []  max ;
    delete []  need ;
    delete []  available ;
    delete []  request ;
    
    return 0;
}



void ReadPR(){          //--------- Fuction ReadFile to read all process and receurs
    
    fstream readFile;
    readFile.open("os.txt");
    readFile>>Num_P ;

    readFile>>Num_R ;
    readFile.close();
}


                                //--------- Fuction ReadFile to read all Matrixs, Vectors and Request
void ReadFile(int **allocation ,int **max ,int **need ,int *available, int *request ,int &process_request)//---------pass by refrance for
{
    char read_colon;
    
    fstream readFile;
    readFile.open("test.txt");
    readFile>>Num_P ;
    readFile>>Num_R ;
    
    for (int i = 0; i <  Num_P ; i++)
        for (int j = 0; j <  Num_R ; j++)
            readFile>>allocation[i][j] ;
    
    for (int i = 0; i <  Num_P ; i++)
        for (int j = 0; j <  Num_R ; j++)
            readFile>>max[i][j] ;
    
    for (int i = 0; i <  Num_P ; i++)
        for (int j = 0; j <  Num_R ; j++)
            need[i][j] =max[i][j]-allocation[i][j] ;
    
    for (int j = 0; j <  Num_R ; j++)
    {
        readFile>>available[j] ;
        r[j]=a++ ;
    }
    
    readFile>>process_request ;
    readFile>>read_colon ;
    for (int j = 0; j <  Num_R ; j++)
        readFile>>request[j] ;

    readFile.close();
}


                        //--------- Function print : to printing all Matrixs, Vectors and Request ----------
void print (int **allocation ,int **max ,int **need ,int *available ,int *request,int process_request)
{
    cout<<"There are "<<Num_P<<" processes in the system.\n"<<endl;
    cout<<"There are "<<Num_R<<"  resource types.\n\n"<<endl;
    
    cout<<"\nThe Allocation Matrix is..."<<endl;
    cout<<"   ";
    for (int j = 0 ; j <  Num_R ;  j++)
        cout<<' '<< r[j] ;
    cout<<endl;
    for (int i = 0; i <  Num_P ; i++)
    {
        cout<<'P'<<i<<':'<<' ';
        for (int j = 0; j <  Num_R ; j++)
        cout<<allocation[i][j] <<' ';
        finish[i]=false ;       //----------------initialise array of pool to Finish processes
        cout<<endl;
    }
    cout<<"\nThe Max Matrix is..."<<endl;
    cout<<"   ";
    for (int j = 0 ; j <  Num_R ;  j++)
        cout<<' '<< r[j] ;
    cout<<endl;
    for (int i = 0; i <  Num_P ; i++)
    {   cout<<'P'<<i<<':'<<' ';
        for (int j = 0; j <  Num_R ; j++)
            cout<<max[i][j] <<' ';
        cout<<endl;
    }
    cout<<"\nThe Need Matrix is.."<<endl;
    cout<<"   ";
    for (int j = 0 ; j <  Num_R ;  j++)
        cout<<' '<< r[j] ;
    cout<<endl;
    for (int i = 0; i <  Num_P ; i++)
    {   cout<<'P'<<i<<':'<<' ';
        for (int j = 0; j <  Num_R ; j++)
            cout<<need[i][j] <<' ';
        cout<<endl;
    }
    cout<<"\nThe Available Vector is..."<<endl;
    cout<<"   ";
    for (int j = 0 ; j <  Num_R ;  j++)
        cout<<' '<< r[j] ;
    cout<<"\n    ";
    for (int j = 0; j <  Num_R ; j++)
        cout<<available[j] <<' ';
        cout<<endl;
    
    bool safe_request= safe( allocation ,need ,available ); //------------call function safe to check if the system safe or not
    if (safe_request)
        cout<<"\nTHE SYSTEM IS IN A SAFE STATE!... "<<endl;
    else
        cout<<"\nTHE SYSTEM IS NOT IN A SAFE STATE! ....X"<<endl;
        
    
    cout<<"\nThe Request Vector is..."<<endl;
    cout<<"   ";
    for (int j = 0 ; j <  Num_R ;  j++)
        cout<<' '<< r[j] ;
    cout<<"\n  "<<process_request<<":";
    for (int j = 0; j <  Num_R ; j++)
        cout<<request[j] <<' ';
    cout<<endl;
    

    cout<<"\nThe work Vector is..."<<endl;  //----------------initialise array of work =
    cout<<"   ";
    for (int j = 0 ; j <  Num_R ;  j++)
        cout<<' '<< r[j] ;
    cout<<"\n  "<<process_request<<":";
    for (int j = 0; j <  Num_R ; j++)
    {
        cout<<work[j] <<' ';}
    cout<<endl;
}



bool safe (int **allocation ,int **need ,int *available  ) //--------- Function safe to check if the system safe or not
{
    bool safeFlag=true ,needSmallar=true;
    for (int j = 0; j <  Num_R ; j++) //----------------initialise array of work =  available
        work[j] = available[j] ;
    
    for (int i = 0; i <  Num_P ; i++)      { //---------------check if the system safe or not( need <= work ) and finish[i]==false
        needSmallar=true;
        if (finish[i]==false) {
        for (int j = 0; j <  Num_R ; j++)
        {
            if (need[i][j] > work[j])
            {
                needSmallar=false ;
                safeFlag=false;
                break ;
            }
         }
           if (needSmallar == true)
           {
               for (int j = 0; j <  Num_R ; j++)
               {
                   work[j]=work[j]+allocation[i][j];
                   finish[i]=true ;
               }
           }
        }
    }
    //_______________________*******_______________________
    safeFlag=true;
    for (int i = 0; i <  Num_P ; i++)      {
        needSmallar=true;
        if (finish[i]==false) {
            for (int j = 0; j <  Num_R ; j++)
            {
                if (need[i][j] > work[j])
                {
                    needSmallar=false ;
                    safeFlag=false;
                    break ;
                }
            }
            if (needSmallar == true)
            {
                for (int j = 0; j <  Num_R ; j++)
                {
                    work[j]=work[j]+allocation[i][j];
                    finish[i]=true ;
                }
            }
        }
    }
    return safeFlag;
}
        //--------- Function ( TestRequest ) check THE REQUEST if it CAN BE GRANTED or not! ----------
void TestRequest(int **allocation ,int **need ,int *available , int *request ,int process_request)
{
    bool flag_request=true;
    for (int j = 0; j <  Num_R ; j++)
    {
        if (request[j] > need[process_request][j])
        {
            flag_request=false;
            break;
        }
        if (request[j] > available[j])
        {
            flag_request=false;
            break;
        }
    }
    if (flag_request == false)
        cout<<"\nTHE REQUEST CAN NOT BE GRANTED .... X "<<endl;
    else
    {
        for (int j = 0; j <  Num_R ; j++)
        {
            available[j]-=request[j];
            allocation[process_request][j]+=request[j];
            need[process_request][j]-=request[j];
        }
        bool safe_request= safe( allocation ,need ,available );
        if (safe_request == true)
        {
            cout<<"\nTHE REQUEST CAN BE GRANTED ...."<<endl;
            
            cout<<"\nThe Available Vector is..."<<endl;
            cout<<"   ";
            for (int j = 0 ; j <  Num_R ;  j++)
                cout<<' '<< r[j] ;
            cout<<"\n    ";
            for (int j = 0; j <  Num_R ; j++)
            {
                cout<<work[j] <<' ';}
            cout<<endl;
        }
        else
            cout<<"\nTHE REQUEST CAN NOT BE GRANTED BECAUSE \nTHE SYSTEM IS NOT IN A SAFE STATE! ...."<<endl;
        
    }
}