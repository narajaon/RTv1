/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 13:48:11 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/13 15:23:31 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			fill_inter_plane(t_light *light, t_plane *plane,
		t_inter *inter, t_ray *view)
{
	t_coor		norm_plane;
	t_coor		norm_dir;
	t_coor		view_norm;
	double		dv;

	point_on_ray(&view->origin, &view->direction,
			&inter->ray.origin, plane->dist);
	dot_sub(&light->coord, &inter->ray.origin, &inter->ray.direction);
	normalize(&plane->norm, &norm_plane);
	dv = dot_prod(&view->direction, &norm_plane);
	normalize(&inter->ray.direction, &norm_dir);
	inter->cos_alph = dot_prod(&norm_plane, &norm_dir);
	inter->shape = plane->col.i;
	inter->col.i = put_col(light, inter, &plane->col);
	inter->dist_min = plane->dist;
}

int				is_plane(t_ray *view, t_plane *plane,
		t_light *light, t_inter *inter)
{
	double		dv;
	double		xv;
	double		t;
	t_coor		x_point;

	dot_sub(&plane->center, &view->origin, &x_point);
	dv = dot_prod(&view->direction, &plane->norm);
	if (dv > 0)
		dot_mult(&plane->norm, &plane->norm, -1);
	if (fabs(dv) < 0)
		return (plane->dist = 0);
	xv = dot_prod(&x_point, &plane->norm);
	t = xv / dv;
	plane->dist = t;
	if (t < RAY_MIN || t > RAY_MAX)
		return (plane->dist = 0);
	if (plane->dist < inter->dist_min)
		fill_inter_plane(light, plane, inter, view);
	return (plane->dist);
}

double			shad_plane(t_ray *view, t_plane *plane, t_light *light)
{
	double		dv;
	double		xv;
	double		t;
	t_coor		x_point;
	double		local_dist;

	dot_sub(&plane->center, &view->origin, &x_point);
	dv = dot_prod(&view->direction, &plane->norm);
	if (fabs(dv) < 0)
		return (local_dist = 0);
	xv = dot_prod(&x_point, &plane->norm);
	t = xv / dv;
	local_dist = t;
	if (local_dist < 0.000001 || local_dist > 1)
		return (local_dist = 0);
	return (local_dist);
}

void			closest_plane(t_list *planes, t_env *e)
{
	t_list		*lst;
	t_plane		*actual;

	lst = planes;
	while (lst)
	{
		actual = lst->content;
		is_plane(&e->view.ray, actual, &e->light, &e->inter);
		lst = lst->next;
	}
}

double			check_shadow_plane(t_list *planes, t_env *e)
{
	t_list		*lst;
	t_plane		*actual;

	lst = planes;
	while (lst)
	{
		actual = lst->content;
		if (shad_plane(&e->inter.ray, actual, &e->light))
			return (1);
		lst = lst->next;
	}
	return (0);
}
