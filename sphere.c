#include "rtv1.h"

int				check_shadow(t_inter *inter, t_light *light, int (*f)())
{
	return (1);
}

unsigned int	put_col_sphere(t_light *light, t_inter *inter, t_sphere *sphere)
{
	double		b;
	double		g;
	double		r;

	b = clamp_col(sphere->col.tab[0], inter->cos_alph, light->col.tab[0]) * 255;
	g = clamp_col(sphere->col.tab[1], inter->cos_alph, light->col.tab[1]) * 255;
	r = clamp_col(sphere->col.tab[2], inter->cos_alph, light->col.tab[2]) * 255;
	init_col(&inter->col, r, g, b);
	inter->col.i = mult_col(&inter->col, &light->col);
	return (inter->col.i);
}

void			fill_inter_sphere(t_light *light, t_sphere *sphere,
		t_inter *inter, t_view *view)
{
	t_coor		norm_sphere;
	t_coor		norm_dir;
	t_coor		view_norm;

	point_on_ray(&view->ray.origin, &view->ray.direction,
			&inter->ray.origin, sphere->dist);
	dot_sub(&inter->ray.origin, &sphere->coord, &norm_sphere);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&norm_sphere, &norm_sphere);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_sphere, &norm_dir);
	inter->col.i = put_col_sphere(light, inter, sphere);
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
	t_coor		norm_dir;

	dot_sub(&view->ray.origin, &sphere->coord, &local.origin);
	a = vect_pow(&view->ray.direction);
	b = 2 * (dot_prod(&view->ray.direction, &local.origin));
	c = vect_pow(&local.origin) - pow(sphere->r, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (sphere->dist = 0);
	sphere->hit_1 = (-b - sqrt(delt)) / (2 * a);
	sphere->hit_2 = (-b + sqrt(delt)) / (2 * a);
	sphere->dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
	if (sphere->dist < 0)
		return (sphere->dist = 0);
	return (sphere->dist);
}
