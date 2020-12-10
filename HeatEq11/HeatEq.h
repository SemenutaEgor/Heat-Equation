//HeatEq.h

#ifndef _HeatEq_h
#define _HeatEq_h

#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include <fstream>

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

	HeatEq();
	HeatEq(double x_start, double x_finish, double t_start, double t_finish, int n, int m);
	void ReCreate();

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

	void Setx_start(double val) { x_start = val; }
	void Setx_finish(double val) { x_finish = val; }
	void Sett_start(double val) { t_start = val; }
	void Sett_finish(double val) { t_finish = val; }
	void Setn(int val) { n = val; }
	void Setm(int val) { m = val; };

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
