/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:08:43 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/08 19:34:08 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_hook(int keycode, t_env *e)
{
	if (keycode == 53)
	{
		mlx_destroy_image(e->mlx, e->img.img_ptr);
		mlx_destroy_window(e->mlx, e->win);
		exit(error_msg(0));
	}
	return (keycode);
}

int		mouse_move(int x, int y, t_env *e)
{
	printf("x %d y %d", x, y);
	return (0);
}

void	init_sphere(t_env *e)
{
	e->sphere.r = 100;
	e->sphere.col = 0x00000000;
	e->sphere.x = 0;
	e->sphere.y = 0;
	e->sphere.z = 0;
}

void	init_view1(t_env *e)
{
	e->view.x = -300;
	e->view.y = 0;
	e->view.z = 0;
	e->view.dist = 100;
}

void	check_sphere(t_env *e)
{
	double		vx;
	double		vy;
	double		vz;
	double		a;
	double		b;
	double		c;
	double		k1;
	double		k2;
	double		k;
	double		delt;
//	static int	i;

//	if (i == 10)
//		exit(0);
	vx = e->view.dist;
	vy = WIN_X / 2 - e->pix.x;
	vz = WIN_Y / 2 - e->pix.y;
	a = pow(vx, 2) + pow(vy, 2) + pow(vz, 2);
	b = 2 * (e->view.x + e->view.y + e->view.z);
	c = pow(e->view.x, 2) + pow(e->view.x, 2) + pow(e->view.x, 2) + pow(e->view.x, 2) - pow(e->sphere.r, 2);
	delt = pow(b, 2) - 4 * a * c;
	if (delt >= 0)
	{
		k1 = (-b + sqrt(delt)) / 2 * a;
		k2 = (-b - sqrt(delt)) / 2 * a;
		//le plus petit non negatif???
		k = (k1 < k2) ? k1 : k2;
	}
	else
		k = 0;
	e->prim.x = e->view.x + k * vx;
	e->prim.y = e->view.y + k * vy;
	e->prim.z = e->view.z + k * vz;
//	if (!(pow(e->prim.x, 2) + pow(e->prim.y, 2) + pow(e->prim.z, 2) - pow(e->sphere.r, 2)))
		e->img.img[e->pix.y * WIN_X + e->pix.x] = e->sphere.col;
//	printf("primx %f primy %f primz %f\n", e->prim.x, e->prim.y, e->prim.z);
//	i++;
}

void	do_sphere(t_env *e)
{
	init_sphere(e);
	init_view1(e);
	print_rt(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	mlx_key_hook(e->win, &key_hook, e);
	mlx_loop(e->mlx);
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ac != 2)
		exit(error_msg(1));
	e.scene = ft_atoi(av[1]);
	if (e.scene == 4 || e.scene > 4 || e.scene <= 0)
		exit(error_msg(4));
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIN_X, WIN_Y, "Displaying RT scene");
	e.img.img_ptr = mlx_new_image(e.mlx, WIN_X, WIN_Y);
	e.img.img = (int *)mlx_get_data_addr(e.img.img_ptr,
			&e.img.bpp, &e.img.size_line, &e.img.endian);
	do_sphere(&e);
	return (0);
}
