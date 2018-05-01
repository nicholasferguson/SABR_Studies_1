// Haug_example_p270.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include "SABRvol.h"
#include "findAlpha.h"
#include "oFmt.h"
#include "alphaSABR.h"
#include "Black76.h"


double**  createMatrix(unsigned int rows, unsigned int cols) {
	double ** matrix;
	matrix = (double **)calloc(cols, sizeof(double *));
	for (unsigned int i = 0; i < cols; i++)
		matrix[i] = (double *)calloc(cols, sizeof(double));
	return matrix;
}

int main()
{
	// Example from page 270 of Espen Haug's (aka The Collector) excellent book
	// By Fabrice Douglas Rouah ( for matlab )
	// Converted to C/C++ by Nicholas Ferguson
	// Added Black-76 put, call and put call parity.

	// Required inputs
	double F = 100;            // Futures price
	double T = 0.5;            // Maturity in years
	double b = 0.999;         // beta SABR parameter
	double v = 0.5;            // vol - of - vol SABR parameter
	double ATMvol = 0.30;      // Market ATM volatility
	double r = .02;           // for Black 76 only.

	// Define the strikes and correlation levels
	std::vector<double> K = { 70, 80, 90, 100, 110, 120, 130 };
	// Correlation levels are simply incremented by .25 about a mean of zero?
	std::vector<double> rho = { -0.75, -0.50 ,-0.25, 0.00, 0.25, 0.50, 0.75 };

	// Find the length of each vector
	int I = rho.size();
	int J = K.size();



	// data structures.
	double** Vol = createMatrix(I, J);
	double** alpha = createMatrix(I, J);
	double** blackP = createMatrix(I, J);
	double** blackC = createMatrix(I, J);
	double** parity = createMatrix(I, J);

	// Find the SABR volatilities for each strike / correlation combination
	// SABRVolatility is from VB code from Haug's book
	// SABRVol is from matlab code from Fabrice Douglas Rouah website.
	// We can run either and get same result.
	for (int i = 0; i < I; ++i){
		for (int j = 0; j < J; ++j){
			alpha[i][j] = findAlpha(F, K[j], T, ATMvol, b, rho[i], v);
			//Vol[i][j] = SABRVolatility(F, K[j], T, alpha[i][j], b, v, rho[i]);
			Vol[i][j] = SABRvol(alpha[i][j], b, rho[i], v, F, K[j], T);
			blackP[i][j] = Black76(F, K[j], T, Vol[i][j], r, "Put");
			blackC[i][j] = Black76(F, K[j], T, Vol[i][j], r, "Call");
			parity[i][j] = diffInPutCallParity(blackC[i][j], blackP[i][j], F, K[j], r, T);
			Vol[i][j] *= 100;  // to make ouput %.  This format agrees with Haug's example.
			}}


	std::cout << "SABR Black-76 Equivalent Volatilies (%)" << std::endl << std::endl;
	print_2Dmatrix2(Vol,K, rho);
	std::cout << std::endl;
	std::cout << "Alpha Parameter Values" << std::endl << std::endl;
	print_2Dmatrix2(alpha, K, rho);
	std::cout << std::endl;
	std::cout << "Black-76 Put Prices r:" << r << std::endl << std::endl;
	print_2Dmatrix2(blackP, K, rho);
	std::cout << std::endl;
	std::cout << "Black-76 Call Prices r:" << r << std::endl << std::endl;
	print_2Dmatrix2(blackC, K, rho);
	std::cout << std::endl;
	std::cout << "diff in Black-76 Put Call Parity Eqn: (C-P) - (F-K)exp(-rT) r:" << r << " F: " << F << " T:" << T << std::endl << std::endl;
	print_2Dmatrix2(parity, K, rho);
	return 0;
}

