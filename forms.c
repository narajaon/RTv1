#include "rtv1.h"

void	is_plan(t_env *e)
{
	t_coor		x;
	t_coor		v;
	double		xv;
	double		dv;

	dot_sub(&e->view.coord, &e->plan.coord, &x);
	vect_norm(&e->plan.coord, &v, vect_len(&e->plan.coord));
	//dot_mult(&x, &x, -1);
	xv = dot_prod(&x, &v);
	dv = dot_prod(&e->prim.coord, &v);
	if (fabs(dv) > 0.00001)
		e->plan.k = xv / dv;
}

void	is_sphere(t_env *e)
{
	double		a;
	double		b;
	double		c;

	a = pow(e->prim.coord.x, 2) + pow(e->prim.coord.y, 2) + pow(e->prim.coord.z, 2);
	b = 2 * (e->view.coord.x * e->prim.coord.x + e->view.coord.y * e->prim.coord.y + e->view.coord.z * e->prim.coord.z);
	c = pow(e->view.coord.x, 2) + pow(e->view.coord.y, 2) + pow(e->view.coord.z, 2) - pow(e->sphere.r, 2);
	e->sphere.delt = pow(b, 2) - 4 * a * c;
	if (e->sphere.delt >= 0.00001)
	{
		e->sphere.k1 = (-b + sqrt(e->sphere.delt)) / 2 * a;
		e->sphere.k2 = (-b - sqrt(e->sphere.delt)) / 2 * a;
		e->sphere.k = (e->sphere.k1 < e->sphere.k2) ? e->sphere.k1 : e->sphere.k2;
		if (e->pix.coord.x == WIN_X / 2 && e->pix.coord.y == WIN_Y / 2)
			printf("k1 %f k2 %f\nsphere %f plan %f\n", e->sphere.k1, e->sphere.k2, e->sphere.k, e->plan.k);
		/*init shadow r.coord.y here*/
	}
}
