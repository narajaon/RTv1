/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:31:49 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/14 11:57:43 by narajaon         ###   ########.fr       */
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

int		error_msg(int error)
{
	if (error == 1)
		ft_putstr_fd("Usage : ./rtv1 <value>\n1- sphere\
				\n2- cylender\n3- cones\
				\n4- mix\n", 2);
	else if (error == 2)
		ft_putstr_fd("Couldn't allocate memory :(\n", 2);
	else if (error == 3)
		ft_putstr_fd("Invalid scene :(\n", 2);
	else
		ft_putstr_fd("Window closed, cya\n", 1);
	return (error);
}

int		rot_view(int keycode, t_env *e)
{
	//printf("%d\n", keycode);
	if (keycode == EX_KEY)
	{
		mlx_destroy_image(e->mlx, e->img.img_ptr);
		mlx_destroy_window(e->mlx, e->win);
		exit(error_msg(0));
	}
	else if (keycode == UP_KEY)
		e->rot_y += 0.1;
	else if (keycode == DOWN_KEY)
		e->rot_y -= 0.1;
	else if (keycode == LEFT_KEY)
		e->rot_z += 0.1;
	else if (keycode == RIGHT_KEY)
		e->rot_z -= 0.1;
	else if (keycode == R_KEY)
		e->rot_y = 0;
	do_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	return (keycode);
}
