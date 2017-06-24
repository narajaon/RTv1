#include "rtv1.h"

int				check_shadow(t_inter *inter, t_light *light, int (*f)())
{
	return (1);
}

double			clamp_col(double col, double cos, double light)
{
	if (cos < 0)
		return (0);
	//if (col * cos > 255)
	//	return (cos * light);
	return (col * cos);
}

unsigned int	put_col_sphere(t_light *light, t_inter *inter, t_sphere *sphere)
{
	t_col		col;
	double		b;
	double		g;
	double		r;

	b = clamp_col(sphere->col.tab[0], inter->cos_alph, light->col.i) * 255;
	g = clamp_col(sphere->col.tab[1], inter->cos_alph, light->col.i) * 255;
	r = clamp_col(sphere->col.tab[2], inter->cos_alph, light->col.i) * 255;
	init_col(&inter->col, r, g, b);
	//printf("tab[0] %x b %f\n", sphere->col.tab[0], b);
	//printf("tab[1] %x g %f\n", sphere->col.tab[1], g);
	//printf("tab[2] %x r %f\n\n", sphere->col.tab[2], r);
	inter->col.i = mult_col(&inter->col, &light->col);
	//inter->col.i = mult_col(&inter->col, &light->col);
	return (col.i);
}

void			fill_inter_sphere(t_light *light, t_sphere *sphere,
		t_inter *inter, t_view *view)
{
	t_coor		norm_sphere;
	t_coor		norm_dir;
	t_coor		view_norm;

//	normalize(&view->ray.direction, &view_norm);
//
	point_on_ray(&view->ray.origin, &view->ray.direction,
			&inter->ray.origin, sphere->dist);
	dot_sub(&inter->ray.origin, &sphere->coord, &norm_sphere);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	//normalize(&inter->ray.direction, &norm_dir);
	//normalize(&norm_sphere, &norm_sphere);
	inter->cos_alph = dot_prod(&norm_sphere, &inter->ray.direction) /
		(vect_len(&inter->ray.direction) *
		vect_len(&norm_sphere));
	inter->col.i = put_col_sphere(light, inter, sphere);
	inter->shape = SPHERE;
	print_coord(&inter->ray.origin);
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
	b = 2 * (dot_prod(&local.direction, &local.origin));
	c = vect_pow(&local.origin) - pow(sphere->r, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (sphere->dist = 0);
	sphere->hit_1 = (-b - sqrt(delt)) / (2 * a);
	sphere->hit_2 = (-b + sqrt(delt)) / (2 * a);
	sphere->dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
//	printf("x %d y %d dist %f\n", pix->x, pix->y, sphere->dist);
	if (sphere->dist < 0)
		return (sphere->dist = 0);
	fill_inter_sphere(light, sphere, inter, view);
	printf("cos_alph %f\n", inter->cos_alph);
	//printf("k1 %f k2 %f\n\n", sphere->hit_1, sphere->hit_2);
	//printf("dist %f\n", sphere->dist);
	return (1);
}
