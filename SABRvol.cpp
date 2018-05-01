#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#define Defaults_EPSILON 0.000000000001
//-------------------------------------------- -
//Returns the SABR volatility.
//Required inputs :
//a = alpha parameter
//b = beta parameter
//r = rho parameter
//v = vol of vol parameter
//F = spot price
//K = strike price
//T = maturity
//-------------------------------------------- -
//SABRvol(alpha, beta, rho, nu, forward, strike, expiryTime);
double SABRvol(double a, double  b, double r, double  v, double  F, double K, double  T)
{
	double Term1 = 0;
	double Term2 = 0;
	double Term3 = 0;
	double y = 0;
	double FK = 0;
	double z = 0;
	double x = 0;
	if (abs(F - K) <= 0.001) // ATM vol
	{
		Term1 = a / pow(F , (1 - b));
		Term2 = (pow((1 - b), 2) / 24 * pow(a, 2) / pow(F, (2 - 2 * b)) + (r*b*a*v) / 4 / pow(F, (1 - b)) + ((2 - 3 * pow(r, 2))* pow(v, 2)) / 24);
		y = Term1*(1 + Term2*T);
	}
	else  // Non - ATM vol
	{
		FK = F*K;
		z = (v / a)*pow((FK), ((1 - b) / 2))*log(F / K);
		x = log((sqrt(1 - 2 * r*z + pow(z, 2)) + z - r) / (1 - r));
		Term1 = a / pow(FK, ((1 - b) / 2)) / (1 + pow((1 - b), 2) / 24 * pow(log(F / K), 2) + pow((1 - b), 4) / 1920 * pow(log(F / K), 4));
		if (abs(x - z) < Defaults_EPSILON) // 1e-10)
			Term2 = 1;
		else
			Term2 = z / x;



		Term3 = 1 + ((pow((1 - b), 2) / 24) * pow(a, 2) / pow(F*K, (1 - b)) + r*b*v*a / 4 / pow(F*K, ((1 - b) / 2)) + (2 - 3 * pow(r, 2)) / 24 * pow(v, 2))*T;
		y = Term1*Term2*Term3;

	}

	return y;
}

bool isClose(double one, double two) {
	return one - two < Defaults_EPSILON;
}
// This function does not duplicate results in Haug's book.
double SABRvol2(double alpha, double beta, double rho, double nu, double forward, double strike, double expiryTime)
{
	double oneMinusBeta = 1.0 - beta;
	double A = pow(forward * strike, oneMinusBeta);
	double sqrtA = sqrt(A);
	double logM;
	if (!isClose(forward, strike))
		logM = log(forward / strike);
	else {
		double epsilon = (forward - strike) / strike;
		logM = epsilon - .5 * epsilon * epsilon;
	}
	double z = (nu / alpha) * sqrtA * logM;
	double B = 1.0 - 2.0 * rho * z + z * z;
	double C = oneMinusBeta * oneMinusBeta * logM * logM;
	double tmp = (sqrt(B) + z - rho) / (1.0 - rho);
	double xx = log(tmp);
	double D = sqrtA * (1.0 + C / 24.0 + C * C / 1920.0);
	double d = 1.0
		+ expiryTime
		* (oneMinusBeta * oneMinusBeta * alpha * alpha / (24.0 * A)
		+ 0.25 * rho * beta * nu * alpha / sqrtA + (2.0 - 3.0
		* rho * rho)
		* (nu * nu / 24.0));

	double multiplier;
	// computations become precise enough if the square of z worth
	// slightly more than the precision machine (hence the m)
	double m = 10;
	if (abs(z * z) >  Defaults_EPSILON  * m)
		multiplier = z / xx;
	else {
		double talpha = (0.5 - rho * rho) / (1.0 - rho);
		double tbeta = alpha - .5;
		double tgamma = rho / (1 - rho);
		multiplier = 1.0 - beta * z
			+ (tgamma - talpha + tbeta * tbeta * .5) * z * z;
	}
	return (alpha / D) * multiplier * d;
}
