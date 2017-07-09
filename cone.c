#include "rtv1.h"

void			fill_inter_cone(t_light *light, t_cone *cone,
		t_inter *inter, t_ray *view)
{
	t_coor		norm_cone;
	t_coor		norm_dir;
	t_coor		local_dir;
	t_coor		local_hei;
	t_coor		x_ray;
	double		m_dist;

	dot_sub(&view->origin, &cone->vertex, &x_ray);
	m_dist = dot_prod(&view->direction, &cone->hei) * cone->dist +
		dot_prod(&x_ray, &cone->hei);
	point_on_ray(&view->origin, &view->direction,
			&inter->ray.origin, cone->dist);
	dot_sub(&inter->ray.origin, &cone->vertex, &local_dir);
	dot_mult(&cone->hei, &local_hei, (1 + pow(cone->angle, 2)) * m_dist);
	dot_sub(&local_dir, &local_hei, &norm_cone);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&norm_cone, &norm_cone);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_cone, &norm_dir);
	inter->shape = cone->col.i;
	inter->col.i = put_col(light, inter, &cone->col);
	inter->dist_min = cone->dist;
}

int				is_cone(t_ray *view, t_cone *cone,
		t_light *light, t_inter *inter)
{
	double		a;
	double		b;
	double		c;
	double		delt;
	t_ray		local;
	t_coor		x_ray;

	dot_sub(&view->origin, &cone->center, &local.origin);
	dot_sub(&view->origin, &cone->vertex, &x_ray);
	a = dot_prod(&view->direction, &view->direction) -
		(1 + pow(cone->angle, 2)) *
		pow(dot_prod(&view->direction, &cone->hei), 2);
	b = 2 * (dot_prod(&view->direction, &x_ray) -
		(1 + pow(cone->angle, 2)) *
		dot_prod(&view->direction, &cone->hei) *
		dot_prod(&x_ray, &cone->hei));
	c = dot_prod(&x_ray, &x_ray) - (1 + pow(cone->angle, 2)) *
		pow(dot_prod(&x_ray, &cone->hei), 2);
//	printf("a %f b %f c %f\n", a, b, c);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (cone->dist = 0);
	//printf("delt %f\n", delt);
	cone->hit_1 = (-b - sqrt(delt)) / (2 * a);
	cone->hit_2 = (-b + sqrt(delt)) / (2 * a);
	cone->dist = smallest_non_negativ(cone->hit_1, cone->hit_2);
	//printf("dist %f\n", cone->dist);
	if (cone->dist < 0)
		return (cone->dist = 0);
	if (cone->dist < inter->dist_min)
		fill_inter_cone(light, cone, inter, view);
	return (cone->dist);
}

double				shad_cone(t_ray *view, t_cone *cone,
		t_light *light)
{
	double		a;
	double		b;
	double		c;
	double		delt;
	t_ray		local;
	t_coor		x_ray;
	double		local_dist;

	dot_sub(&view->origin, &cone->center, &local.origin);
	dot_sub(&view->origin, &cone->vertex, &x_ray);
	a = dot_prod(&view->direction, &view->direction) -
		(1 + pow(cone->angle, 2)) *
		pow(dot_prod(&view->direction, &cone->hei), 2);
	b = 2 * (dot_prod(&view->direction, &x_ray) -
		(1 + pow(cone->angle, 2)) *
		dot_prod(&view->direction, &cone->hei) *
		dot_prod(&x_ray, &cone->hei));
	c = dot_prod(&x_ray, &x_ray) - (1 + pow(cone->angle, 2)) *
		pow(dot_prod(&x_ray, &cone->hei), 2);
	if ((delt = pow(b, 2) - 4 * a * c) < 0)
		return (cone->dist = 0);
	cone->hit_1 = (-b - sqrt(delt)) / (2 * a);
	cone->hit_2 = (-b + sqrt(delt)) / (2 * a);
	local_dist = smallest_non_negativ(cone->hit_1, cone->hit_2);
	if (local_dist < 0 || local_dist > 1)
		return (cone->dist = 0);
	return (local_dist);
}

void		closest_cone(t_list *cones, t_env *e)
{
	t_list		*lst;
	t_cone		*actual;

	lst = cones;
	while (lst)
	{
		actual = lst->content;
		is_cone(&e->view.ray, actual, &e->light, &e->inter);
		lst = lst->next;
	}
}

double		check_shadow_cone(t_list *cones, t_env *e)
{
	t_list			*lst;
	t_cone			*actual;
	int				col;

	lst = cones;
	while (lst)
	{
		actual = lst->content;
		if (shad_cone(&e->inter.ray, actual, &e->light))
			return (1);
		lst = lst->next;
	}
	return (0);
}
