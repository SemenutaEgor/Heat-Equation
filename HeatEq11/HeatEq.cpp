//HeatEq.cpp

#include "HeatEq.h"

void HeatEq::TriagMatrix(double* A_arr, double* B_arr, double* C_arr, double kappa1, double kappa2, double mu1, double mu2, double* phi_arr, int size_arr)
{
	int arr_size = size_arr + 2;
	int n = arr_size - 1;
	double* solutions = new double[n + 1];
	double* alphas = new double[n];
	double* betas = new double[n];

	for (int i = 0; i < size_arr; i++) {
		cout << "A[" << i << "] = " << A_arr[i] << endl;
	}

	for (int i = 0; i < size_arr; i++) {
		cout << "B[" << i << "] = " << B_arr[i] << endl;
	}

	for (int i = 0; i < size_arr; i++) {
		cout << "C[" << i << "] = " << C_arr[i] << endl;
	}

	for (int i = 0; i < size_arr; i++) {
		cout << "phi[" << i << "] = " << phi_arr[i] << endl;
	}

	cout << "kappa1 = " <<  kappa1 << endl;
	cout << "kappa2 = " << kappa2 << endl;
	cout << "mu1 = " << mu1 << endl;
	cout << "mu2 = " << mu2 << endl;

	// forward sweep
	alphas[0] = kappa1;
	betas[0] = mu1;
	cout << "alpha[" << 0 << "] = " << alphas[0] << endl;
	cout << "beta[" << 0 << "] = " << betas[0] << endl;
	for (int i = 0; i < n - 1; i++) {
		alphas[i + 1] = B_arr[i] / (C_arr[i] - alphas[i] * A_arr[i]);
		betas[i + 1] = (phi_arr[i] + betas[i]*A_arr[i]) / (C_arr[i] - alphas[i] * A_arr[i]);
		cout << "alpha[" << i+1 << "] = " << alphas[i+1] << endl;
		cout << "beta[" << i+1 << "] = " << betas[i+1] << endl;
	}

	// back substitution
	solutions[n] = (mu2 + kappa2*betas[n-1]) / (1 - kappa2*alphas[n-1]);
	cout << "n = " << n << endl;

	for (int i = n-1; i >= 0; i--) {
		solutions[i] = alphas[i] * solutions[i+1] + betas[i];
	}

	for (int i = 0; i < arr_size; i++) {
		cout << "sol[" << i << "] = " << solutions[i] << endl;
	}
}

//void HeatEq::PrintSolutions()
//{
//	for (int i = 0; i < sizeof(solutions); i++) {
//		cout << solutions[i] << endl;
//	}
//}
