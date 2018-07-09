#include "functions.h"
#include <fftw3.h>
#include <cmath>

using namespace std;

void Derivative(double& num1, double& num2, double J) {
  //takes two derivatives
       num1 = -1 * pow(J,2) * num1;
       num2 = -1 * pow(J,2) * num2;  
}


double INITIAL(double X){ // Initial function
    double value = 1.0/cosh(3*(X-M_PI));//sin(X) + sin(3*X);
    return value;
}



void FFT(double *in, double *Result,
         int N, double L){

    double *input, *outI, *kx;
    input = new double [N];
    outI = new double [N];
    kx = new double [N];

    for(int i=0; i<N; i++){
        input[i] = in[i];
    }

    //Declaring transformed matricies;
    fftw_complex *out;
    out= (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*(N));

    //Plans for execution
    fftw_plan p;

    p= fftw_plan_dft_r2c_1d(N,input, out, FFTW_ESTIMATE);

    fftw_execute(p);


    //Frequencies
      for (int i = 0; i< N/2; ++i) {
         kx[i] = i/L;
       } 
         
         kx[N/2] =0.00;

      for (int i = 0; i < ((N/2)-1); ++i)  {
          kx[i+1+N/2] = -kx[N/2-i-1];
       }


    //Derivative
    for(int i=0; i<N;i++){

        Derivative(out[i][0],out[i][1],kx[i]);
    }

    fftw_plan pI;
    //Execution of Inverse FFT

    pI = fftw_plan_dft_c2r_1d(N,out,outI,FFTW_PRESERVE_INPUT);

    fftw_execute(pI);

    for(int i=0;i<N; i++){//Dividing by the size of the array
        Result[i] = (1.0/N)*outI[i];
    }

    fftw_free(outI); fftw_free(out);
    fftw_free(input);
    fftw_destroy_plan(pI);  fftw_destroy_plan(p);
}