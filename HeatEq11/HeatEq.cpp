//HeatEq.cpp

#include "HeatEq.h"

int HeatEq::Getn() {
	return n;
}

int HeatEq::Getm() {
	return m;
}

double HeatEq::Geth() {
	return h;
}

double HeatEq::Gettau() {
	return tau;
}

int HeatEq::Getlayer_counter() {
	return layer_counter;
}

double HeatEq::GetA() {
	return A;
}

double HeatEq::GetB() {
	return B;
}

double HeatEq::GetC() {
	return C;
}

double HeatEq::GetKappa1() {
	return kappa1;
}

double HeatEq::GetKappa2() {
	return kappa2;
}

void HeatEq::TridiagMatrix(double* A_arr, double* B_arr, double* C_arr, double kappa1, double kappa2, double mu1, double mu2, double* phi_arr, int size_arr)
{
	int arr_size = size_arr + 2;
	int n = arr_size - 1;
	double* alphas = new double[n];
	double* betas = new double[n];

	//for (int i = 0; i < size_arr; i++) {
	//	cout << "A[" << i << "] = " << A_arr[i] << endl;
	//}

	//for (int i = 0; i < size_arr; i++) {
	//	cout << "B[" << i << "] = " << B_arr[i] << endl;
	//}

	//for (int i = 0; i < size_arr; i++) {
	//	cout << "C[" << i << "] = " << C_arr[i] << endl;
	//}

	//for (int i = 0; i < size_arr; i++) {
	//	cout << "phi[" << i << "] = " << phi_arr[i] << endl;
	//}

	//cout << "kappa1 = " <<  kappa1 << endl;
	//cout << "kappa2 = " << kappa2 << endl;
	//cout << "mu1 = " << mu1 << endl;
	//cout << "mu2 = " << mu2 << endl;

	// forward sweep
	alphas[0] = kappa1;
	betas[0] = mu1;
	//cout << "alpha[" << 0 << "] = " << alphas[0] << endl;
	//cout << "beta[" << 0 << "] = " << betas[0] << endl;
	for (int i = 0; i < n - 1; i++) {
		alphas[i + 1] = B_arr[i] / (C_arr[i] - alphas[i] * A_arr[i]);
		betas[i + 1] = (phi_arr[i] + betas[i] * A_arr[i]) / (C_arr[i] - alphas[i] * A_arr[i]);
		//cout << "alpha[" << i+1 << "] = " << alphas[i+1] << endl;
		//cout << "beta[" << i+1 << "] = " << betas[i+1] << endl;
	}

	// back substitution
	TMsolutions[n] = (mu2 + kappa2 * betas[n - 1]) / (1 - kappa2 * alphas[n - 1]);
	//cout << "n = " << n << endl;

	for (int i = n - 1; i >= 0; i--) {
		TMsolutions[i] = alphas[i] * TMsolutions[i + 1] + betas[i];
	}

	//	for (int i = 0; i <= n; i++) {
	//		cout << "sol[" << i << "] = " << solutions[i] << endl;
	//	}
}

void HeatEq::ZeroLayer() {
	for (int i = 0; i < n + 1; i++) {
		layer[i] = 1 - pow((x_start + i * h), 2);
	}
}

void HeatEq::NextLayer() {
	double* alphas = new double[n];
	double* betas = new double[n];

	// forward sweep
	alphas[0] = kappa1;
	betas[0] = mu1;

	for (int i = 0; i < n - 1; i++) {
		alphas[i + 1] = B / (C - alphas[i] * A);
		betas[i + 1] = ((5.0 * tau * sin(t_start + i * tau) + layer[i]) + betas[i] * A) / (C - alphas[i] * A);
	}

	// back substitution
	layer[n] = (mu2 + kappa2 * betas[n - 1]) / (1 - kappa2 * alphas[n - 1]);

	for (int i = n - 1; i >= 0; i--) {
		layer[i] = alphas[i] * layer[i + 1] + betas[i];
	}

	layer_counter++;
}


void HeatEq::PrintTMSolutions() {
	for (int i = 0; i < n; i++) {
		cout << "sol[" << i << "] = " << TMsolutions[i] << endl;
	}
}

void HeatEq::PrintLastLayer() {
	for (int i = 0; i < n + 1; i++) {
		cout << "v[" << i << "," << layer_counter << "] = " << layer[i] << endl;
	}
}

void HeatEq::PrintMatrix() {
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n+1; j++)
		{
			if ((i == 0) && (j == 0)) {
				cout << 1 << "\t";
			}
			else
				if ((i == 0) && (j == 1)) {
					cout << -kappa1 << "\t";
				}
				else
					if ((i == n) && (j == n - 1)) {
						cout << -kappa2 << "\t";
					}
					else
						if ((i == n) && (j == n)) {
							cout << 1 << "\t";
						}
						else
							if (i == j) {
								cout << -C << "\t";
							}
							else
								if (i - j == 1) {
									cout << A << "\t";
								}
								else
									if (j - i == 1) {
										cout << B << "\t";
									}
									else
										cout << 0 << "\t";
		}
		cout << '\n';
	}
}

