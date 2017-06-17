#include "rtv1.h"

void	rot_x(double *x, double *y, double *z, double angle)
{
	double		tmpx;
	double		tmpy;
	double		tmpz;

	tmpx = *x;
	tmpy = cos(angle) * *y - sin(angle) * *z;
	tmpy = sin(angle) * *y + cos(angle) * *z;
	*x = tmpx;
	*y = tmpy;
	*z = tmpz;
}

void	rot_y(double *x, double *y, double *z, double angle)
{
	double		tmpx;
	double		tmpy;
	double		tmpz;

	tmpx = cos(angle) * *x + sin(angle) * *z;
	tmpy = *y;
	tmpz = -sin(angle) * *x + cos(angle) * *z;
	*x = tmpx;
	*y = tmpy;
	*z = tmpz;
}

void	rot_z(double *x, double *y, double *z, double angle)
{
	double		tmpx;
	double		tmpy;
	double		tmpz;

	tmpx = cos(angle) * *x - sin(angle) * *y;
	tmpy = sin(angle) * *x + cos(angle) * *y;
	tmpz = *z;
	*x = tmpx;
	*y = tmpy;
	*z = tmpz;
}
