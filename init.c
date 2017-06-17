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

void	init_sphere(t_env *e)
{
	e->sphere.col = 0x00FF0000;
	e->sphere.r = 5;
	e->sphere.coord.x = 0;
	e->sphere.coord.y = 0;
	e->sphere.coord.z = 0;
	e->sphere.k = 0;
}

void	init_plan(t_env *e)
{
	e->plan.col = 0x000000FF;
	e->plan.coord.x = 0;
	e->plan.coord.y = 0;
	e->plan.coord.z = 0;
	e->plan.k = 0;
}

void	init_view1(t_env *e)
{
	e->view.coord.x = -10;
	e->view.coord.y = 0;
	e->view.coord.z = -2;
	e->view.dist = 100;
}

void	init_light1(t_env *e)
{
	e->light1.coord.x = 0;
	e->light1.coord.y = 0;
	e->light1.coord.z = 0;
}

void	init_prim(t_env *e)
{
	e->prim.coord.x = e->view.dist;
	e->prim.coord.y = WIN_X / 2 - e->pix.coord.x;
	e->prim.coord.z = WIN_Y / 2 - e->pix.coord.y;
}
