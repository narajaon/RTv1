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
	e->plan.col = 0x00FFFFFF;
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

void	init_light1(t_env *e)
{
	e->light1.x = 0;
	e->light1.y = 0;
	e->light1.z = 0;
}

void	init_prim(t_env *e)
{
	e->prim.x = e->view.dist;
	e->prim.y = WIN_X / 2 - e->pix.x;
	e->prim.z = WIN_Y / 2 - e->pix.y;
}
