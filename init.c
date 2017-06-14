/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 12:18:35 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/14 16:15:11 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_sphere(t_env *e)
{
	e->sphere.col = 0x00FF0000;
	e->sphere.r = 200;
	e->sphere.x = 0;
	e->sphere.y = 0;
	e->sphere.z = 0;
}

void	init_plan(t_env *e)
{
	e->plan.col = 0x000000FF;
	e->plan.x = 0;
	e->plan.y = 0;
	e->plan.z = 0;
	e->plan.k = 0;
}

void	init_view1(t_env *e)
{
	e->view.x = -300;
	e->view.y = 0;
	e->view.z = 0;
	e->view.dist = 100;
}

void	init_shad(t_env *e, unsigned int col)
{
	e->shad.x = e->prim.x;
	e->shad.y = e->prim.y;
	e->shad.z = e->prim.z;
	e->shad.col = col;
}

void	init_prim(t_env *e)
{
	e->prim.x = e->view.dist;
	e->prim.y = WIN_X / 2 - e->pix.x;
	e->prim.z = WIN_Y / 2 - e->pix.y;
	e->prim.x += e->pad[0];
	e->prim.y += e->pad[1];
	e->prim.z += e->pad[2];
}
