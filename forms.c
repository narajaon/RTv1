#include "rtv1.h"

void	is_plan(t_env *e)
{
	e->plan.k = -(e->view.coord.z) / (e->prim.coord.z);
}

void	is_sphere(t_env *e)
{
	double		delt;
	double		k1;
	double		k2;

	e->sphere.a = pow(e->prim.coord.x, 2) + pow(e->prim.coord.y, 2) + pow(e->prim.coord.z, 2);
	e->sphere.b = 2 * (e->view.coord.x * e->prim.coord.x + e->view.coord.y * e->prim.coord.y + e->view.coord.z * e->prim.coord.z);
	e->sphere.c = pow(e->view.coord.x, 2) + pow(e->view.coord.y, 2) + pow(e->view.coord.z, 2) - pow(e->sphere.r, 2);
	delt = pow(e->sphere.b, 2) - 4 * e->sphere.a * e->sphere.c;
	if (delt >= 0.00001)
	{
		k1 = (-e->sphere.b + sqrt(delt)) / 2 * e->sphere.a;
		k2 = (-e->sphere.b - sqrt(delt)) / 2 * e->sphere.a;
		e->sphere.k = (k1 < k2) ? k1 : k2;
		if (e->pix.coord.x == WIN_X / 2 && e->pix.coord.y == WIN_Y / 2)
			printf("k1 %f k2 %f\nsphere %f plan %f\n", k1, k2, e->sphere.k, e->plan.k);
		/*init shadow r.coord.y here*/
	}
	else
		e->sphere.k = 0;
}
