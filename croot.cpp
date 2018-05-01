#include <math.h>

//  sourforge gandalf.
#define M_PI 3.14159265358979323846
//  sourforge gandalf.
#define M_SQRT3 1.73205080756887719317
//  sourforge gandalf.
/// Structure definition for double precision complex number
typedef struct Gan_Complex
{
	/// Real part
	double r;
	/// Imaginary part
	double i;
} Gan_Complex, Gan_Complex_d;

/**
* \brief Real cube root function.
* \param x Input real value
* \return The cube root of \a x.
* sourforge gandalf
*
* Real cube root function.
*/
double
gan_cbrt(double x)
{
	return ((x>0.0) ? exp(log(x) / 3.0) : ((x<0.0) ? -exp(log(-x) / 3.0) : 0.0));
}
 

/**
* \brief Find roots of a quadratic equation with real coefficients.
* \param a The coeffient in \f$ x^2 \f$
* \param b The coeffient in \f$ x \f$
* \param c The scalar coeffient
* \param x The roots of the equation
* \return The number of roots, or -1 on error.
*
* Solve quadratic equation
* \f[
*   a\:x^2 + b\:x + c = 0
* \f]
* using method given in Numerical Recipes.
* sourforge gandalf.
*/
int
gan_solve_quadratic(double a, double b, double c, Gan_Complex x[2])
{
	double d;

	if (a == 0.0)
	{
		/* linear equation */
		if (b == 0.0)
		{
			if (c == 0.0)
			{
				return -1;
			}

			/* equation is c == 0 for non-zero c */
			return 0;
		}

		x[0].r = -c / b;
		x[0].i = 0.0;
		return 1;
	}

	if (b == 0.0)
	{
		/* simple case */
		if (c <= 0.0)
		{
			x[0].r = sqrt(-c / a);
			x[1].r = -x[0].r;
			x[0].i = x[1].i = 0.0;
		}
		else
		{
			x[0].r = x[1].r = 0.0;
			x[0].i = sqrt(c / a);
			x[1].i = -x[0].i;
		}

		return 2;
	}

	/* compute discriminant */
	d = b*b - 4.0*a*c;

	if (d > 0.0)
	{
		double q;

		/* positive discriminant: two real roots */
		q = (b > 0.0) ? -0.5*(b + sqrt(d)) : -0.5*(b - sqrt(d));
		x[0].r = q / a;
		x[1].r = c / q;
		x[0].i = x[1].i = 0.0;
	}
	else
	{
		double qr, qi, q2;

		/* negative discriminant: two complex roots */
		qr = -0.5*b;
		if (b > 0.0)
			qi = -0.5*sqrt(-d);
		else
			qi = 0.5*sqrt(-d);

		x[0].r = qr / a;
		x[0].i = qi / a;
		q2 = qr*qr + qi*qi;
		x[1].r = c*qr / q2;
		x[1].i = -c*qi / q2;
	}

	return 2;
}
/**
* \brief Find roots of a cubic equation with real coefficients.
* \param a The coeffient in \f$ x^3 \f$
* \param b The coeffient in \f$ x^2 \f$
* \param c The coeffient in \f$ x \f$
* \param d The scalar coeffient
* \param x The roots of the equation
* \return The number of roots, or -1 on error.
*
* Solve cubic equation
* \f[
*    a\:x^3 + b\:x^2 + c\:x + d = 0
* \f]
* using method given in Numerical Recipes.
*
* sourforge gandalf.  amended by Nick Ferguson to fit Haug's CRoot type eval for a return
*/
 
