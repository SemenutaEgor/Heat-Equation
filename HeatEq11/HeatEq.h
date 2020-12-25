//HeatEq.h

#ifndef _HeatEq_h
#define _HeatEq_h

#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include <fstream>
#include "StreamTable.h"

//#define MAXSIZE 100000

using namespace std;

class HeatEq {
private:

	//for heat equation
	double x_start; //x start value
	double x_finish; //x finish value
	double t_start; // start time
	double t_finish; // finish time
	//double t_start_show; // time from which the show will start
	int n; // number of segments along x
	int m; // number of segments along t
	double h; //step along x
	double tau; //step along t
	double* layer; //array for layers
	double layer_counter; //counter of layers
	double min_temp; //minimal temperature of rod
	double max_temp; //maximal temperature of rod

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
	HeatEq(int n, int m);
	void ReCreate();

	//Set&Get methods
	double Getx_start();
	double Gett_start();
	double Getx_finish();
	double Gett_finish();
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
	double GetPhi(int i, int j); //calculate and return Phi[i][j]

	void Setx_start(double val) { x_start = val; }
	void Setx_finish(double val) { x_finish = val; }
	void Sett_start(double val) { t_start = val; }
	void Sett_finish(double val) { t_finish = val; }
	//void Sett_start_show(double val) { t_start_show = val; }
	void Setn(int val) { n = val; }
	void Setm(int val) { m = val; }
	void Setmin_temp(double val) { min_temp = val; }
	void Setmax_temp(double val) { max_temp = val; }

	//Tridiagonal matrix algorithm
	void TridiagMatrix(double* A_arr, double* B_arr, double* C_arr, double kappa1, double kappa2, 
		double mu1, double mu2, double* phi_arr, int size_arr);

	//Heat Equation methods
	int TempCheck(double temp, int index); //checks the temperature for hypothermiaand overheating
	void TempCheckToFile(); //checks the temperature for hypothermiaand overheating
	int CheckedZeroLayer(); //zero layer calculation with checking the temperature for hypothermiaand overheating
	int CheckedNextLayer(); //next layer calculation with checking the temperature for hypothermiaand overheating
	void ZeroLayer(); //zero layer calculation
	void NextLayer(); //next layer calculation
	double GetTemperature(double x, double t); //return temperature on defined states
	double HeatSource(double t); // return heat source density at time t
	//void HeatSourcesInTime(); // return heat source density at time t
	//void TemperatureChanges(); // monitors temperature changes on the rod over a certain period of time
	
	//Output methods
	void PrintTMSolutions(); //print solutions of tridiagonal matrix algorithm
	void PrintLastLayerToFile(); //print last layer into file
	void PrintLastLayer(); //print last layer into console
	void PrintMatrix(); //print tridiadonal matrix for last layer

};

#endif
