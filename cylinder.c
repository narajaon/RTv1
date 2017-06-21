#include "rtv1.h"

int		is_cyli(t_view *view, t_cyli *cyli, t_pix *pix)
{
	float		a;
	float		b;
	float		c;
	float		delt;
	float		m;
	t_ray		tmp;
	//t_coor		n;

	//normalize(&cyli->cap, &n);
	dot_cpy(&view->ray.origin, &tmp.origin);
	dot_cpy(&view->ray.direction, &tmp.direction);
	dot_sub(&tmp.origin, &cyli->cap, &tmp.origin);
	dot_sub(&tmp.direction, &cyli->cap, &tmp.direction);
	a = pow(tmp.direction.x, 2) + pow(tmp.direction.z, 2);
	b = 2 * (tmp.origin.x * tmp.direction.x + tmp.origin.z * tmp.direction.z);
	c = pow(tmp.direction.x, 2) + pow(tmp.direction.z, 2) - pow(cyli->r, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < -RAY_MIN)
		return (0);
	cyli->hit_1 = (-b - sqrt(delt)) / (2 * a);
	cyli->hit_2 = (-b + sqrt(delt)) / (2 * a);
	cyli->dist = smallest_non_negativ(cyli->hit_1, cyli->hit_2);
	if (pix->x == WIN_X / 2 && pix->y == WIN_Y / 2)
	{
//		printf("cyli %f\n", cyli->dist);
	}
	if (cyli->dist < 1 && fabs(cyli->dist) < RAY_MIN)
		return (cyli->dist = 0);
	return (1);
}
