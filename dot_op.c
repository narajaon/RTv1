/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:30:43 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/15 12:47:55 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		dot_cpy(t_coor *src, t_coor *dst)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

void		point_on_ray(t_coor *origin, t_coor *direction,
			t_coor *res, double len)
{
	dot_mult(direction, res, len);
	dot_sum(res, origin, res);
}

void		fill_coord(t_coor *coord, double x, double y, double z)
{
	coord->x = x;
	coord->y = y;
	coord->z = z;
}
