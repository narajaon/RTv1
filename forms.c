/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:30:50 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/12 18:59:51 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		check_shadow(t_env *e)
{
	if (check_shadow_sphere(e->spheres, e))
		return (1);
	if (check_shadow_cylinder(e->cylinders, e))
		return (1);
	if (check_shadow_cone(e->cones, e))
		return (1);
	//if (check_shadow_plane(e->planes, e))
	//	return (1);
	return (0);
}

int		check_collision(t_env *e)
{
	init_inter(&e->inter);
	init_ray(&e->view, &e->pix);
	dot_sub(&e->plane.norm, &e->plane.center, &e->plane.norm);
	closest_plane(e->planes, e);
	closest_sphere(e->spheres, e);
	closest_cylinder(e->cylinders, e);
	closest_cone(e->cones, e);
	if (check_shadow(e))
	{
		return (e->img.img[e->pix.y * WIN_Y + e->pix.x] =
					shad_col(&e->inter, e->inter.shape, &e->light));
	}
	return (e->img.img[e->pix.y * WIN_Y + e->pix.x] = e->inter.col.i);
}
