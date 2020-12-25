//HeatEq.cpp

#include "HeatEq.h"

HeatEq::HeatEq() {
	this->n = 0;
	this->m = 0;
	this->x_start = 0;
	this->x_finish = 1;
	this->t_start = 0;
	this->t_finish = 1000;

	this->h = 0;
	this->tau = 0;

	this->A = 0;
	this->B = 0;
	this->C = 0;
	this->kappa1 = 0;
	this->kappa2 = 0;
	this->mu1 = 0;
	this->mu2 = 0;
	this->phi_arr = new double[0];
	this->TMsolutions = new double[0];

	this->layer = new double[0];
	this->layer_counter = 0;

}

HeatEq::HeatEq(int n, int m) {
	this->n = n;
	this->m = m;
	this->x_start = 0;
	this->x_finish = 1;
	this->t_start = 0;
	this->t_finish = 1000;

	this->h = (x_finish - x_start) / n;
	this->tau = (t_finish - t_start) / m;

	this->A = (9.0 * tau) / pow(h, 2);
	this->B = (9.0 * tau) / pow(h, 2);
	this->C = 1.0 + (18.0 * tau) / pow(h, 2);
	this->kappa1 = 1.0;
	this->kappa2 = 1.0 / (1.0 + 7.0 * h);
	this->mu1 = 0;
	this->mu2 = (2 * h) / (1.0 + 7.0 * h);
	this->phi_arr = new double[n - 2];
	this->TMsolutions = new double[n];

	this->layer = new double[n + 1];
	this->layer_counter = 0;

}

void HeatEq::ReCreateIrreg() {
	this->h = h;
	this->tau = tau;
	this->x_start = 0;
	this->x_finish = 1;
	this->t_start = 0;
	this->t_finish = 1000;

	this->n = 1 + (x_finish - x_start) / h;
	this->m = 1 + (t_finish - t_start) / tau;

	this->h = (x_finish - x_start) / n;
	this->tau = (t_finish - t_start) / m;

	this->A = (9.0 * tau) / pow(h, 2);
	this->B = (9.0 * tau) / pow(h, 2);
	this->C = 1.0 + (18.0 * tau) / pow(h, 2);
	this->kappa1 = 1.0;
	this->kappa2 = 1.0 / (1.0 + 7.0 * h);
	this->mu1 = 0;
	this->mu2 = (2 * h) / (1.0 + 7.0 * h);
	this->phi_arr = new double[n - 2];
	this->TMsolutions = new double[n];

	this->layer = new double[n + 1];
	this->layer_counter = 0;

}


void HeatEq::ReCreate() {
	h = (x_finish - x_start) / n;
	tau = (t_finish - t_start) / m;

	A = (9.0 * tau) / pow(h, 2);
	B = (9.0 * tau) / pow(h, 2);
	C = 1.0 + (18.0 * tau) / pow(h, 2);
	kappa1 = 1.0;
	kappa2 = 1.0 / (1.0 + 7.0 * h);
	mu1 = 0;
	mu2 = (2 * h) / (1.0 + 7.0 * h);
	phi_arr = new double[n - 2];
	TMsolutions = new double[n];

	layer = new double[n + 1];
	layer_counter = 0;
}

double HeatEq::Getx_start() {
	return x_start;
}

double HeatEq::Gett_start() {
	return t_start;
}

double HeatEq::Getx_finish() {
	return x_finish;
}

double HeatEq::Gett_finish() {
	return t_finish;
}

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

