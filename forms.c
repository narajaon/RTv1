#include "rtv1.h"

void	is_plan(t_env *e)
{
	t_coor		x;
	t_coor		v;
	double		xv;
	double		dv;

	dot_sub(&e->plan.coord, &e->view.coord, &x);
	vect_norm(&e->plan.coord, &v, vect_len(&e->plan.coord));
//	dot_mult(&x, &x, -1);
	xv = dot_prod(&x, &v);
	dv = dot_prod(&e->prim.coord, &v);
	if ((dv > 0.00001 && xv > 0.00001) || (dv < -0.00001 && xv < -0.00001))
	{
		dot_cpy(&e->plan.coord, &e->plan.hit);
		e->plan.k = -xv / dv;
	}
//		printf("sphere %f plan %f\n", e->sphere.k, e->plan.k);
}

void	is_sphere(t_env *e)
{
	t_coor		xv;
	double		a;
	double		b;
	double		c;

	dot_sub(&e->sphere.coord, &e->view.coord, &xv);
	a = dot_prod(&e->prim.coord, &e->prim.coord);
	b = 2 * (dot_prod(&e->prim.coord, &xv));
	c = dot_prod(&xv, &xv) - pow(e->sphere.r, 2);
	e->sphere.delt = pow(b, 2) - 4 * a * c;
//	printf("x %fy %f z %f\n", xv.x, xv.y, xv.z);
	if (e->sphere.delt >= 0.00001)
	{
		e->sphere.k1 = (-b + sqrt(e->sphere.delt)) / 2 * a;
		e->sphere.k2 = (-b - sqrt(e->sphere.delt)) / 2 * a;
		e->sphere.k = (e->sphere.k1 < e->sphere.k2) ? e->sphere.k1 : e->sphere.k2;
		if (e->pix.coord.x == WIN_X / 2 && e->pix.coord.y == WIN_Y / 2)
			printf("k1 %f k2 %f\nsphere %f plan %f\n", e->sphere.k1, e->sphere.k2, e->sphere.k, e->plan.k);
	}
	else
		e->sphere.k = 0;
	dot_cpy(&e->sphere.coord, &e->sphere.hit);
}
