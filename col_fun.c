/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:30:27 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/15 12:21:30 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			init_col(t_col *col, char r, char g, char b)
{
	col->tab[0] = b;
	col->tab[1] = g;
	col->tab[2] = r;
	col->tab[3] = 0x00;
}

int				mult_col(t_col *col1, t_col *col2)
{
	t_col		new_col;

	new_col.tab[0] = col1->tab[0] * col2->tab[0];
	new_col.tab[1] = col1->tab[1] * col2->tab[1];
	new_col.tab[2] = col1->tab[2] * col2->tab[2];
	new_col.tab[3] = 0x00;
	return (new_col.i);
}

double			clamp_col(double col, double cos)
{
	cos = (cos < 0.1) ? 0.1 : cos;
	if (col * cos * 255 > 255)
		return (col * cos / 255);
	return (col * cos);
}

unsigned int	put_col(t_light *light, t_inter *inter, t_col *shape)
{
	double		b;
	double		g;
	double		r;

	b = clamp_col(shape->tab[0], inter->cos_alph) * 255;
	g = clamp_col(shape->tab[1], inter->cos_alph) * 255;
	r = clamp_col(shape->tab[2], inter->cos_alph) * 255;
	init_col(&inter->col, r, g, b);
	inter->col.i = mult_col(&inter->col, &light->col);
	return (inter->col.i);
}

unsigned int	shad_col(t_inter *inter, int shape, t_light *light)
{
	double		b;
	double		g;
	double		r;
	t_col		u_shape;

	u_shape.i = shape;
	inter->cos_alph = (inter->cos_alph > 0.2) ? inter->cos_alph : 0.2;
	b = (u_shape.tab[0] - u_shape.tab[0] *
			light->ambient) * 255 * inter->cos_alph;
	g = (u_shape.tab[1] - u_shape.tab[1] *
			light->ambient) * 255 * inter->cos_alph;
	r = (u_shape.tab[2] - u_shape.tab[2] *
			light->ambient) * 255 * inter->cos_alph;
	init_col(&inter->col, r, g, b);
	inter->col.i = mult_col(&inter->col, &light->col);
	return (inter->col.i);
}
