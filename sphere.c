#include "rtv1.h"

int				check_shadow(t_inter *inter, t_light *light, int (*f)())
{
	return (1);
}

unsigned int	put_col(t_light *light, t_inter *inter, t_sphere *sphere)
{
	t_col		col;
	float		b;
	float		g;
	float		r;

	b = pow(sphere->col.tab[0] * inter->cos_alph, 2.2) * 255;
	g = pow(sphere->col.tab[1] * inter->cos_alph, 2.2) * 255;
	r = pow(sphere->col.tab[2] * inter->cos_alph, 2.2) * 255;
	init_col(&inter->col, r, g, b);
//	inter->col.i = mult_col(&inter->col, &light->col);
	return (col.i);
}

void			fill_inter_sphere(t_light *light, t_sphere *sphere,
		t_inter *inter, t_view *view)
{
	t_coor		norm_ori;
	t_coor		norm_dir;

	point_on_ray(&view->ray.origin, &view->ray.direction, &inter->ray.origin,
			sphere->dist);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&inter->ray.origin, &norm_ori);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_ori, &norm_dir);
//	printf("norm ");
//	printf("ori ");
//	print_coord(&inter->ray.origin);
//	printf("cos_alph %f\n", inter->cos_alph);
	//inter->cos_alph = 1 - inter->cos_alph;
	inter->col.i = put_col(light, inter, sphere);
//	printf("col %d\n", inter->col.i);
	inter->shape = SPHERE;
}

int				is_sphere(t_view *view, t_sphere *sphere,
		t_light *light, t_inter *inter)
{
	double		a;
	double		b;
	double		c;
	double		delt;
	t_ray		local;

	dot_sub(&view->ray.origin, &sphere->coord, &local.origin);
	dot_sub(&view->ray.direction, &sphere->coord, &local.direction);
	a = vect_pow(&local.direction);
	//a = dot_prod(&view->ray.direction, &view->ray.direction);
	b = 2 * (dot_prod(&local.direction, &local.origin));
	c = vect_pow(&local.origin) - pow(sphere->r, 2);
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
	if (sphere->dist < 0)
		return (sphere->dist = 0);
	fill_inter_sphere(light, sphere, inter, view);
	return (1);
}
