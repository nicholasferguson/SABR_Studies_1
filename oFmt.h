#pragma once


#include <iostream>
#include <iomanip>
#include <locale>
using namespace std;

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>


std::string fixed_precision_string(double num) {

	// Magic numbers
	static const int prec_limit = 14;       // Change to 15 if you wish
	static const double log10_fuzz = 1e-15; // In case log10 is slightly off
	static const char decimal_pt = '.';     // Better: use std::locale

	if (num == 0.0) {
		return "0";
	}

	std::string result;

	if (num < 0.0) {
		result = '-';
		num = -num;
	}

	int ndigs = int(std::log10(num) + log10_fuzz);
	std::stringstream ss;
	if (ndigs >= prec_limit) {
		ss << std::fixed
			<< std::setprecision(0)
			<< num;
		result += ss.str();
	}
	else {
		ss << std::fixed
			<< std::setprecision(prec_limit - ndigs)
			<< num;
		result += ss.str();
		auto last_non_zero = result.find_last_not_of('0');
		if (result[last_non_zero] == decimal_pt) {
			result.erase(last_non_zero);
		}
		else if (last_non_zero + 1 < result.length()) {
			result.erase(last_non_zero + 1);
		}
	}
	return result;
}


// from oFmt is from a discussion board.
// needs work. Still too much customization to create a well shaped report.
class oFmt
{
	int myWidth;
	int myPrecision;

public:

	oFmt(int width, int precision)
		: myWidth(width)
		, myPrecision(precision)
	{
	}
	friend std::ostream&
		operator<<(std::ostream& dest, oFmt const& format)
	{
		dest.setf(std::ios_base::fixed, std::ios_base::floatfield);
		dest.precision(format.myPrecision);
		dest.internal;
		dest.width(format.myWidth);
		return dest;
	}
};


template< typename T>
void print_2Dmatrix(T& matrix) {
	int rows = sizeof matrix / sizeof matrix[0]; // 2 rows  
	int cols = sizeof matrix[0] / sizeof(double); // 5 cols

	for (int i = 0; i < rows; ++i) {
		cout << "\t\t";
		for (int j = 0; j < cols; ++j) {
			cout  << oFmt(8, 4) << ((double*)matrix)[i*cols + j] << "\t";
		}
		cout << endl;
	}
}
/**
* \prints with header, y axis labels and fills with data
* \param matrix is data, double[][]
* \param headers.
* \param labels is y axis labels
*  
*  Needs work.  Too much customization to create a report. ie. oFmt(8,0), oFmt(10,6)
*/

void print_2Dmatrix2(double** matrix, std::vector<double>& headers, std::vector<double>&labels) {
	int rows = labels.size();
	int cols = headers.size();
	// first header is 'p' correlation.  This is not in headers.
	std::cout << "\tp\t";
	for (int i = 0; i < headers.size(); ++i) {
		cout << oFmt(8, 0) << "X=" << (int)headers[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < rows; ++i) {
		cout << oFmt(10, 6) << labels[i] << "\t";
		for (int j = 0; j < cols; ++j) {
			cout << oFmt(10, 6) << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}
template< typename T>
void print_2Dmatrix(T& matrix, std::vector<double>& headers, std::vector<double>&labels) {
	int rows = sizeof matrix / sizeof matrix[0];   
	int cols = sizeof matrix[0] / sizeof(double); 
	// first header is 'p' correlation.  This is not in headers.
	std::cout << "\tp\t";
	for (int i = 0; i < headers.size(); ++i) {
		cout << oFmt(8, 0) << "X=" << (int)headers[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < rows; ++i) {
		cout << oFmt(10, 6) << labels[i] << "\t";
		for (int j = 0; j < cols; ++j) {
			cout << oFmt(10, 6) << ((double*)matrix)[i*cols + j] << "\t";
		}
		cout << endl;
	}
}
// prints a single row w/o headers or y axis labels
template< typename T>
void print_matrix_row(T* matrix, int row, int cols) {
	for (int j = 0; j < cols; ++j) {
		cout << FFmt(8, 4) << matrix[row*cols + j] << "\t";
	}
	cout << endl;
}
// prints a single column w/o headers or y axis labels
template< typename T>
void print_matrix_col(T* matrix, int rows, int col) {
	for (int i = 0; i < rows; ++i) {
		cout << FFmt(8, 4) << matrix[i*rows + col] << "\t" << endl;
	}
}