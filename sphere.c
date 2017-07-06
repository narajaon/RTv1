#include "rtv1.h"

void			fill_inter_sphere(t_light *light, t_sphere *sphere,
		t_inter *inter, t_ray *view)
{
	t_coor		norm_sphere;
	t_coor		norm_dir;
	t_coor		view_norm;

	point_on_ray(&view->origin, &view->direction,
			&inter->ray.origin, sphere->dist);
	dot_sub(&inter->ray.origin, &sphere->coord, &norm_sphere);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&norm_sphere, &norm_sphere);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_sphere, &norm_dir);
	inter->col.i = put_col(light, inter, &sphere->col);
	inter->shape = SPHERE;
	inter->dist_min = sphere->dist;
}

int				is_sphere(t_ray *view, t_sphere *sphere,
		t_light *light, t_inter *inter)
{
	double		a;
	double		b;
	double		c;
	double		delt;
	t_ray		local;
	t_coor		norm_dir;

	dot_sub(&view->origin, &sphere->coord, &local.origin);
	a = vect_pow(&view->direction);
	b = 2 * (dot_prod(&view->direction, &local.origin));
	c = vect_pow(&local.origin) - pow(sphere->r, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (sphere->dist = 0);
	sphere->hit_1 = (-b - sqrt(delt)) / (2 * a);
	sphere->hit_2 = (-b + sqrt(delt)) / (2 * a);
	sphere->dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
	if (sphere->dist < 0)
		return (sphere->dist = 0);
	if (sphere->dist < inter->dist_min)
		fill_inter_sphere(light, sphere, inter, view);
	return (sphere->dist);
}

double			shad_sphere(t_ray *view, t_sphere *sphere,
		t_light *light)
{
	double		a;
	double		b;
	double		c;
	double		delt;
	double		local_dist;
	t_ray		local;
	t_coor		norm_dir;

	dot_sub(&view->origin, &sphere->coord, &local.origin);
	a = vect_pow(&view->direction);
	b = 2 * (dot_prod(&view->direction, &local.origin));
	c = vect_pow(&local.origin) - pow(sphere->r, 2);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (sphere->dist = 0);
	sphere->hit_1 = (-b - sqrt(delt)) / (2 * a);
	sphere->hit_2 = (-b + sqrt(delt)) / (2 * a);
	local_dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
	//printf("shad dist %f\n", sphere->dist);
	if (local_dist < 0)
		return (local_dist = 0);
	//printf("sphere->dist %f\n", sphere->dist);
	return (local_dist);
}
