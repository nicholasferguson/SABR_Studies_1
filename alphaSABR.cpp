
#include <math.h>
#define Defaults_EPSILON 0.000000000001
#include "alphaSABR.h"

// From Haug's book
double SABRVolatility(double  F, double K, double  T, double a, double  b, double v, double  r)
{

	return alphaSABR( F,  K,  T, a,  b, v, r);

}
// From Haug's book
double alphaSABR( double  F, double K, double  T, double a, double  b, double v, double  r)
{


	double dSABR[3];
	double sabrz, y;

	dSABR[0] = a / (pow(F*K, (1 - b) / 2) * 
				(1 +(pow(1 - b, 2) / 24) 
				* pow(log(F / K), 2)
				+ (pow(1 - b, 4) / 1920) * pow(log(F / K), 4)));

	if (fabs(F - K) > Defaults_EPSILON)
	{
		sabrz = (v / a) * pow(F*K, (1 - b) / 2) * log(F / K);
		y = (sqrt(1 - 2 * r * sabrz + pow(sabrz, 2)) + sabrz - r) / (1 - r);
		if (fabs(y - 1) < Defaults_EPSILON)
			dSABR[1] = 1;
		else if (y > 0)
			dSABR[1] = sabrz / log(y);
		else
			dSABR[1] = 1;

	}
	else
		dSABR[1] = 1;

	dSABR[2] = 1 + (((pow(1 - b, 2) / 24)* pow(a, 2) / (pow(F*K, (1 - b))))
		+ r*b*v*a / 4 / (pow(F*K, (1 - b) / 2))
		+ (2 - 3 * pow(r, 2)) * pow(v, 2) / 24) * T;

	return dSABR[0] * dSABR[1] * dSABR[2];



}
