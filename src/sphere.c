/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:31:40 by narajaon          #+#    #+#             */
/*   Updated: 2018/01/31 14:58:40 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void			fill_inter_sphere(t_light *light, t_sphere *sphere,
		t_inter *inter, t_ray *view)
{
	t_coor		norm_sphere;
	t_coor		norm_dir;

	point_on_ray(&view->origin, &view->direction,
			&inter->ray.origin, sphere->dist);
	dot_sub(&inter->ray.origin, &sphere->coord, &norm_sphere);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&norm_sphere, &norm_sphere);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_sphere, &norm_dir);
	inter->shape = sphere->col.i;
	inter->col.i = put_col(light, inter, &sphere->col);
	inter->dist_min = sphere->dist;
}

int				is_sphere(t_ray *view, t_sphere *sphere,
		t_light *light, t_inter *inter)
{
	t_ray		local;

	dot_sub(&view->origin, &sphere->coord, &local.origin);
	sphere->a = vect_pow(&view->direction);
	sphere->b = 2 * (dot_prod(&view->direction, &local.origin));
	sphere->c = vect_pow(&local.origin) - pow(sphere->r, 2);
	if ((sphere->delt = pow(sphere->b, 2) - 4 * sphere->a * sphere->c) < 0)
		return (sphere->dist = 0);
	sphere->hit_1 = (-sphere->b - sqrt(sphere->delt)) / (2 * sphere->a);
	sphere->hit_2 = (-sphere->b + sqrt(sphere->delt)) / (2 * sphere->a);
	sphere->dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
	if (sphere->dist <= 0)
		return (sphere->dist = 0);
	if (sphere->dist < inter->dist_min)
		fill_inter_sphere(light, sphere, inter, view);
	return (sphere->dist);
}

double			shad_sphere(t_ray *view, t_sphere *sphere)
{
	double		local_dist;
	t_ray		local;

	dot_sub(&view->origin, &sphere->coord, &local.origin);
	sphere->a = vect_pow(&view->direction);
	sphere->b = 2 * (dot_prod(&view->direction, &local.origin));
	sphere->c = vect_pow(&local.origin) - pow(sphere->r, 2);
	if ((sphere->delt = pow(sphere->b, 2) - 4 * sphere->a * sphere->c) < 0)
		return (sphere->dist = 0);
	sphere->hit_1 = (-sphere->b - sqrt(sphere->delt)) / (2 * sphere->a);
	sphere->hit_2 = (-sphere->b + sqrt(sphere->delt)) / (2 * sphere->a);
	local_dist = smallest_non_negativ(sphere->hit_1, sphere->hit_2);
	if (local_dist < 0 || local_dist > 1)
		return (local_dist = 0);
	return (local_dist);
}

void			closest_sphere(t_list *spheres, t_env *e)
{
	t_list		*lst;
	t_sphere	*actual;

	lst = spheres;
	while (lst)
	{
		actual = lst->content;
		is_sphere(&e->view.ray, actual, &e->light, &e->inter);
		lst = lst->next;
	}
}

double			check_shadow_sphere(t_list *spheres, t_env *e)
{
	t_list			*lst;
	t_sphere		*actual;

	lst = spheres;
	while (lst)
	{
		actual = lst->content;
		if (shad_sphere(&e->inter.ray, actual))
			return (1);
		lst = lst->next;
	}
	return (0);
}
