//HeatEq.h

#ifndef _HeatEq_h
#define _HeatEq_h

#include <iostream>

//#define MAXSIZE 100000

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
	double h; //step along x
	double tau; //step along t
	double* layer; //array for layers
	int layer_counter; //counter of layers

	//for tridiagonal matrix algorithm
	double A; //coefficient A
	double B; //coefficient B
	double C; //coefficient C
	double kappa1; //coefficient kappa1
	double kappa2; //coefficient kappa2
	double mu1; //coefficient mu1
	double mu2; // coefficient mu2
	double* phi_arr; //array for coefficients phi
	double* TMsolutions; //array for solutions
	

public:
	HeatEq(int n, int m, double x_start, double x_finish, double t_start, double t_finish) {
		this->n = n;
		this->m = m;
		this->x_start = x_start;
		this->x_finish = x_finish;
		this->t_start = t_start;
		this->t_finish = t_finish;

		this->h = (x_finish - x_start) / n;
		this->tau = (t_finish - t_start) / m;

		this->A = (9.0 * tau) / pow(h, 2);
		this->B = (9.0 * tau) / pow(h, 2);
		this->C = 1.0 + (18.0 * tau)/pow(h, 2);
		this->kappa1 = -1.0;
		this->kappa2 = 1.0 / (1.0 + 7.0*h);
		this->mu1 = 0;
		this->mu2 = (2*h) / (1.0  + 7.0*h);
		this->phi_arr = new double[n - 2];
		this->TMsolutions = new double[n];

		this->layer = new double[n + 1];
		this->layer_counter = 0;

	}

	//Set&Get methods
	int Getn(); //return n
	int Getm(); //return m
	double Geth(); //return h
	double Gettau(); //return tau
	int Getlayer_counter(); //return layer_counter (number if layers)
	double GetA(); //return A
	double GetB(); //return B
	double GetC(); //return C
	double GetKappa1(); //return kappa1
	double GetKappa2(); //return kappa2

	//Tridiagonal matrix algorithm
	void TridiagMatrix(double* A_arr, double* B_arr, double* C_arr, double kappa1, double kappa2, 
		double mu1, double mu2, double* phi_arr, int size_arr);

	//Heat Equation methods
	void ZeroLayer(); //zero layer calculation
	void NextLayer(); //next layer calculation
	
	//Output methods
	void PrintTMSolutions(); //print solutions of tridiagonal matrix algorithm
	void PrintLastLayer(); //print last layer
	void PrintMatrix(); //print tridiadonal matrix for last layer

};

#endif
