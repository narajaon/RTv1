/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:31:21 by narajaon          #+#    #+#             */
/*   Updated: 2017/07/11 20:08:48 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rot_x(double *x, double *y, double *z, double angle)
{
	double		tmpx;
	double		tmpy;
	double		tmpz;

	tmpx = *x;
	tmpy = cos(angle) * *y - sin(angle) * *z;
	tmpy = sin(angle) * *y + cos(angle) * *z;
	*x = tmpx;
	*y = tmpy;
	*z = tmpz;
}

void	rot_y(double *x, double *y, double *z, double angle)
{
	double		tmpx;
	double		tmpy;
	double		tmpz;

	tmpx = cos(angle) * *x + sin(angle) * *z;
	tmpy = *y;
	tmpz = -sin(angle) * *x + cos(angle) * *z;
	*x = tmpx;
	*y = tmpy;
	*z = tmpz;
}

void	rot_z(double *x, double *y, double *z, double angle)
{
	double		tmpx;
	double		tmpy;
	double		tmpz;

	tmpx = cos(angle) * *x - sin(angle) * *y;
	tmpy = sin(angle) * *x + cos(angle) * *y;
	tmpz = *z;
	*x = tmpx;
	*y = tmpy;
	*z = tmpz;
}
