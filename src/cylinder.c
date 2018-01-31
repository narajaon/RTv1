/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:30:35 by narajaon          #+#    #+#             */
/*   Updated: 2018/01/31 14:56:38 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void			fill_inter_cyli(t_light *light, t_cyli *cyli,
		t_inter *inter, t_ray *view)
{
	t_coor		norm_cyli;
	t_coor		norm_dir;
	t_coor		local_dir;
	t_coor		local_hei;

	point_on_ray(&view->origin, &view->direction,
			&inter->ray.origin, cyli->dist);
	dot_sub(&inter->ray.origin, &cyli->center, &local_dir);
	vect_project(&local_dir, &cyli->hei, &local_hei);
	dot_sub(&local_dir, &local_hei, &norm_cyli);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&norm_cyli, &norm_cyli);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_cyli, &norm_dir);
	inter->shape = cyli->col.i;
	inter->col.i = put_col(light, inter, &cyli->col);
	inter->dist_min = cyli->dist;
}

int				is_cyli(t_ray *view, t_cyli *cyli,
		t_light *light, t_inter *inter)
{
	t_ray		local;
	t_coor		x_ray;

	dot_sub(&view->origin, &cyli->center, &local.origin);
	dot_sub(&view->origin, &cyli->cap_u, &x_ray);
	cyli->a = dot_prod(&view->direction, &view->direction) -
		pow(dot_prod(&view->direction, &cyli->hei), 2);
	cyli->b = 2 * (dot_prod(&view->direction, &x_ray) -
		dot_prod(&view->direction, &cyli->hei) *
		dot_prod(&x_ray, &cyli->hei));
	cyli->c = dot_prod(&x_ray, &x_ray) -
		pow(dot_prod(&x_ray, &cyli->hei), 2) - pow(cyli->r, 2);
	if ((cyli->delt = pow(cyli->b, 2) - 4 * cyli->a * cyli->c) < 0)
		return (cyli->dist = 0);
	cyli->hit_1 = (-cyli->b - sqrt(cyli->delt)) / (2 * cyli->a);
	cyli->hit_2 = (-cyli->b + sqrt(cyli->delt)) / (2 * cyli->a);
	cyli->dist = smallest_non_negativ(cyli->hit_1, cyli->hit_2);
	if (cyli->dist <= 0)
		return (cyli->dist = 0);
	if (cyli->dist < inter->dist_min)
		fill_inter_cyli(light, cyli, inter, view);
	return (cyli->dist);
}

double			shad_cyli(t_ray *view, t_cyli *cyli)
{
	t_ray		local;
	t_coor		x_ray;
	double		local_dist;

	dot_sub(&view->origin, &cyli->center, &local.origin);
	dot_sub(&view->origin, &cyli->cap_u, &x_ray);
	cyli->a = dot_prod(&view->direction, &view->direction) -
		pow(dot_prod(&view->direction, &cyli->hei), 2);
	cyli->b = 2 * (dot_prod(&view->direction, &x_ray) -
		dot_prod(&view->direction, &cyli->hei) *
		dot_prod(&x_ray, &cyli->hei));
	cyli->c = dot_prod(&x_ray, &x_ray) -
		pow(dot_prod(&x_ray, &cyli->hei), 2) - pow(cyli->r, 2);
	if ((cyli->delt = pow(cyli->b, 2) - 4 * cyli->a * cyli->c) < 0)
		return (cyli->dist = 0);
	cyli->hit_1 = (-cyli->b - sqrt(cyli->delt)) / (2 * cyli->a);
	cyli->hit_2 = (-cyli->b + sqrt(cyli->delt)) / (2 * cyli->a);
	local_dist = smallest_non_negativ(cyli->hit_1, cyli->hit_2);
	if (local_dist < 0 || local_dist > 1)
		return (local_dist = 0);
	return (local_dist);
}

void			closest_cylinder(t_list *cylinders, t_env *e)
{
	t_list		*lst;
	t_cyli		*actual;

	lst = cylinders;
	while (lst)
	{
		actual = lst->content;
		is_cyli(&e->view.ray, actual, &e->light, &e->inter);
		lst = lst->next;
	}
}

double			check_shadow_cylinder(t_list *cylinders, t_env *e)
{
	t_list			*lst;
	t_cyli			*actual;

	lst = cylinders;
	while (lst)
	{
		actual = lst->content;
		if (shad_cyli(&e->inter.ray, actual))
			return (1);
		lst = lst->next;
	}
	return (0);
}
