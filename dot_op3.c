/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_op3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 12:47:26 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/15 12:48:02 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cross_prod(t_coor *a, t_coor *b, t_coor *tmp)
{
	tmp->x = a->y * b->z - a->z * b->y;
	tmp->y = a->z * b->x - a->x * b->z;
	tmp->z = a->x * b->y - a->y * b->x;
}

void		vect_project(t_coor *a, t_coor *b, t_coor *res)
{
	double		ab;
	double		bb;

	ab = dot_prod(a, b);
	bb = dot_prod(b, b);
	dot_mult(b, res, ab / bb);
}

void		dot_sub(t_coor *a, t_coor *b, t_coor *tmp)
{
	tmp->x = a->x - b->x;
	tmp->y = a->y - b->y;
	tmp->z = a->z - b->z;
}

void		dot_sum(t_coor *a, t_coor *b, t_coor *tmp)
{
	tmp->x = a->x + b->x;
	tmp->y = a->y + b->y;
	tmp->z = a->z + b->z;
}
