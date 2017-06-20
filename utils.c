/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:31:49 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/20 09:37:16 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

void	print_coord(t_coor *coord)
{
	printf("x %f y %f z %f\n", coord->x, coord->y, coord->z);
}

int		rot_view(int keycode, t_env *e)
{
	printf("key %d\n", keycode);
	if (keycode == EX_KEY)
	{
		mlx_destroy_image(e->mlx, e->img.img_ptr);
		mlx_destroy_window(e->mlx, e->win);
		exit(error_msg(0));
	}
	else if (keycode == UP_KEY)
		e->rot_y += 0.2;
	else if (keycode == DOWN_KEY)
		e->rot_y -= 0.2;
	else if (keycode == LEFT_KEY)
		e->rot_z += 0.1;
	else if (keycode == RIGHT_KEY)
		e->rot_z -= 0.1;
	else if (keycode == R_KEY)
		e->rot_y = 0;
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
//	mlx_loop(e->mlx);
	//mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	return (keycode);
}

void	print_rt(t_env *e)
{
	e->pix.y = 0;
	while (e->pix.y < WIN_Y)
	{
		e->pix.x = 0;
		while (e->pix.x < WIN_X)
		{
			check_collision(e);
			e->pix.x++;
		}
		e->pix.y++;
	}
}
