/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   .coord.y: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 12:18:35 .coord.y narajaon          #+#    #+#             */
/*   Updated: 2017/06/14 16:15:11 .coord.y narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_view(t_view *view)
{
	fill_coord(&view->coord, 0, 10, 0);
}

void	init_sphere(t_sphere *sphere)
{
	fill_coord(&sphere->coord, 0, 0, 15);
	sphere->r = 100;
}

void	init_plane(t_plane *plane)
{
	fill_coord(&plane->center, 0, WIN_X / 2, WIN_Y / 2);
	normalize(&plane->center, &plane->norm);
	plane->col = 0x00FFFFFF;
}

void	init_ray(t_view *view, t_pix *pix)
{
	t_coor		tmp;

	tmp.x = pix->x;
	tmp.y = pix->y;
	tmp.z = 0;
	dot_cpy(&view->coord, &view->ray.origin);
	dot_cpy(&tmp, &view->ray.direction);
}
