

#include <algorithm>
#include <complex>
#include <iostream>
#include <sstream>
#include <vector>
//#include "bbpr.h"
#include "croot.h"

inline bool positiveX(double x)
{
	return (0 < x);
}

bool myfn(double i, double j) { return i<j; }

struct positive
{
	bool operator()(const double& left, const double& right) const
	{
		return left < right;
	}
};
struct myclass {
	bool operator() (int i, int j) { return i<j; }
} myobj;

int find(double a[], int size, bool compare(double))
{
	int i;

	for (i = 0; i < size && !compare(a[i]); i++);

	int min = i;

	for (; i < size; i++)
	{
		if (compare(a[i]) && a[i] < a[min]) min = i;
	}

	return (min);
}

// ------------------------------------------------------------------------ -
// Finds the SABR "alpha" parameter by solving the cubic equation described
// in West(2005) "Calibration of the SABR Model in Illiquid Markets"
// The function can return multiple roots.In that case, the program
// eliminates negative roots, and select the smallest root among the
// positive roots that remain.
// Required inputs :
// F = spot price
// K = strike price
// T = maturity
// ATMvol = ATM market volatility
// b = beta parameter
// r = rho parameter
// v = vol of vol parameter
// ------------------------------------------------------------------------ -
double findAlpha(double F, double K, double T, double ATMvol, double b, double r, double v)
{
	double Alpha;
	if (r == 0.0)
		int a = 5;
	// Find the coefficients of the cubic equation for alpha
	double C3 = pow(1 - b, 2) * T /( 24 / pow(F, 2 - 2 * b));
	double C2 = r*b*v*T / 4 / pow(F, 1 - b);
	double C1 = (1 + (2 - 3 * pow(r, 2)) / 24 * pow(v, 2) * T );
	double C0 = -ATMvol*pow(F,1 - b);
	// Return the roots of the cubic equation(multiple roots)
	// CRoot from Haug's book has a bug
//	Alpha = CRoot(C3,C2,C1,C0,r);
	Alpha = gan_solve_cubic(C3, C2, C1, C0);

	return Alpha;
}