double
gan_solve_cubic(double a, double b, double c, double d)
{
	double Q, Rp, Q3;
	Gan_Complex x[3];

	if (a == 0.0)
	{
		Gan_Complex xq[2];
		int qn, i;

		/* solve quadratic */
		qn = gan_solve_quadratic(b, c, d, xq);
		for (i = qn - 1; i >= 0; i--)
		{
			x[i].r = xq[i].r;
			x[i].i = xq[i].i;
		}

	//	return qn; // let this process fall through to end.
	}
	else 
	
	{
		if (a != 1.0)
		{
			b /= a;
			c /= a;
			d /= a;
		}

		Q = (b*b - 3.0*c) / 9.0;
		Rp = (2.0*b*b*b - 9.0*b*c + 27.0*d) / 54.0;
		Q3 = Q*Q*Q;
		if (Rp*Rp < Q3)
		{
			double t, Qr2m, b3 = b / 3.0;

			/* real roots */
			t = acos(Rp / sqrt(Q3));
			Qr2m = -2.0*sqrt(Q);
			x[0].r = Qr2m*cos(t / 3.0) - b3;
			x[1].r = Qr2m*cos((t + 2.0*M_PI) / 3.0) - b3;
			x[2].r = Qr2m*cos((t - 2.0*M_PI) / 3.0) - b3;

			/* set imaginary components to zero */
			x[0].i = x[1].i = x[2].i = 0.0;
		}
		else
		{
			/* one real and two complex roots */
			double A, B;

			A = (Rp > 0) ? -gan_cbrt(fabs(Rp) + sqrt(Rp*Rp - Q3))
				: gan_cbrt(fabs(Rp) + sqrt(Rp*Rp - Q3));
			B = (A == 0.0) ? 0.0 : Q / A;
			x[0].r = (A + B) - b / 3.0;
			x[0].i = 0.0;
			x[1].r = -0.5*(A + B) - b / 3.0;
			x[1].i = 0.5*M_SQRT3*(A - B);
			x[2].r = x[1].r;
			x[2].i = -x[1].i;
		}
	}
	// added code by Nick Ferguson
	double ret;
	if (x[0].r > 0)
		ret =x[0].r;
	else if (x[1].r > 0)
		ret = x[1].r;
	else if (x[2].r > 0)
		ret = x[2].r;

	if (x[1].r > 0 && x[1].r < ret)
		ret = x[1].r;
	if (x[2].r > 0 && x[2].r < ret)
		ret = x[2].r;

	return ret;
}
// From Haug's book
double ArcCos(double y)
{

	return atan(-y / sqrt(-y * y + 1)) + 2 * atan(1);

}

int sgn(double num)
{
	if (num > 0)
		return 1;
	else if (num == 0)
		return 0;
	else if(num < 0)
		return -1;


}
// from haug book.  but has issues, when rho = 0.  Instead used some functions from sourforge gandalf
double CRoot(double cubic, double quadratic, double linear, double constant, double rho)
{

	double roots[3];
	double a, b, C;
	double r, Q;
	double capA, capB, theta;
	double ret = 0;

	a = quadratic / cubic;
	b = linear / cubic;
	C = constant / cubic;
	Q = (pow(a, 2) - 3 * b) / 9;
	r = (2 * pow(a, 3) - 9 * a * b + 27 * C) / 54;

	if ((pow(r, 2) - pow(Q, 3)) >= 0)
	{
		capA = -sgn(r) * (fabs(r) + pow(sqrt(pow(r, 2) - pow(Q, 3)),( 1 / 3)));
		if (capA == 0)
			capB = 0;
		else
			capB = Q / capA;
		ret = capA + capB - a / 3;
	}
	else
	{
		theta = ArcCos(r / pow(Q, 1.5));
		roots[0] = -2 * sqrt(Q) * cos(theta / 3) - a / 3;
		roots[1] = -2 * sqrt(Q) * cos(theta / 3 + 2.0943951023932) - a / 3;
		roots[2] = -2 * sqrt(Q) * cos(theta / 3 - 2.0943951023932) - a / 3;

		if (roots[0] > 0)
			ret = roots[0];
		else if (roots[1] > 0)
			ret = roots[1];
		else if(roots[2] > 0)
			ret = roots[2];

		if (roots[1] > 0 && roots[1] < ret)
			ret = roots[1];
		if (roots[2] > 0 && roots[2] < ret)
			ret = roots[3];

	}

	return ret;

}