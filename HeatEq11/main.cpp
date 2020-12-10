// main.cpp

#include "HeatEq.h"

int main() {
	//double A[1] = {1.0};
	//double B[1] = {2.0};
	//double C[1] = {-7.0};
	//double kappa1 = - (1.0 / 3.0);
	//double kappa2 = -(2.0 / 9.0);
	//cout << "Tridiagonal matrix algorithm test" << endl;
	//cout << "kappa1 = " << kappa1 << endl;
	//cout << "kappa2 = " << kappa2 << endl;
	//double mu1 = 4.0 / 3.0;
	//double mu2 = 11.0 / 9.0;
	//double phi[1] = { -10.0 };
	//double* example = new double[sizeof(phi) + 2];
	//cout << "size of A = " << sizeof(A)/sizeof(double) << endl;
	//HeatEq E(3, 0, 0, 0, 0, 0);
	//cout << "n = " << E.Getn() << endl;
	//E.TridiagMatrix(A, B, C, kappa1, kappa2, mu1, mu2, phi, 1);
	//E.PrintTMSolutions();

	HeatEq E1(5, 0, 0, 5, 0, 0);
	cout << "h = " << E1.Geth() << endl;
	E1.ZeroLayer();
	E1.PrintLayer();
}