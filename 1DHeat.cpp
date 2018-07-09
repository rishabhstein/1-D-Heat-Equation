#include <iostream>
#include <cmath>
#include <fstream>
#include <fftw3.h>

#include "functions.h"

using namespace std;

const int N = 64;
const double L=5.0;

int main()
{
    //Creating and delcaring function variables
    double *initial,*w1,*y;
    double dx= 2*M_PI/N, x=0, t=0, dt=0.01; 
    double tmax= 100*dt;

    //creating arrays for the RK4 procedure
    initial = new double [N];
    w1 = new double [N]; y= new double [N];
    double *resultArray = new double[N];
    double *resultnext = new double[N];
    int j = 1; 

    // The stability parameter are declared but not used
    float alpha=0.5, CFL=alpha*dt/(10*pow(dx,2));

    //Output files
    ofstream sendtofileINITIAL("HeatdataINITIAL.dat");
    ofstream sendtofile5("Heatdata5.dat");
    ofstream sendtofile25("Heatdata25.dat");
    ofstream sendtofile85("Heatdata85.dat");
    ofstream sendtofileFINAL("HeatdataFINAL.dat");

    //Initial data
    for(int i=0; i<N; i++){
        y[i] = INITIAL(x);  
        sendtofileINITIAL << i*2*M_PI/N <<" "<< y[i] << endl;
        x+=dx;
    }


    while(t<=tmax){

        FFT(y,resultArray,N,L);
	       //cout << j << endl;
        for(int i = 0; i < N; i++){    //Calculating w1
            w1[i] = y[i];
            resultnext[i] = w1[i] + alpha * dt * resultArray[i];
            y[i] = resultnext[i];        

            
            //Outputing data at certain time periods
            if(j==5)
                sendtofile5 << i*2*M_PI/N <<" "<< y[i] << endl;

            if(j==25)
                sendtofile25 << i*2*M_PI/N <<" "<< y[i] << endl;

            if(j==85)
                sendtofile85 << i*2*M_PI/N <<" "<< y[i] << endl;

            if(j==100)
                sendtofileFINAL << i*2*M_PI/N <<" "<< y[i] << endl; 
        }
        j++;// counter
        t+= dt;// time counter
    }

    sendtofileINITIAL.close();
    sendtofile5.close();
    sendtofile25.close();
    sendtofile85.close();
    sendtofileFINAL.close();
    return 0;
}
