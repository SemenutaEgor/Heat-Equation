//HeatEq.h

#ifndef _HeatEq_h
#define _HeatEq_h

#include <iostream>

#define MAXSIZE 100000

using namespace std;

class HeatEq {
private:

	//for heat equation
	double x_start; //x start value
	double x_finish; //x finish value
	double t_start; // start time
	double t_finish; // finish time
	int n; // number of segments along x
	int m; // number of segments along t

	//for tridiagonal matrix algorithm
	double *A_arr = new double[MAXSIZE]; //array of coefficients A
	double *B_arr = new double[MAXSIZE]; //array of coefficients B
	double *C_arr = new double[MAXSIZE]; //array of coefficients C
	double kappa1; //coefficient kappa1
	double kappa2; //coefficient kappa2
	double mu1; //coefficient mu1
	double mu2; // coefficient mu2
	double *phi_arr = new double[MAXSIZE]; //array for coefficients phi
	

public:
	//static double* solutions = new double[MAXSIZE]; //array for solutions

	void TriagMatrix(double* A_arr, double* B_arr, double* C_arr, double kappa1, double kappa2, double mu1, double mu2, double* phi_arr, int size_arr);
	//static void PrintSolutions();

};

#endif
