#include "rtv1.h"

int				check_shadow(t_inter *inter, t_light *light, int (*f)())
{
	return (1);
}

unsigned int	put_col(t_light *light, t_inter *inter, t_col col)
{
	//col.tab[0] *= inter->cos_alph;
	//col.tab[1] *= inter->cos_alph;
//	col.tab[2] = inter->cos_alph;
	//col.tab[3] *= inter->cos_alph;
//	col.i = col.i * inter->cos_alph / 255;
	return (col.i);
}

void			fill_inter_sphere(t_light *light, t_sphere *sphere,
		t_inter *inter, t_view *view)
{
	t_coor		norm;
	t_coor		tmp;

	normalize(&view->ray.direction, &norm);
	dot_mult(&norm, &tmp, sphere->dist); //dt
	dot_sum(&view->ray.origin, &tmp, &inter->ray.origin); //o + dt
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	//normalize(&inter->ray.origin, &inter->norm);
	inter->cos_alph = dot_prod(&inter->ray.origin, &inter->ray.direction) /
		vect_len(&inter->ray.origin) * vect_len(&inter->ray.direction);
//	printf("norm ");
//	print_coord(&inter->norm);
//	printf("ori ");
//	print_coord(&inter->ray.origin);
	printf("cos_alph %f\n", inter->cos_alph);
	inter->col.i = put_col(light, inter, sphere->col);
	inter->shape = SPHERE;
}

int				is_sphere(t_view *view, t_sphere *sphere,
		t_light *light, t_inter *inter)
{
	double		a;
	double		b;
	double		c;
	double		delt;
	t_ray		tmp;

	dot_cpy(&view->ray.origin, &tmp.origin);
	dot_cpy(&view->ray.direction, &tmp.direction);
	dot_sub(&view->ray.direction, &sphere->coord, &tmp.direction);
	dot_sub(&view->ray.origin, &sphere->coord, &tmp.origin);
//	printf("direction ");
	a = vect_pow(&tmp.origin);
	//a = dot_prod(&view->ray.direction, &view->ray.direction);
	b = 2 * (dot_prod(&tmp.origin, &tmp.direction));
	c = vect_pow(&tmp.direction) - pow(sphere->r, 2);
	//print_coord(&tmp.origin);
	//print_coord(&tmp.direction);
	//printf("a %f b %f c %f\n", a, b, c)
	//c = dot_prod(&tmp, &tmp) - pow(sphere->r, 2);
	//c = dot_prod(&tmp.direction, &tmp.direction) - pow(sphere->r, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (sphere->dist = 0);
	sphere->hit_1 = (-b - sqrt(delt)) / (2 * a);
	sphere->hit_2 = (-b + sqrt(delt)) / (2 * a);
	sphere->dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
//	printf("delt %f\n", delt);
//	printf("dist %f\n", sphere->dist);
//	printf("k1 %f k2 %f\n\n", sphere->hit_1, sphere->hit_2);
//	printf("x %d y %d dist %f\n", pix->x, pix->y, sphere->dist);
	/*need to check why there's a padding of 1 here*/
//	printf("dist %f\n", sphere->dist);
	if (sphere->dist < 0)
		return (sphere->dist = 0);
	fill_inter_sphere(light, sphere, inter, view);
	return (1);
}
