#include <fstream>
#include<vector>
#include <string>
#include <cmath>
#include "plplot\plstream.h"
using namespace std;
const int NSIZE = 101;
int main(int argc, char ** argv) {
	ifstream fin("input.txt");
	if (!fin)
		exit(1);
	string max_frequency;
	int n;//no of inputs;
	fin >> n;
	double temp, max = 0, min = INT_MAX;
	double *x_input = new double[n], *y_input = new double[n];
	for (int i = 0; i < n; i++)
	{
		fin >> x_input[i];
		fin >> y_input[i];
		if (max < y_input[i])
		{
			max = y_input[i];
			max_frequency = to_string(int(x_input[i]));
		}
		if (min > y_input[i])
			min = y_input[i];
		x_input[i] = log10(x_input[i]);
	}
	max_frequency = "max freq : " + max_frequency + " Hz";
	//std::cout << max;
	for (int i = 0; i < n; i++)
	{
		y_input[i] = 20 * log10(y_input[i] / max);
	}
	double x[NSIZE], y[NSIZE];
	int size = -5 + int(20 * log10(min / max));
	PLFLT xmin = 1, xmax = 7., ymin = size, ymax = 1;
	int   i;
	for (i = 0; i < NSIZE; i++) {
		x[i] = i;
		y[i] = i;
	}
	auto pls = new plstream();
	plsdev("wingcc");
	pls->init();
	pls->env(xmin, xmax, ymin, ymax, 0, 10);
	pls->lab("x (Hz)", "y (dB)", "Frequency Response ");
	pls->line(NSIZE, x_input, y_input);
	pls->ptex(6.5, -20, 0, 0, 1, max_frequency.c_str());
	delete pls;
	fin.close();
}