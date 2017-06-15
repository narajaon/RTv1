#include "rtv1.h"

void	is_plan(t_env *e)
{
	e->plan.k = -(e->view.z) / (e->prim.z);
}

void	is_sphere(t_env *e)
{
	double		delt;
	double		k1;
	double		k2;

	e->sphere.a = pow(e->prim.x, 2) + pow(e->prim.y, 2) + pow(e->prim.z, 2);
	e->sphere.b = 2 * (e->view.x * e->prim.x + e->view.y * e->prim.y + e->view.z * e->prim.z);
	e->sphere.c = pow(e->view.x, 2) + pow(e->view.y, 2) + pow(e->view.z, 2) - pow(e->sphere.r, 2);
	delt = pow(e->sphere.b, 2) - 4 * e->sphere.a * e->sphere.c;
	if (delt >= 0.00001)
	{
		k1 = (-e->sphere.b + sqrt(delt)) / 2 * e->sphere.a;
		k2 = (-e->sphere.b - sqrt(delt)) / 2 * e->sphere.a;
		e->sphere.k = (k1 < k2) ? k1 : k2;
		if (e->pix.x == WIN_X / 2 && e->pix.y == WIN_Y / 2)
			printf("k1 %f k2 %f\nsphere %f plan %f\n", k1, k2, e->sphere.k, e->plan.k);
		init_shad(e, e->sphere.col);
	}
	else
		e->sphere.k = 0;
}