double HeatEq::GetPhi(int i, int j) {
	double Phi;
	Phi = 5 * tau * sin(t_start + j * tau) + layer[i];
	return Phi;
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

void HeatEq::TempCheckToFile() {
	ofstream out;
	out.open("TemperatureControl.txt", std::ios::app);
	int layernum = layer_counter;
	for (int i = 0; i <= n; i++) {
		if (layer[i] < min_temp) {
			out << "Стержень переохладился в точке " << "v[" << i << "," << layernum << "], его температура = " << scientific << layer[i] << endl;
		}
		if (layer[i] > max_temp) {
			out << "Стержень перегрелся в точке " << "v[" << i << "," << layernum << "], его температура = " << scientific << layer[i] << endl;
		}
	}
	out.close();
}

int HeatEq::TempCheck(double temp, int index) {
	int layernum = layer_counter;
	if (temp < min_temp) {
		cout << "Стержень переохладился в точке " << "v[" << index << "," << layernum <<"], его температура = " << scientific << temp << endl;
		string ch;
		do {
			cout << "Продолжить?(y/n)";
			cin >> ch;
			if (ch == "n") {
				return -1;
			}
		} while (ch != "y");
	}
	if (temp > max_temp) {
		cout << "Стержень перегрелся в точке " << "v[" << index << "," << layernum << "], его температура = " << scientific << temp << endl;
		string ch;
		do {
			cout << "Продолжить?(y/n)";
			cin >> ch;
			if (ch == "n") {
				return -1;
			}
		} while (ch != "y");
	}
	else
		return 0;
}

int HeatEq::CheckedZeroLayer() {
	for (int i = 0; i < n + 1; i++) {
		layer[i] = 1 - pow((x_start + i * h), 2);
		if (TempCheck(layer[i], i) == -1) {
			return -1;
		}
	}
	return 0;
}

int HeatEq::CheckedNextLayer() {
	layer_counter++;
	double* alphas = new double[n];
	double* betas = new double[n];

	// forward sweep
	alphas[0] = kappa1;
	betas[0] = mu1;

	for (int i = 0; i < n - 1; i++) {
		alphas[i + 1] = B / (C - alphas[i] * A);
		betas[i + 1] = ((5.0 * tau * sin(t_start + ((layer_counter + 1) * tau)) + layer[i + 1]) + betas[i] * A) / (C - alphas[i] * A);
	}

	// back substitution
	layer[n] = (mu2 + kappa2 * betas[n - 1]) / (1 - kappa2 * alphas[n - 1]);
	if (TempCheck(layer[n], n) == -1) {
		return -1;
	}

	for (int i = n - 1; i >= 0; i--) {
		layer[i] = alphas[i] * layer[i + 1] + betas[i];
		if (TempCheck(layer[i], i) == -1) {
			return -1;
		}
	}

	/*layer_counter++;*/
	return 0;
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
		betas[i + 1] = ((5.0 * tau * sin(t_start + ((layer_counter + 1) * tau)) + layer[i + 1]) + betas[i] * A) / (C - alphas[i] * A);
	}

	// back substitution
	layer[n] = (mu2 + kappa2 * betas[n - 1]) / (1 - kappa2 * alphas[n - 1]);

	for (int i = n - 1; i >= 0; i--) {
		layer[i] = alphas[i] * layer[i + 1] + betas[i];
	}

	layer_counter++;
}

double HeatEq::GetTemperature(double x, double t) {
	int xindex = (x - x_start) / h;
	int tindex = (t - t_start) / tau;

	//cout << "xindex = " << xindex << endl;
	//cout << "tindex = " << tindex << endl;

	ZeroLayer();
	//cout << "Посчитал " << layer_counter << " слой" << endl;
	for (int i = 1; i <= tindex; i++) {
		NextLayer();
		//cout << "Посчитал " << layer_counter << " слой" << endl;
	}

	return layer[xindex];
}

double HeatEq::HeatSource(double time) {
	return 5 * sin(time);
}

void HeatEq::AverageTemperatureOnLayer() {
	ofstream out;
	out.open("AverageTemperature.txt", std::ios::app);
	double temperature;
	double average_temperature;
	temperature = 0;
	for (int i = 0; i <= n; i++) {
		temperature += layer[i];
	}
	average_temperature = temperature / n;
	out << "Средняя температура на слое " << layer_counter << " = "<< average_temperature << endl;
	out.close();
}

//void HeatEq::HeatSourcesInTime() {
//	ofstream out;
//	out.open("HeatSourcesInTime.txt", std::ios::app);
//
//	for ()
//
//	heat_density = Eq.HeatSource(time);
//	if (heat_density < 0) {
//		cout << "Плотность стоков тепла: " << heat_density << endl;
//	}
//	else {
//		if (heat_density > 0) {
//			cout << "Плотность источников тепла: " << heat_density << endl;
//		}
//		else {
//			cout << "Источников (стоков) тепла нет" << endl;
//		}
//	}
//}


void HeatEq::PrintTMSolutions() {
	for (int i = 0; i < n; i++) {
		cout << "sol[" << i << "] = " << TMsolutions[i] << endl;
	}
}

void HeatEq::PrintLastLayerToFile() {
	ofstream out;
	out.open("Grid.txt", std::ios::app);
	out << fixed;
	out.precision(15);
	int layernum = layer_counter;
	for (int i = 0; i < n + 1; i++) {
		out <<  "v[" << i << "," << layernum << "] = " << scientific << layer[i] << setw(10);
	}            
	out << endl;
	out.close();
}

void HeatEq::PrintLastLayer() {
	cout << fixed;
	cout.precision(15);
	int layernum = layer_counter;
	for (int i = 0; i < n + 1; i++) {
		cout << "v[" << i << "," << layernum << "] = " << scientific << layer[i] << setw(10);
	}
	cout << endl;
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

