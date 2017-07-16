/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:30:15 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/15 12:54:34 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				fill_inter_cone(t_light *light, t_cone *cone,
		t_inter *inter, t_ray *view)
{
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
	dot_sub(&local_dir, &local_hei, &cone->norm);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&cone->norm, &cone->norm);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&cone->norm, &norm_dir);
	inter->shape = cone->col.i;
	inter->col.i = put_col(light, inter, &cone->col);
	inter->dist_min = cone->dist;
}

int					is_cone(t_ray *view, t_cone *cone,
		t_light *light, t_inter *inter)
{
	t_ray		local;
	t_coor		x_ray;

	dot_sub(&view->origin, &cone->center, &local.origin);
	dot_sub(&view->origin, &cone->vertex, &x_ray);
	cone->a = dot_prod(&view->direction, &view->direction) -
		(1 + pow(cone->angle, 2)) *
		pow(dot_prod(&view->direction, &cone->hei), 2);
	cone->b = 2 * (dot_prod(&view->direction, &x_ray) -
		(1 + pow(cone->angle, 2)) *
		dot_prod(&view->direction, &cone->hei) *
		dot_prod(&x_ray, &cone->hei));
	cone->c = dot_prod(&x_ray, &x_ray) - (1 + pow(cone->angle, 2)) *
		pow(dot_prod(&x_ray, &cone->hei), 2);
	if ((cone->delt = pow(cone->b, 2) - 4 * cone->a * cone->c) < 0)
		return (cone->dist = 0);
	cone->hit_1 = (-cone->b - sqrt(cone->delt)) / (2 * cone->a);
	cone->hit_2 = (-cone->b + sqrt(cone->delt)) / (2 * cone->a);
	cone->dist = smallest_non_negativ(cone->hit_1, cone->hit_2);
	if (cone->dist <= 0)
		return (cone->dist = 0);
	if (cone->dist < inter->dist_min)
		fill_inter_cone(light, cone, inter, view);
	return (cone->dist);
}

double				shad_cone(t_ray *view, t_cone *cone)
{
	t_ray		local;
	t_coor		x_ray;
	double		local_dist;

	dot_sub(&view->origin, &cone->center, &local.origin);
	dot_sub(&view->origin, &cone->vertex, &x_ray);
	cone->a = dot_prod(&view->direction, &view->direction) -
		(1 + pow(cone->angle, 2)) *
		pow(dot_prod(&view->direction, &cone->hei), 2);
	cone->b = 2 * (dot_prod(&view->direction, &x_ray) -
		(1 + pow(cone->angle, 2)) *
		dot_prod(&view->direction, &cone->hei) *
		dot_prod(&x_ray, &cone->hei));
	cone->c = dot_prod(&x_ray, &x_ray) - (1 + pow(cone->angle, 2)) *
		pow(dot_prod(&x_ray, &cone->hei), 2);
	if ((cone->delt = pow(cone->b, 2) - 4 * cone->a * cone->c) < 0)
		return (cone->dist = 0);
	cone->hit_1 = (-cone->b - sqrt(cone->delt)) / (2 * cone->a);
	cone->hit_2 = (-cone->b + sqrt(cone->delt)) / (2 * cone->a);
	local_dist = smallest_non_negativ(cone->hit_1, cone->hit_2);
	if (local_dist < 0 || local_dist > 1)
		return (cone->dist = 0);
	return (local_dist);
}

void				closest_cone(t_list *cones, t_env *e)
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

double				check_shadow_cone(t_list *cones, t_env *e)
{
	t_list			*lst;
	t_cone			*actual;

	lst = cones;
	while (lst)
	{
		actual = lst->content;
		if (shad_cone(&e->inter.ray, actual))
			return (1);
		lst = lst->next;
	}
	return (0);
}
