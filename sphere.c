#include "rtv1.h"

float	smallest_non_negativ(float a, float b)
{
	if (a > 0.00001 || b > 0.00001)
			return ((a > 0.00001) ? a : b);
	return (0);
}

int		is_sphere(t_view *view, t_sphere *sphere, t_pix *pix)
{
	float		a;
	float		b;
	float		c;
	float		delt;
	t_ray		tmp;

	dot_cpy(&view->ray.origin, &tmp.origin);
	dot_cpy(&view->ray.direction, &tmp.direction);
	dot_sub(&tmp.origin, &sphere->coord, &tmp.origin);
	dot_sub(&tmp.direction, &sphere->coord, &tmp.direction);
	a = vect_pow(&tmp.direction);
	b = 2 * (dot_prod(&tmp.origin, &tmp.direction));
	c = vect_pow(&tmp.direction) - pow(sphere->r, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < -0.00001)
		return (0);
	sphere->hit_1 = (-b - sqrt(delt)) / (2 * a);
	sphere->hit_2 = (-b + sqrt(delt)) / (2 * a);
	sphere->dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
//	printf("k1 %f k2 %f\n", sphere->hit_1, sphere->hit_2);
//	printf("dist %f\n", sphere->dist);

	/*need to check why there's a padding of 1 here*/

	if (sphere->dist < 1)
		return (sphere->dist = 0);
	return (1);
}
