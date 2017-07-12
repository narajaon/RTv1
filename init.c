/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:30:54 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/12 19:31:49 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_inter(t_inter *inter)
{
	init_col(&inter->col, 0x00, 0x00, 0x00);
	inter->shape = NONE;
	inter->dist_min = INFINITY;
}

void	init_ray(t_view *view, t_pix *pix)
{
	dot_cpy(&view->coord, &view->ray.origin);
	view->ray.origin.x += view->x_value;
	view->ray.origin.y += view->y_value;
	view->ray.origin.z += view->z_value;
	fill_coord(&view->ray.direction, pix->x, pix->y, 0);
	view->ray.direction.x += view->x_value;
	view->ray.direction.y += view->y_value;
	view->ray.direction.z += view->z_value;
	dot_sub(&view->ray.direction, &view->ray.origin, &view->ray.direction);
	rot_y(&view->ray.direction.x, &view->ray.direction.y,
			&view->ray.direction.z, view->rot_y);
	rot_z(&view->ray.direction.x, &view->ray.direction.y,
			&view->ray.direction.z, view->rot_z);
	rot_x(&view->ray.direction.x, &view->ray.direction.y,
			&view->ray.direction.z, view->rot_x);
	normalize(&view->ray.direction, &view->ray.direction);
	view->ray.len = 0;
}
