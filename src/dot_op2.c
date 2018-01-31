/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 12:46:17 by narajaon          #+#    #+#             */
/*   Updated: 2018/01/31 14:56:59 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double		dot_prod(t_coor *a, t_coor *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double		vect_pow(t_coor *a)
{
	return (pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
}

double		vect_len(t_coor *a)
{
	return (sqrt(vect_pow(a)));
}

void		dot_mult(t_coor *a, t_coor *tmp, double nb)
{
	tmp->x = a->x * nb;
	tmp->y = a->y * nb;
	tmp->z = a->z * nb;
}

void		normalize(t_coor *a, t_coor *tmp)
{
	double		len;

	len = vect_len(a);
	dot_mult(a, tmp, 1 / len);
}
