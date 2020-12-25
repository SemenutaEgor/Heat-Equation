// main.cpp

#include <stdlib.h>
#include "HeatEq.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;

void Menu(HeatEq Eq) {
	string com;
	do {
		cout << "Введите 'help' для, чтобы появился список команд" << endl;
		cin >> com;
		if (com == "initial") {
			//clrscr();
			//gotoxy(0, 1);
			int n, m;
			double tf, mint, maxt;
			cout << "Введите T - конечное время: ";
			cin >> tf;
			Eq.Sett_finish(tf);
			cout << "Введите n - количество узлов по x: ";
			cin >> n;
			Eq.Setn(n);
			cout << "Введите m - количество слоёв: ";
			cin >> m;
			Eq.Setm(m);
			cout << "Введите температуру переохлаждения стержня: ";
			cin >> mint;
			Eq.Setmin_temp(mint);
			cout << "Введите температуру перегрева стержня: ";
			cin >> maxt;
			Eq.Setmax_temp(maxt);

			Eq.ReCreate();
		}

		if (com == "info") {
			cout << "Вариант 4" << endl;
			cout << "Уравнение тепопроводности: du/dt = 9 * d^2u/dx^2 + 5*sin(t)" << endl;
			cout << "x принадлежит отрезку [0,1], t принадлежит отрезку [0, 1000]" << endl;
			cout << "Начальные условия: u(x, 0) = 1 - x^2" << endl;
			cout << "Граничные условия слева (второго рода): du/dx(0, t) = 0" << endl;
			cout << "Граничные условия справа (третьего рода): -du/dx(1, t) = 7 * (u(1, t) - 2/7)" << endl;
			cout << "Неявная разностная схема:" << endl;
			cout << "(9*tau/h^2) * v[i-1, j+1] + (9*tau/h^2) * v[i+1, j+1] - (1 + 18*tau/h^2) * v[i, j+1] = - (5*tau*sin(t) + v[i, j])" << endl;
			cout << "i = 1, ... , n-1;     j = 1, ..., m" << endl;
			cout << "v[i, 0] = 1 - x^2,    i = 0, ..., n" << endl;
			cout << "(v[1, j+1] - v[0, j+1])/h = 0,    j = 1, ..., m" << endl;
			cout << "-(v[n, j+1] - v[n-1, j+1])/h = 7 * (v[n, j+1] - 2/7),    j = 1, ..., m" << endl;
			cout << endl;
			cout << "a = " << Eq.Getx_start() << " - начало отрезка по x" <<endl;
			cout << "b = " << Eq.Getx_finish() << " - конец отрезка по x" << endl;
			cout << "t0 = " << Eq.Gett_start() << " - начало отрезка по t" << endl;
			cout << "T = " << Eq.Gett_finish() << " - конец отрезка по t" << endl;
			cout << "h = " << Eq.Geth() << " - шаг по x" << endl;
			cout << "tau = " << Eq.Gettau() << " - шаг по t" << endl;/*
			cout << "Матрица прогонки для последнего посчитанного слоя" << endl;
			Eq.PrintMatrix();*/
		}

		if (com == "solve") {
			ofstream out;
			out.open("HeatSourcesInTime.txt", std::ios::app);
			double heat_density;
			double time;
			Eq.ReCreate();
			Eq.ZeroLayer();
			Eq.TempCheckToFile();
			Eq.PrintLastLayerToFile();
			heat_density = Eq.HeatSource(0);
			if (heat_density < 0) {
				out << "t = " << 0 <<" Плотность стоков тепла: " << heat_density << endl;
			}
			else {
				if (heat_density > 0) {
					out << "t = " << 0 << "Плотность источников тепла: " << heat_density << endl;
				}
				else {
					out << "t = " << 0 << "Источников (стоков) тепла нет" << endl;
				}
			}
			for (int i = 1; i <= Eq.Getm(); i++) {
				Eq.NextLayer();
				Eq.TempCheckToFile();
				Eq.PrintLastLayerToFile();
				time = Eq.Gett_start() + Eq.Gettau() * Eq.Getlayer_counter();
				heat_density = Eq.HeatSource(time);
				if (heat_density < 0) {
					out << "t = " << time << " Плотность стоков тепла: " << heat_density << endl;
				}
				else {
					if (heat_density > 0) {
						out << "t = " << time << " Плотность источников тепла: " << heat_density << endl;
					}
					else {
						out << "t = " << time << " Источников (стоков) тепла нет" << endl;
					}
				}
			}
			out.close();
		}

		if (com == "temp") {
			double x = -1;
			double t = -1;
			string strx, strt;
			while ((x < 0) || (x > 1)) {
				cout << "Ведите x (от 0 до 1): ";
				cin >> x;
			}

			while ((t < 0) || (t > 1000)) {
				cout << "Ведите t (от 0 до 1000): ";
				cin >> t;
			}

			strx = to_string(x);
			//cout << "strx = " << strx << endl;
			int xcounter = 0;
			for (int i = strx.length()-1; i >= 0; i--) {
				//cout << "str[" << i << "] = " << strx[i] << endl;
				if (strx[i] == ',') {
					break;
				}
				else {
					if (strx[i] != '0') {
						xcounter++;
					}
				}
			}
			/*cout << "xcounter = " << xcounter << endl;*/

			strt = to_string(t);
			//cout << "strx = " << strx << endl;
			int tcounter = 0;
			for (int i = strt.length() - 1; i >= 0; i--) {
				//cout << "str[" << i << "] = " << strx[i] << endl;
				if (strt[i] == ',') {
					break;
				}
				else {
					if (strt[i] != '0') {
						tcounter++;
					}
				}
			}
			/*cout << "tcounter = " << tcounter << endl;*/
		

			double valn = pow(10, xcounter);
			if (valn <= 1000) {
				Eq.Setn(1000);
			}
			else {
				Eq.Setn(valn);
			}

			double valm = 1000 * pow(10, tcounter);
			if (valm <= 1000) {
				Eq.Setm(1000);
			}
			else {
				Eq.Setm(valm);
				cout << "valm = " << valm << endl;
			}

			//calculate temperature

			Eq.ReCreate();

			double temp;
			temp = Eq.GetTemperature(x, t); 

			cout << "v(" << x << "," << t << ") = " << temp << endl;
		}

		if (com == "h") {
			cout << "h = " << Eq.Geth() << endl;
		}

		if (com == "tau") {
			cout << "tau = " << Eq.Gettau() << endl;
		}

		if (com == "n") {
			cout << "n = " << Eq.Getn() << endl;
		}

		if (com == "m") {
			cout << "m = " << Eq.Getm() << endl;
		}

		if (com == "matrix") {
			Eq.PrintMatrix();
		}

		if (com == "layer") {
			int num, res;
			cout << "Введите номер слоя от 0 до " << Eq.Getm() << ": ";
			cin >> num;
			if (num == 0) {
				res = Eq.CheckedZeroLayer();
				if (res != -1) {
					Eq.PrintLastLayer();
				}
			}
			else {
				Eq.ZeroLayer();
				for (int i = 1; i < num; i++) {
					Eq.NextLayer();
					//cout << "Посчитал " << layer_counter << " слой" << endl;
				}
				res = Eq.CheckedNextLayer();
				if (res != -1) {
					Eq.PrintLastLayer();
				}
			}
		}

		if (com == "heatsource") {
			double heat_density;
			double time;
			cout << "Введите время: t = ";
			cin >> time;
			heat_density = Eq.HeatSource(time);
			if (heat_density < 0) {
				cout << "Плотность стоков тепла: " << heat_density << endl;
			}
			else {
				if (heat_density > 0) {
					cout << "Плотность источников тепла: " << heat_density << endl;
				}
				else {
					cout << "Источников (стоков) тепла нет" << endl;
				}
			}
		}

		if (com == "help") {
			cout << endl;
			cout << "initial - ввод новых параметров для уравнения" << endl;
			cout << "info - узнать все параметры" << endl;
			cout << "solve - узнать температуру во всех узлах сетки (только после initial)" << endl;
			cout << "temp - узнать температуру в конкретной точке" << endl;
			cout << "layer - вывести на экран какой-то слой (только после initial)" << endl;
			cout << "heatsource - вывести на экран плотность источников (стоков) тепла в момент времени t (только после initial)" << endl;
			cout << "h - узнать шаг h по x" << endl;
			cout << "tau - узнать шаг tau по t" << endl;
			cout << "n - узнать количество узлов n по x" << endl;
			cout << "m - узнать количество узлов m по t" << endl;/*
			cout << "matrix - напечатать матрицу прогонки (для последнего посчитанного слоя)" << endl;*/
			cout << "exit - exit" << endl;
		}
	} while (com != "exit");
}

int main() {
	system("title Задача 10 Неявная разностная схема для нестационарного уравнения теплопроводности, Семенюта Е. Родионов П.");
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