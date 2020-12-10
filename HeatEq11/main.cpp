// main.cpp

#include <stdlib.h>
#include "HeatEq.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

void Menu(HeatEq Eq) {
	string com;
	do {
		cout << "¬ведите 'help' дл€, чтобы по€вилс€ список команд" << endl;
		cin >> com;
		if (com == "create") {
			//clrscr();
			//gotoxy(0, 1);
			int n, m;
			double x0, xn, t0, tn;
			cout << "¬ведите x0: ";
			cin >> x0;
			Eq.Setx_start(x0);
			cout << "¬ведите xn: ";
			cin >> xn;
			Eq.Setx_finish(xn);
			cout << "¬ведите t0: ";
			cin >> t0;
			Eq.Sett_start(t0);
			cout << "¬ведите tn: ";
			cin >> tn;
			Eq.Sett_finish(tn);
			cout << "¬ведите n: ";
			cin >> n;
			Eq.Setn(n);
			cout << "¬ведите m: ";
			cin >> m;
			Eq.Setm(m);

			Eq.ReCreate();
		}

		if (com == "solve") {
			Eq.ZeroLayer();
			Eq.PrintLastLayer();
			for (int i = 1; i <= Eq.Getm(); i++) {
				Eq.NextLayer();
				Eq.PrintLastLayer();
			}
		}

		if (com == "temp") {
			double x, t;
			cout << "¬едите x: ";
			cin >> x;
			int xcounter = 0;
			while (fmod(x, 1.0) != 0) {
				xcounter++;
				x *= 10;
			}

			int valn = pow(10, xcounter);
			if (valn <= 100) {
				Eq.Setn(100);
			}
			else {
				Eq.Setn(valn);
			}

			cout << "¬ведите t: ";
			cin >> t;
			int tcounter = 0;
			while (fmod(t, 1.0) != 0) {
				tcounter++;
				t *= 10;
			}
			int valm = pow(10, tcounter);
			if (valm <= 1000) {
				Eq.Setn(1000);
			}
			else {
				Eq.Setn(valm);
			}

			Eq.ReCreate();

			int xindex = (x - Eq.Getx_start()) / Eq.Geth();
			int tindex = (t - Eq.Gett_start()) / Eq.Gettau();

			double value;
			value = Eq.GetTemperature(xindex, tindex); //дописать функцию, котора€ будет просчитывать эту 
			                                           //новую сетку до нужного значени€ и возвр€щать его.
		}

		if (com == "help") {
			cout << "create - ввод новых параметров дл€ уравнени€" << endl;
			cout << "solve - узнать температуру во всех узлах сетки" << endl;
			cout << "temp - узнать температуру в конкретной точке" << endl;
			cout << "exit - exit" << endl;
		}
	} while (com != "exit");
}

int main() {
	setlocale(LC_ALL, "Russian");
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

	//HeatEq E1(5, 1, 0, 5, 0, 1);
	//cout << "h = " << E1.Geth() << endl;
	//cout << "tau = " << E1.Gettau() << endl;
	//E1.ZeroLayer();
	//E1.PrintLastLayer();
	//cout << "A = " << E1.GetA() << endl;
	//cout << "B = " << E1.GetB() << endl;
	//cout << "C = " << E1.GetC() << endl;
	//cout << "kappa1 = " << E1.GetKappa1() << endl;
	//cout << "kappa2 = " << E1.GetKappa2() << endl;
	//E1.PrintMatrix();

	HeatEq Eq;
	Menu(Eq);
	//E1.NextLayer();
	//cout << "it is a " << E1.Getlayer_counter() << " layer:" << endl;
	//E1.PrintLastLayer();

}