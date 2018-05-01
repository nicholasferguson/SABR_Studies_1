#pragma once

#include <vector>

std::vector<double> roots(double *a);
void rootsX(double *a, int n, double *wr, double *wi, int* numr);
int roots2(double *a, int n, double *wr, double *wi);
void deflate(double *a, int n, double *b, double *quad, double *err);
void find_quad(double *a, int n, double *b, double *quad, double *err, int *iter);
void diff_poly(double *a, int n, double *b);
void recurse(double *a, int n, double *b, int m, double *quad,	double *err, int *iter);
void get_quads(double *a, int n, double *quad, double *x);
